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

#include "keyhandler.hpp"

std::shared_ptr<KeyHandler> keyHandler(new KeyHandler());

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
