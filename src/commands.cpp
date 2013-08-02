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
	buffers->append(Buffers::CoreBuffer, "[#] Command /help executed, data: " + data);
	buffers->appendf(0, "Expected: 4, got: %d.", data.length());
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
	(void) data;
	core->setRunning(false);
}

void Commands::CommandsList(const std::string &data)
{
	(void) data;
	buffers->append(Buffers::CoreBuffer, "[#] Available commands:");

	std::map<std::string, Command> list;
	commands->getCommands(list);

	for(std::map<std::string, Command>::iterator it = list.begin(); it != list.end(); ++it)
	{
		std::stringstream command;
		command << "    /" << std::left << std::setw(16) << std::setfill(' ') << it->first << ' ' << std::get<0>(it->second);
		buffers->append(Buffers::CoreBuffer, command.str());
	}
}

void Commands::Accept(const std::string &data)
{
	int number = atoi(data.c_str());
	if(number < 0 || number > (int) Core::MaxRequests)
		buffers->append(Buffers::CoreBuffer, "[!] Invalid request number.");
	else
	{
		core->acceptRequest(number);
		buffers->append(Buffers::CoreBuffer, "[#] Friend request accepted.");
	}
}

void Commands::Nick(const std::string &data)
{
	if(data.empty() || data.length() > MAX_NAME_LENGTH)
		buffers->append(Buffers::CoreBuffer, "[!] Invalid nick length.");
	else
	{
		char nick[MAX_NAME_LENGTH];
		strcpy(nick, data.c_str());
		setname((unsigned char *) nick, data.length());

		buffers->appendf(Buffers::CoreBuffer, "[#] Nick changed to %s.", nick);
	}
}
