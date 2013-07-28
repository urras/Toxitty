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

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <iomanip>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>

#include "buffers.hpp"
#include "interface.hpp"

typedef std::tuple<std::string, std::function<void(const std::string &)>> Command;

class Commands
{
	public:
		Commands();
		~Commands();

		bool add(const std::string &command, const std::string &description, std::function<void(const std::string &)> func);
		bool execute(std::string &data);

		void getCommands(std::map<std::string, Command> &commands) { commands = m_commands; }

		static void Help(const std::string &data);
		static void Buffer(const std::string &data);
		static void Exit(const std::string &data);
		static void CommandsList(const std::string &data);

	private:
		std::map<std::string, Command> m_commands;
};

extern std::shared_ptr<Commands> commands;

#endif
