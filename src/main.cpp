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

	buffers->append(Buffers::CoreBuffer, "[#] Toxitty v0.1");
	buffers->append(Buffers::CoreBuffer, "[#] Type /help for more information.");

	commands->add("help", Commands::Help);

	keyHandler->addShortcut(KEY_F(1), [&running] { running = false; });
	keyHandler->addShortcut(KEY_LEFT, [] { buffers->prev(); clear(); });
	keyHandler->addShortcut(KEY_RIGHT, [] { buffers->next(); clear(); });
	keyHandler->addShortcut(KEY_RESIZE, [&h, &w] { getmaxyx(stdscr, h, w); clear(); });

	std::string input[Buffers::MaxBuffers];
	int ch = 0, currentBuffer = 0;
	while(running)
	{
		ch = getch();
		currentBuffer = buffers->getCurrent();

		if(!keyHandler->handle(ch))
		{
			if(ch == KEY_BACKSPACE && input[currentBuffer].length() > 0)
				input[currentBuffer].pop_back();
			else if(ch >= 32 && ch <= 126)
				input[currentBuffer] += (char) ch;
			else if(ch == '\n' && input[currentBuffer].length() > 0)
			{
				if(input[currentBuffer][0] == '/')
				{
					if(!commands->execute(input[currentBuffer]))
						buffers->append(Buffers::CoreBuffer, "[!] Unrecognized command: " + input[currentBuffer]);
				}
				else
					buffers->append(currentBuffer, input[currentBuffer]);

				input[currentBuffer].clear();
			}
		}

		mvprintw(0, 0, "%s", buffers->getData(currentBuffer).c_str());
		mvprintw(h - 1, 0, "[#%d] [Nick] [Receiver] %s\n", currentBuffer, input[currentBuffer].c_str());

		clrtoeol();
		refresh();
	}

	endwin();
	return 0;
}
