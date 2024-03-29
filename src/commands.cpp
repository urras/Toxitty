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

#include "commands.hpp"

std::shared_ptr<Commands> commands(new Commands());

Commands::Commands()
{
}

Commands::~Commands()
{
}

bool Commands::add(const std::string &command, const std::string &description, std::function<void(const std::string &)> func)
{
	if(m_commands.find(command) == m_commands.end())
	{
		m_commands[command] = Command(description, func);
		return true;
	}

	return false;
}

bool Commands::execute(std::string data)
{
	std::size_t position = data.find(' ');
	const std::string &command = (position != std::string::npos ? data.substr(1, position - 1) : data.substr(1));

	std::map<std::string, Command>::iterator it = m_commands.find(command);
	if(it != m_commands.end())
	{
		if(position != std::string::npos)
			data = data.substr(position + 1);
		else
			data = "";

		std::get<1>(it->second)(data);
		return true;
	}

	return false;
}

void Commands::Help(const std::string &data)
{
	buffers->append(Buffers::CoreBuffer, "[#] You can find a general FAQ at https://github.com/diath/Toxitty/blob/master/doc/HELP");
	buffers->append(Buffers::CoreBuffer, "[#] Use /commands to see the list of available commands.");
}

void Commands::Buffer(const std::string &data)
{
	if(data == "prev")
		buffers->prev();
	else if(data == "next")
		buffers->next();
	else if(data == "clear")
		buffers->erase(buffers->getCurrent());
	else
	{
		unsigned int buffer = (unsigned int) atoi(data.c_str());
		if(buffer < 0 || buffer > Buffers::MaxBuffers)
			return;

		buffers->setCurrent(buffer);
	}

	clear();
}

void Commands::Exit(const std::string &data)
{
	core->setRunning(false);
}

void Commands::CommandsList(const std::string &data)
{
	buffers->append(Buffers::CoreBuffer, "[#] Available commands:");

	std::map<std::string, Command> list;
	commands->getCommands(list);
	std::stringstream command;

	for(const auto &it : list)
	{
		command.str("");
		command << "    /" << std::left << std::setw(16) << std::setfill(' ') << it.first << ' ' << std::get<0>(it.second);
		buffers->append(Buffers::CoreBuffer, command.str());
	}
}

void Commands::Set(const std::string &data)
{
	StringVec parameters = split(data, " ");
	if(parameters.size() == 0)
	{
		buffers->append(Buffers::CoreBuffer, "[#] Current configuration:");

		std::map<std::string, std::string> values = config->getValues();
		std::stringstream option;

		for(const auto &it : values)
		{
			option.str("");
			option << "    " << std::left << std::setw(24) << std::setfill(' ') << it.first << ' ' << it.second;
			buffers->append(Buffers::CoreBuffer, option.str());
		}
	}
	else if(parameters.size() == 1)
	{
		std::string value = config->getValue(parameters[0]);
		if(value.empty())
			buffers->appendf(Buffers::CoreBuffer, "[#] No value set for key '%s'.", parameters[0].c_str());
		else
			buffers->appendf(Buffers::CoreBuffer, "[#] Key '%s' is set to '%s'.", parameters[0].c_str(), value.c_str());
	}
	else
	{
		std::string value;
		if(parameters.size() == 2)
			value = parameters[1];
		else
		{
			StringVec vec = parameters;
			vec.erase(vec.begin());

			value = join(vec, " ");
		}

		config->setValue(parameters[0], value);
		buffers->appendf(Buffers::CoreBuffer, "[#] Key '%s' has been set to '%s'.", parameters[0].c_str(), value.c_str());
	}
}

void Commands::Add(const std::string &data)
{
	StringVec parameters = split(data, " ");
	if(parameters.size() == 0)
	{
		buffers->append(Buffers::CoreBuffer, "[!] Command requires at least one parameters.");
		return;
	}

	if(parameters[0].empty() || parameters[0].length() > crypto_box_PUBLICKEYBYTES * 2 || !verifyKey(parameters[0]))
		buffers->append(Buffers::CoreBuffer, "[!] Invalid public key.");
	else
	{
		int ret = FAERR_UNKNOWN;
		if(parameters.size() == 2)
			ret = m_addfriend((unsigned char *) publicKeyToData(parameters[0]).c_str(), (unsigned char *) parameters[1].c_str(), parameters[1].length() + 1);
		else	
			ret = m_addfriend((unsigned char *) publicKeyToData(parameters[0]).c_str(), (unsigned char *) "via Toxitty", sizeof("via Toxitty") + 1);

		switch(ret)
		{
			case FAERR_TOOLONG:
				buffers->appendf(Buffers::CoreBuffer, "[!] Request message too long.");
			break;

			case FAERR_NOMESSAGE:
				buffers->append(Buffers::CoreBuffer, "[!] Missing request message.");
			break;

			case FAERR_OWNKEY:
				buffers->append(Buffers::CoreBuffer, "[!] Can not send a friend request to yourself.");
			break;

			case FAERR_ALREADYSENT:
				buffers->append(Buffers::CoreBuffer, "[!] Friend request already sent.");
			break;

			case FAERR_UNKNOWN:
				buffers->append(Buffers::CoreBuffer, "[!] Unknown error occured while sending a friend request.");
			break;

			default:
				buffers->appendf(Buffers::CoreBuffer, "[#] Friend added as %d.", ret);
		}
	}
}

