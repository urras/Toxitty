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

	mvprintw(0, 0, "%s", buffers->getData(buffer).c_str());
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
