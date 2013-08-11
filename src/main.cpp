/*
	Toxitty - An experimental Tox client.
	Copyright (C) 2013  Kamil Chojnowski <diath@pyboard.net>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "buffers.hpp"
#include "callbacks.hpp"
#include "commands.hpp"
#include "config.hpp"
#include "core.hpp"
#include "keyhandler.hpp"
#include "interface.hpp"
#include "input.hpp"

int main(int argc, char *argv[])
{
	config->load();
	interface->init();

	buffers->append(Buffers::CoreBuffer, "[#] Toxitty v0.1");
	buffers->append(Buffers::CoreBuffer, "[#] Type /help for more information.");

	commands->add("help", "Displays help contents.", Commands::Help);
	commands->add("buffer", "Manages buffer navigation.", Commands::Buffer);
	commands->add("exit", "Exits the client.", Commands::Exit);
	commands->add("quit", "Exits the client.", Commands::Exit);
	commands->add("commands", "Lists available commands.", Commands::CommandsList);
	commands->add("add", "Sends a friend request.", Commands::Add);
	commands->add("accept", "Accepts a friend request.", Commands::Accept);
	commands->add("nick", "Changes your nick.", Commands::Nick);
	commands->add("status", "Changes your status message.", Commands::Status);
	commands->add("set", "Manages user configuration.", Commands::Set);
	commands->add("message", "Sends a message to a receiver", Commands::Message);
	commands->add("query", "Opens a conversation buffer with receiver.", Commands::Query);
	commands->add("close", "Clears and closes currently open buffer.", Commands::Close);
	commands->add("online", "Sets your status to online.", Commands::Online);
	commands->add("away", "Sets your status to away.", Commands::Away);
	commands->add("busy", "Sets your status to busy.", Commands::Busy);
	commands->add("me", "Sends action message.", Commands::Me);
	commands->add("save", "Saves current configuration.", Commands::Save);

	keyHandler->addShortcut(KEY_UP, [] { input->prevHistory(buffers->getCurrent()); clear(); });
	keyHandler->addShortcut(KEY_DOWN, [] { input->nextHistory(buffers->getCurrent()); clear(); });
	keyHandler->addShortcut(KEY_LEFT, [] { input->prevCaret(buffers->getCurrent()); clear(); });
	keyHandler->addShortcut(KEY_RIGHT, [] { input->nextCaret(buffers->getCurrent()); clear(); });
	keyHandler->addShortcut(KEY_PPAGE, [] { interface->onScrollUp(); clear(); });
	keyHandler->addShortcut(KEY_NPAGE, [] { interface->onScrollDown(); clear(); });
	keyHandler->addShortcut(KEY_RESIZE, [] { interface->onResize(); clear(); });

	m_callback_friendrequest(Callbacks::FriendRequest);
	m_callback_friendmessage(Callbacks::Message);
	m_callback_action(Callbacks::ActionMessage);
	m_callback_namechange(Callbacks::NickChange);
	m_callback_userstatus(Callbacks::StatusChange);
	m_callback_statusmessage(Callbacks::StatusMessageChange);

	core->start();

	int ch = 0;
	unsigned int currentBuffer = 0;

	while(core->isRunning())
	{
		ch = getch();
		currentBuffer = buffers->getCurrent();

		if(!keyHandler->handle(ch))
		{
			if((ch == 0x107 || ch == 0x8 || ch == 0x7f) && input->data[currentBuffer].length() > 0)
			{
				int position = input->getPosCaret(currentBuffer);
				if(position == -1)
					input->data[currentBuffer].pop_back();
				else if(position > 0)
				{
					input->data[currentBuffer] = input->data[currentBuffer].erase(position - 1, 1);
					input->setPosCaret(currentBuffer, position - 1);
				}
			}
			else if(ch == KEY_DC && input->data[currentBuffer].length() > 0)
			{
				int position = input->getPosCaret(currentBuffer);
				if(position != -1)
				{
					if(position == (int) input->data[currentBuffer].size() - 1)
					{
						input->data[currentBuffer].pop_back();
						input->setPosCaret(currentBuffer, position - 1);
					}
					else
						input->data[currentBuffer] = input->data[currentBuffer].erase(position, 1);
				}
			}
			else if(ch >= 32 && ch <= 126)
			{
				int position = input->getPosCaret(currentBuffer);
				if(position == -1)
					input->data[currentBuffer] += (char) ch;
				else
				{
					input->data[currentBuffer].insert(position, 1, (char) ch);
					input->setPosCaret(currentBuffer, position + 1);
				}
			}
			else if((ch == '\n' || ch == KEY_ENTER) && input->data[currentBuffer].length() > 0)
			{
				if(input->data[currentBuffer][0] == '/' || currentBuffer == Buffers::CoreBuffer)
				{
					if(input->data[currentBuffer][0] != '/')
						input->data[currentBuffer].insert(0, 1, '/');

					if(!commands->execute(input->data[currentBuffer]))
						buffers->append(Buffers::CoreBuffer, "[!] Unrecognized command: " + input->data[currentBuffer]);
				}
				else
				{
					int id = buffers->getFriendByBuffer(currentBuffer);
					if(id != -1)
					{
						buffers->appendf(currentBuffer, "[%s] <%s> %s", getTime(true).c_str(), core->getNick().c_str(), input->data[currentBuffer].c_str());

						if(!m_sendmessage(id, (unsigned char *) input->data[currentBuffer].c_str(), input->data[currentBuffer].length() + 1))
							buffers->append(currentBuffer, "[!] Couldn't send your message.");
					}
					else
						buffers->append(currentBuffer, "[!] No friend assigned to this buffer.");
				}

				input->history[currentBuffer].push_back(input->data[currentBuffer]);
				if((int) input->history[currentBuffer].size() >= config->getIntValue("limit.input"))
					input->history[currentBuffer].erase(input->history[currentBuffer].begin());

				input->setPosHistory(currentBuffer, -1);
				input->setPosCaret(currentBuffer, -1);

				input->data[currentBuffer].clear();

				clear();
			}
		}

		interface->draw();
		interface->clr();
	}

	interface->end();
	config->save();

	return 0;
}
