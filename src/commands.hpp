#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "buffers.hpp"

class Commands
{
	public:
		Commands();
		~Commands();

		bool add(const std::string &command, std::function<void(const std::string &)> func);
		bool execute(std::string &data);

		static void help(const std::string &data);

	private:
		std::map<std::string, std::function<void(const std::string &)>> m_commands;
};

extern std::shared_ptr<Commands> commands;

#endif
