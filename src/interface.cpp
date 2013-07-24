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

	getmaxyx(stdscr, height, width);

	running = true;
}

void Interface::draw()
{
	unsigned int currentBuffer = buffers->getCurrent();

	mvprintw(0, 0, "%s", buffers->getData(currentBuffer).c_str());
	mvprintw(height - 1, 0, "[#%d] [Nick] [Receiver] %s\n", currentBuffer, input->data[currentBuffer].c_str());
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
