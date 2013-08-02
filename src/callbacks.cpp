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

#include "callbacks.hpp"

void Callbacks::FriendRequest(unsigned char *key, unsigned char *data, unsigned short length)
{
	int requests = core->getNumRequests();
	core->setNumRequests(requests + 1);
	core->addRequest(requests, key);

	buffers->appendf(Buffers::CoreBuffer, "[#] New friend request received with message: %s", (char *) data);
	buffers->appendf(Buffers::CoreBuffer, "[#] Accept with /accept %d.", requests);
}

void Callbacks::Message(int id, unsigned char *data, unsigned short length)
{
	char name[MAX_NAME_LENGTH];
	getname(id, (unsigned char *) name);

	buffers->appendf(Buffers::CoreBuffer, "[#] <%s> %s", name, data);
}

void Callbacks::NickChange(int id, unsigned char *data, unsigned short length)
{
	char name[MAX_NAME_LENGTH];
	getname(id, (unsigned char *) name);

	buffers->appendf(Buffers::CoreBuffer, "[#] %s is now known as %s.", name, data);
}

void Callbacks::StatusChange(int id, unsigned char *data, unsigned short length)
{
	char name[MAX_NAME_LENGTH];
	getname(id, (unsigned char *) name);

	buffers->appendf(Buffers::CoreBuffer, "[#] %s changed their status to %s", name, data);
}
