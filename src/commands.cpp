#include "commands.hpp"

std::shared_ptr<Commands> commands(new Commands());

Commands::Commands()
{
}

Commands::~Commands()
{
}

bool Commands::add(const std::string &command, std::function<void(const std::string &)> func)
{
	if(m_commands.find(command) == m_commands.end())
	{
		m_commands[command] = func;
		return true;
	}

	return false;
}

bool Commands::execute(const std::string &command)
{
	std::map<std::string, std::function<void(const std::string &)>>::iterator it = m_commands.find(command);
	if(it != m_commands.end())
	{
		(it->second)(command);
		return true;
	}

	return false;
}

void Commands::help(const std::string &data)
{
	buffers->append(Buffers::CoreBuffer, "[#] Command executed: ");
	buffers->append(Buffers::CoreBuffer, data + '\n');
}
