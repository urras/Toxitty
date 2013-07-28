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

#include "input.hpp"

std::shared_ptr<Input> input(new Input());

Input::Input()
{
	for(unsigned int i = 0; i < Buffers::MaxBuffers; ++i)
	{
		m_posHistory[i] = -1;
		m_posCaret[i] = -1;
	}
}

Input::~Input()
{
}

void Input::prevCaret(unsigned int buffer)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return;

	if(data[buffer].size() == 0)
		return;

	if(m_posCaret[buffer] == -1)
		m_posCaret[buffer] = data[buffer].length() - 1;
	else
		--m_posCaret[buffer];
}

void Input::nextCaret(unsigned int buffer)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return;

	if(data[buffer].size() == 0)
		return;

	if(m_posCaret[buffer] < (int) data[buffer].length() - 1)
		++m_posCaret[buffer];
}

void Input::prevHistory(unsigned int buffer)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return;

	if(history[buffer].size() == 0)
		return;

	if(m_posHistory[buffer] == -1)
		m_posHistory[buffer] = history[buffer].size() - 1;
	else if(m_posHistory[buffer] > 0)
		--m_posHistory[buffer];

	data[buffer] = history[buffer].at(m_posHistory[buffer]);
}

void Input::nextHistory(unsigned int buffer)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return;

	if(history[buffer].size() == 0)
		return;

	if(m_posHistory[buffer] < (int) history[buffer].size() - 1)
		++m_posHistory[buffer];

	data[buffer] = history[buffer].at(m_posHistory[buffer]);
}

int Input::getPosCaret(unsigned int buffer)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return -1;

	return m_posCaret[buffer];
}

void Input::setPosCaret(unsigned int buffer, int position)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return;

	m_posCaret[buffer] = position;
}

int Input::getPosHistory(unsigned int buffer)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return -1;

	return m_posHistory[buffer];
}

void Input::setPosHistory(unsigned int buffer, int position)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return;

	m_posHistory[buffer] = position;
}
