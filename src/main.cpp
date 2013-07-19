#include <iostream>
#include <ncurses.h>

#include "buffers.hpp"
#include "keyhandler.hpp"

int main(int argc, char *argv[])
{
	initscr();
	raw();
	noecho();

	buffers->append(Buffers::CoreBuffer, ":: Toxitty v0.1\n");
	buffers->append(Buffers::CoreBuffer, ":: Type /help for more information.\n");

	bool running = true;
	keyHandler->addShortcut(126, [&running] { running = false; });

	int h = 0, w = 0;
	getmaxyx(stdscr, h, w);

	int currentBuffer = 0;

	std::string input;
	int ch = 0;
	while(running)
	{
		ch = getch();
		if(!keyHandler->handle(ch))
		{
			if(ch == 127 && input.length() > 0)
				input.pop_back();
			else if(ch >= 65 && ch <= 122)
				input += (char) ch;
			else if(ch == '\n' && input.length() > 0)
			{
				buffers->append(currentBuffer, input + '\n');
				input.clear();
			}
		}

		mvprintw(0, 0, "%s", buffers->getData(currentBuffer).c_str());
		mvprintw(h - 1, 0, "[Buffer #%d] [Nick] [Receiver] %s", currentBuffer, input.c_str());

		clrtoeol();
		refresh();
	}

	endwin();
	return 0;
}
