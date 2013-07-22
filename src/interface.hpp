#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <ncurses.h>
#include <memory>

class Interface
{
	public:
		Interface();
		~Interface();

		void init();
		void draw();
		void clr();
		void end();

		void onResize();

		int width, height;
};

extern std::shared_ptr<Interface> interface;

#endif

