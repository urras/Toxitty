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

#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include "../tox/core/Messenger.h"
#include "../tox/core/network.h"

#include "buffers.hpp"
#include "core.hpp"

class Callbacks
{
	public:
		Callbacks() = delete;
		~Callbacks() = delete;

		static void FriendRequest(unsigned char *key, unsigned char *data, unsigned short length);
		static void Message(int id, unsigned char *data, unsigned short length);
		static void ActionMessage(int id, unsigned char *data, unsigned short length);
		static void NickChange(int id, unsigned char *data, unsigned short length);
		static void StatusChange(int id, USERSTATUS status);
		static void StatusMessageChange(int id, unsigned char *data, unsigned short length);
};

#endif

