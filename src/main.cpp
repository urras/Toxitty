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
	commands->add("commands", "Lists available commands.", Commands::CommandsList);

	keyHandler->addShortcut(KEY_F(1), [] { interface->running = false; });
	keyHandler->addShortcut(KEY_UP, [] { input->prevHistory(buffers->getCurrent()); clear(); });
	keyHandler->addShortcut(KEY_DOWN, [] { input->nextHistory(buffers->getCurrent()); clear(); });
	keyHandler->addShortcut(KEY_LEFT, [] { input->prevCaret(buffers->getCurrent()); clear(); });
	keyHandler->addShortcut(KEY_RIGHT, [] { input->nextCaret(buffers->getCurrent()); clear(); });
	keyHandler->addShortcut(KEY_RESIZE, [] { interface->onResize(); clear(); });

	int ch = 0;
	unsigned int currentBuffer = 0;

	while(interface->running)
	{
		ch = getch();
		currentBuffer = buffers->getCurrent();

		if(!keyHandler->handle(ch))
		{
			if(ch == KEY_BACKSPACE && input->data[currentBuffer].length() > 0)
				input->data[currentBuffer].pop_back();
			else if(ch >= 32 && ch <= 126)
			{
				int position = input->getPosCaret(currentBuffer);
				if(position == -1)
					input->data[currentBuffer] += (char) ch;
				else
					input->data[currentBuffer].insert(position, 1, (char) ch);
			}
			else if(ch == '\n' && input->data[currentBuffer].length() > 0)
			{
				if(input->data[currentBuffer][0] == '/')
				{
					if(!commands->execute(input->data[currentBuffer]))
						buffers->append(Buffers::CoreBuffer, "[!] Unrecognized command: " + input->data[currentBuffer]);
				}
				else
				{
					if(currentBuffer == Buffers::CoreBuffer)
						buffers->append(Buffers::CoreBuffer, "[!] You can only send commands to the core buffer.");
					else
						buffers->append(currentBuffer, input->data[currentBuffer]);
				}

				input->history[currentBuffer].push_back(input->data[currentBuffer]);
				input->setPosHistory(currentBuffer, -1);
				input->setPosCaret(currentBuffer, -1);

				input->data[currentBuffer].clear();
			}
		}

		interface->draw();
		interface->clr();
	}

	interface->end();
	return 0;
}
