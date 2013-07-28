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

#ifndef INPUT_HPP
#define INPUT_HPP

#include <memory>
#include <string>
#include <vector>

#include "buffers.hpp"

class Input
{
	public:
		Input();
		~Input();

		std::string data[Buffers::MaxBuffers];
		std::vector<std::string> history[Buffers::MaxBuffers];

		void prevCaret(unsigned int buffer);
		void nextCaret(unsigned int buffer);

		void prevHistory(unsigned int buffer);
		void nextHistory(unsigned int buffer);

		int getPosCaret(unsigned int buffer);
		void setPosCaret(unsigned int buffer, int position);

		int getPosHistory(unsigned int buffer);
		void setPosHistory(unsigned int buffer, int position);

	private:
		int m_posHistory[Buffers::MaxBuffers];
		int m_posCaret[Buffers::MaxBuffers];
};

extern std::shared_ptr<Input> input;

#endif
