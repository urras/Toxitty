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

	getmaxyx(stdscr, height, width);

	running = true;
}

void Interface::draw()
{
	unsigned int buffer = buffers->getCurrent();
	int caret = input->getPosCaret(buffer);
	(void) caret;

	unsigned int size = buffers->getSize(buffer);
	if(size > 0)
	{
		int scroll = buffers->getScroll(buffer);
		if(scroll == -1)
		{
			if(size < (unsigned int) height)
			{
				for(int i = 0; i < height; ++i)
					mvprintw(i, 0, "%s\n", buffers->getData(buffer, i).c_str());
			}
			else
			{
				int start = size - height + 1;
				int p = 0;
				for(int i = start; i < (int) size; ++i, ++p)
					mvprintw(p, 0, buffers->getData(buffer, i).c_str());
			}
		}
		else
		{
			int p = 0;
			for(int i = scroll; i < scroll + height; ++i, ++p)
				mvprintw(p, 0, buffers->getData(buffer, i).c_str());
		}
	}

	mvprintw(height - 1, 0, "%s [#%d] (C:%d) [Nick] [Receiver] %s\n", getTime().c_str(), buffer, input->getPosCaret(buffer), input->data[buffer].c_str());
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
}
