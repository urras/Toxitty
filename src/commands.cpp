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

bool Commands::execute(std::string &data)
{
	std::size_t position = data.find(' ');
	const std::string &command = (position != std::string::npos ? data.substr(1, position - 1) : data.substr(1));

	std::map<std::string, std::function<void(const std::string &)>>::iterator it = m_commands.find(command);
	if(it != m_commands.end())
	{
		if(position != std::string::npos)
			data = data.substr(position + 1);

		(it->second)(data);
		return true;
	}

	return false;
}

void Commands::help(const std::string &data)
{
	buffers->append(Buffers::CoreBuffer, "[#] Command /help executed, data: " + data);
}
