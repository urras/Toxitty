#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <ncurses.h>
#include <memory>

#include "buffers.hpp"
#include "input.hpp"

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
		bool running;
};

extern std::shared_ptr<Interface> interface;

#endif

