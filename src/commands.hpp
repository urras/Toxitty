#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "buffers.hpp"

typedef std::tuple<std::string, std::function<void(const std::string &)>> Command;

class Commands
{
	public:
		Commands();
		~Commands();

		bool add(const std::string &command, const std::string &description, std::function<void(const std::string &)> func);
		bool execute(std::string &data);

		static void Help(const std::string &data);
		static void Buffer(const std::string &data);

	private:
		std::map<std::string, Command> m_commands;
};

extern std::shared_ptr<Commands> commands;

#endif
