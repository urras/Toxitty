#include <iostream>
#include <ncurses.h>

int main(int argc, char *argv[])
{
	initscr();
	raw();
	keypad(stdscr, true);

	int ch = 0;
	bool running = true;
	while(running)
	{
		ch = getch();
		if(ch == KEY_F(1))
		{
			printw("Exiting...\n");
			running = false;
		}
		else
			printw("Key press recv.\n");

		refresh();
	}

	endwin();
	return 0;
}
