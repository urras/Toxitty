#ifndef KEYHANDLER_HPP
#define KEYHANDLER_HPP

#include <functional>
#include <map>
#include <memory>

class KeyHandler
{
	public:
		KeyHandler();
		~KeyHandler();

		bool handle(int character);

		bool addShortcut(int character, std::function<void()> func);
		bool delShortcut(int character);

	private:
		std::map<int, std::function<void()>> m_shortcuts;
	
};

extern std::shared_ptr<KeyHandler> keyHandler;

#endif

