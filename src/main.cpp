#include <iostream>
#include <ncurses.h>

#include "keyhandler.hpp"

int main(int argc, char *argv[])
{
	initscr();
	raw();
	keypad(stdscr, 0);
	noecho();

	printw(":: Toxitty v0.1\n");
	printw(":: Type /help for more information.\n");

	bool running = true;
	keyHandler->addShortcut(126, [&running] { running = false; });

	int h = 0, w = 0;
	getmaxyx(stdscr, h, w);

	int currentBuffer = 0;

	std::string buffer;
	int ch = 0;
	while(running)
	{
		ch = getch();
		if(!keyHandler->handle(ch))
		{
			if(ch == 127 && buffer.length() > 0)
				buffer.pop_back();
			else if(ch >= 65 && ch <= 122)
				buffer += (char) ch;
			else if(ch == '\n')
				buffer.clear();
		}

		mvprintw(h - 1, 0, "[Buffer #%d] [Nick] [Receiver] %s", currentBuffer, buffer.c_str());

		clrtoeol();
		refresh();
	}

	endwin();
	return 0;
}
