#include <iostream>
#include <ncurses.h>

#include "buffers.hpp"
#include "commands.hpp"
#include "keyhandler.hpp"

int main(int argc, char *argv[])
{
	initscr();
	raw();
	noecho();
	keypad(stdscr, 1);

	int h = 0, w = 0;
	getmaxyx(stdscr, h, w);

	bool running = true;

	buffers->append(Buffers::CoreBuffer, "[#] Toxitty v0.1\n");
	buffers->append(Buffers::CoreBuffer, "[#] Type /help for more information.\n");

	commands->add("help", Commands::help);

	keyHandler->addShortcut(KEY_F(1), [&running] { running = false; });
	keyHandler->addShortcut(KEY_LEFT, [] { buffers->prev(); clear(); });
	keyHandler->addShortcut(KEY_RIGHT, [] { buffers->next(); clear(); });
	keyHandler->addShortcut(KEY_RESIZE, [&h, &w] { getmaxyx(stdscr, h, w); clear(); });

	std::string input;
	int ch = 0;
	while(running)
	{
		ch = getch();
		if(!keyHandler->handle(ch))
		{
			if(ch == KEY_BACKSPACE && input.length() > 0)
				input.pop_back();
			else if(ch >= 32 && ch <= 126)
				input += (char) ch;
			else if(ch == '\n' && input.length() > 0)
			{
				if(input[0] == '/')
				{
					if(!commands->execute(input))
						buffers->append(Buffers::CoreBuffer, "[!] Unrecognized command: " + input + '\n');
				}
				else
					buffers->append(buffers->getCurrent(), input + '\n');

				input.clear();
			}
		}

		mvprintw(0, 0, "%s", buffers->getData(buffers->getCurrent()).c_str());
		mvprintw(h - 1, 0, "[#%d] [Nick] [Receiver] %s", buffers->getCurrent(), input.c_str());

		clrtoeol();
		refresh();
	}

	endwin();
	return 0;
}
