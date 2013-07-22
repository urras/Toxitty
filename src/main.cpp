#include "buffers.hpp"
#include "commands.hpp"
#include "keyhandler.hpp"
#include "interface.hpp"
#include "input.hpp"

int main(int argc, char *argv[])
{
	interface->init();

	buffers->append(Buffers::CoreBuffer, "[#] Toxitty v0.1");
	buffers->append(Buffers::CoreBuffer, "[#] Type /help for more information.");

	commands->add("help", "Displays help contents.", Commands::Help);
	commands->add("buffer", "Manages buffer navigation.", Commands::Buffer);
	commands->add("exit", "Exits the client.", Commands::Exit);
	commands->add("quit", "Exits the client.", Commands::Exit);

	keyHandler->addShortcut(KEY_F(1), [] { interface->running = false; });
	keyHandler->addShortcut(KEY_LEFT, [] { buffers->prev(); clear(); });
	keyHandler->addShortcut(KEY_RIGHT, [] { buffers->next(); clear(); });
	keyHandler->addShortcut(KEY_RESIZE, [] { interface->onResize(); clear(); });

	int ch = 0, currentBuffer = 0;
	while(interface->running)
	{
		ch = getch();
		currentBuffer = buffers->getCurrent();

		if(!keyHandler->handle(ch))
		{
			if(ch == KEY_BACKSPACE && input->data[currentBuffer].length() > 0)
				input->data[currentBuffer].pop_back();
			else if(ch >= 32 && ch <= 126)
				input->data[currentBuffer] += (char) ch;
			else if(ch == '\n' && input->data[currentBuffer].length() > 0)
			{
				if(input->data[currentBuffer][0] == '/')
				{
					if(!commands->execute(input->data[currentBuffer]))
						buffers->append(Buffers::CoreBuffer, "[!] Unrecognized command: " + input->data[currentBuffer]);
				}
				else
					buffers->append(currentBuffer, input->data[currentBuffer]);

				input->data[currentBuffer].clear();
			}
		}

		mvprintw(0, 0, "%s", buffers->getData(currentBuffer).c_str());
		mvprintw(interface->height - 1, 0, "[#%d] [Nick] [Receiver] %s\n", currentBuffer, input->data[currentBuffer].c_str());

		interface->clr();
	}

	interface->end();
	return 0;
}
