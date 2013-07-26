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
	if(size < (unsigned int) height)
	{
		for(int i = 0; i < height; ++i)
		{
			mvprintw(i, 0, "%s\n", buffers->getData(buffer, i).c_str());
		}
	}
	else
	{
		int start = size - height + 1;
		int p = 0;
		for(int i = start; i < (int) size; ++i)
		{
			mvprintw(p, 0, buffers->getData(buffer, i).c_str());
			//mvprintw(p, 0, "p: %d, i: %d\n", p, i);
			++p;
		}
	}

	mvprintw(height - 1, 0, "[#%d] [Nick] [Receiver] %s\n", buffer, input->data[buffer].c_str());
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
