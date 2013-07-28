/*
	Toxitty - An experimental Tox client.
	Copyright (C) 2013  Kamil Chojnowski <diath@pyboard.net>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <ncurses.h>
#include <memory>

#include "buffers.hpp"
#include "input.hpp"
#include "misc.hpp"

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