void Commands::Accept(const std::string &data)
{
	int number = atoi(data.c_str());
	if(number < 0 || number > (int) Core::MaxRequests)
		buffers->append(Buffers::CoreBuffer, "[!] Invalid request number.");
	else
	{
		if(core->acceptRequest(number))
			buffers->append(Buffers::CoreBuffer, "[#] Friend request accepted.");
		else
			buffers->append(Buffers::CoreBuffer, "[#] Failed to accept the friend request.");
	}
}

void Commands::Nick(const std::string &data)
{
	if(data.empty() || data.length() > MAX_NAME_LENGTH)
		buffers->append(Buffers::CoreBuffer, "[!] Invalid nick length.");
	else
	{
		char nick[MAX_NAME_LENGTH];
		memcpy(nick, data.c_str(), data.length() + 1);
		setname((unsigned char *) nick, data.length() + 1);

		core->setNick(data);
		config->setValue("nick", data);

		buffers->appendf(Buffers::CoreBuffer, "[#] Nick changed to %s.", nick);
	}
}

void Commands::Status(const std::string &data)
{
	if(data.empty() || data.length() > MAX_STATUSMESSAGE_LENGTH)
		buffers->append(Buffers::CoreBuffer, "[!] Invalid status message length.");
	else
	{
		char status[MAX_STATUSMESSAGE_LENGTH];
		memcpy(status, data.c_str(), data.length() + 1);
		m_set_statusmessage((unsigned char *) status, data.length() + 1);

		core->setStatusMessage(data);
		config->setValue("status", data);

		buffers->appendf(Buffers::CoreBuffer, "[#] Status message changed to %s.", status);
	}
}

void Commands::Message(const std::string &data)
{
	StringVec parameters = split(data, " ");
	if(parameters.size() < 2)
		buffers->append(Buffers::CoreBuffer, "[#] Command requires two parameters.");
	else
	{
		std::string message;
		if(parameters.size() == 2)
			message = parameters[1];
		else
		{
			StringVec vec = parameters;
			vec.erase(vec.begin());

			message = join(vec, " ");
		}

		int id = atoi(parameters[0].c_str());
		if(!m_sendmessage(id, (unsigned char *) message.c_str(), message.length() + 1))
			buffers->append(Buffers::CoreBuffer, "[!] Could not send your message.");
		else
		{
			int buffer = buffers->getBufferByFriend(id);
			if(buffer == -1)
			{
				buffer = buffers->getFirstFree();
				if(buffer == -1)
					buffers->append(Buffers::CoreBuffer, "[!] Could not assign a new buffer.");
				else
				{
					buffers->assign(buffer, id);
					buffers->appendf(buffer, "[%s] <%s> %s", getTime(true).c_str(), core->getNick().c_str(), message.c_str());
					buffers->setCurrent(buffer);
				}
			}
		}
	}
}

void Commands::Me(const std::string &data)
{
	unsigned int buffer = buffers->getCurrent();
	if(buffer == 0)
		buffers->append(Buffers::CoreBuffer, "[!] Can not execute /me in the core buffer.");
	else
	{
		int id = buffers->getFriendByBuffer(buffer);
		if(!m_sendaction(id, (unsigned char *) data.c_str(), data.length() + 1))
			buffers->append(buffer, "[!] Can not send the action message.");
		else
		{
			buffers->appendf(buffer, "[%s] * %s %s", getTime(true).c_str(), core->getNick().c_str(), data.c_str());
		}
	}
}

void Commands::Query(const std::string &data)
{
	int id = atoi(data.c_str());
	int buffer = buffers->getBufferByFriend(id);
	if(buffer == -1)
	{
		buffer = buffers->getFirstFree();
		if(buffer == -1)
			buffers->append(Buffers::CoreBuffer, "[!] Could not assign a new buffer.");
		else
			buffers->assign(buffer, id);
	}

	if(buffer != -1)
		buffers->setCurrent(buffer);
}

void Commands::Close(const std::string &data)
{
	int buffer = buffers->getCurrent();
	if(buffer == 0)
		buffers->append(buffer, "[!] The core buffer can not be closed.");
	else
	{
		buffers->erase(buffer);
		buffers->assign(buffer, -1);
		buffers->setCurrent(0);
	}
}

void Commands::Online(const std::string &data)
{
	m_set_userstatus(USERSTATUS_NONE);

	if(core->getStatusMessage().length() == 0)
		buffers->append(Buffers::CoreBuffer, "[#] Your status is now online.");
	else
		buffers->appendf(Buffers::CoreBuffer, "[#] Your status is now online (%s).", core->getStatusMessage().c_str());
}

void Commands::Away(const std::string &data)
{
	m_set_userstatus(USERSTATUS_AWAY);

	if(core->getStatusMessage().length() == 0)
		buffers->append(Buffers::CoreBuffer, "[#] Your status is now away.");
	else
		buffers->appendf(Buffers::CoreBuffer, "[#] Your status is now away (%s).", core->getStatusMessage().c_str());
}

void Commands::Busy(const std::string &data)
{
	m_set_userstatus(USERSTATUS_BUSY);

	if(core->getStatusMessage().length() == 0)
		buffers->append(Buffers::CoreBuffer, "[#] Your status is now busy.");
	else
		buffers->appendf(Buffers::CoreBuffer, "[#] Your status is now busy (%s).", core->getStatusMessage().c_str());
}

void Commands::Save(const std::string &data)
{
	if(config->save())
		buffers->append(Buffers::CoreBuffer, "[#] Configuration saved.");
}
