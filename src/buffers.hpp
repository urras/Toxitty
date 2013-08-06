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

#ifndef BUFFERS_HPP
#define BUFFERS_HPP

#include <cstdarg>
#include <cstring>
#include <memory>
#include <curses.h>
#include <string>
#include <vector>

#include "../tox/core/Messenger.h"
#include "../tox/core/network.h"

class Buffers
{
	public:
		static const unsigned int MaxBuffers = 100;
		static const unsigned int CoreBuffer = 0;

		Buffers();
		~Buffers();

		void append(unsigned int buffer, const std::string &data);
		void appendf(unsigned int buffer, const char *format, ...);
		void erase(unsigned int buffer);

		int getFirstFree() const;
		int getBufferByFriend(int id);
		int getFriendByBuffer(unsigned int buffer);

		std::string getName(unsigned int buffer);

		void assign(unsigned int buffer, int id);

		unsigned int getSize(unsigned int buffer);
		std::string getData(unsigned int buffer, unsigned int position);

		unsigned int getCurrent() const { return m_current; }
		void setCurrent(unsigned int current) { if(current >= 0 && current < Buffers::MaxBuffers) m_current = current; }

		void prev();
		void next();

	private:
		std::vector<std::string> m_buffer[Buffers::MaxBuffers];
		unsigned int m_current;
		int m_assign[Buffers::MaxBuffers];
};

extern std::shared_ptr<Buffers> buffers;

#endif
