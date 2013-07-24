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

bool Commands::execute(std::string &data)
{
	std::size_t position = data.find(' ');
	const std::string &command = (position != std::string::npos ? data.substr(1, position - 1) : data.substr(1));

	std::map<std::string, Command>::iterator it = m_commands.find(command);
	if(it != m_commands.end())
	{
		if(position != std::string::npos)
			data = data.substr(position + 1);

		std::get<1>(it->second)(data);
		return true;
	}

	return false;
}

void Commands::Help(const std::string &data)
{
	buffers->append(Buffers::CoreBuffer, "[#] Command /help executed, data: " + data);
}

void Commands::Buffer(const std::string &data)
{
	if(data == "prev")
		buffers->prev();
	else if(data == "next")
		buffers->next();
	else
	{
		unsigned int buffer = (unsigned long) atoi(data.c_str());
		if(buffer < 0 || buffer > Buffers::MaxBuffers)
			return;

		buffers->setCurrent(buffer);
	}
}

void Commands::Exit(const std::string &data)
{
	(void) data;
	interface->running = false;
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
