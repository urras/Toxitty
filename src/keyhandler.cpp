#include "keyhandler.hpp"

extern std::shared_ptr<KeyHandler> keyHandler(new KeyHandler());

KeyHandler::KeyHandler()
{
}

KeyHandler::~KeyHandler()
{
	m_shortcuts.clear();
}

bool KeyHandler::handle(int character)
{
	std::map<int, std::function<void()>>::iterator it = m_shortcuts.find(character);
	if(it != m_shortcuts.end())
	{
		(it->second)();
		return true;
	}

	return false;
}

bool KeyHandler::addShortcut(int character, std::function<void()> func)
{
	if(m_shortcuts.find(character) == m_shortcuts.end())
	{
		m_shortcuts[character] = func;
		return true;
	}

	return false;
}

bool KeyHandler::delShortcut(int character)
{
	if(m_shortcuts.find(character) != m_shortcuts.end())
	{
		m_shortcuts.erase(character);
		return true;
	}

	return false;
}
