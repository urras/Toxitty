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

#include "interface.hpp"

std::shared_ptr<Interface> interface(new Interface());

Interface::Interface()
{
	width = 0;
	height = 0;
	running = false;

	for (unsigned int i = 0; i < Buffers::MaxBuffers; ++i)
	{
		m_bufferScroll[i] = 0;
	}
}

Interface::~Interface()
{
}

void Interface::init()
{
	initscr();
	raw();
	noecho();
	keypad(stdscr, 1);
	nodelay(stdscr, 1);

	onResize();

	running = true;
}

void Interface::draw()
{
	unsigned int buffer = buffers->getCurrent();
	int caret = input->getPosCaret(buffer);
	(void) caret;

	// Draw the buffer's contents
	int size = (int) buffers->getSize(buffer);
	unsigned int from = size - bufferHeight - m_bufferScroll[buffer];
	if (size > 0)
	{
		int row = 0;
		for (int i = from; i < size; ++i, ++row)
		{
			mvprintw(row, 0, buffers->getData(buffer, i).c_str());
		}
	}

	mvprintw(height - 1, 0, "%s [#%d] [Nick] [Receiver] %s\n", getTime().c_str(), buffer, input->data[buffer].c_str());
}

void Interface::clr()
{
	clrtoeol();
	refresh();
}

void Interface::end()
{
	endwin();
}

void Interface::onResize()
{
	getmaxyx(stdscr, height, width);
	bufferHeight = height - 1;
}

void Interface::onScrollUp()
{
	unsigned int buffer = buffers->getCurrent();
	int size = (int) buffers->getSize(buffer);
	int offset = m_bufferScroll[buffer];

	if (size > bufferHeight + offset)
	{
		++m_bufferScroll[buffer];
	}
}

void Interface::onScrollDown()
{
	unsigned int buffer = buffers->getCurrent();
	unsigned int offset = m_bufferScroll[buffer];
	if (offset > 0)
	{
		--m_bufferScroll[buffer];
	}
}
