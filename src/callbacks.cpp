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

	if(strlen((char *) data) == 0)
		buffers->append(Buffers::CoreBuffer, "[#] New friend request received.");
	else
		buffers->appendf(Buffers::CoreBuffer, "[#] New friend request received with message: %s", (char *) data);

	buffers->appendf(Buffers::CoreBuffer, "[#] Accept with /accept %d.", requests);

	if(config->getBoolValue("bell.request"))
		std::cout << "\a" << std::flush;
}

void Callbacks::Message(int id, unsigned char *data, unsigned short length)
{
	char name[MAX_NAME_LENGTH];
	getname(id, (unsigned char *) name);

	int buffer = buffers->getBufferByFriend(id);
	if(buffer == -1)
	{
		buffer = buffers->getFirstFree();
		if(buffer == -1)
		{
			buffers->appendf(Buffers::CoreBuffer, "[!] No free buffers available while receiving a messege from %s.", name);
			return;
		}

		buffers->assign(buffer, id);
		buffers->appendf(Buffers::CoreBuffer, "[#] New conversation started with %s at buffer #%d (/buffer %d to switch).", name, buffer, buffer);
	}

	if(strlen(name) == 0)
		buffers->appendf(buffer, "[%s] <%d> %s", getTime(true).c_str(), id, data);
	else
		buffers->appendf(buffer, "[%s] <%s> %s", getTime(true).c_str(), name, data);

	if(config->getBoolValue("bell.message"))
		std::cout << "\a" << std::flush;
}

void Callbacks::ActionMessage(int id, unsigned char *data, unsigned short length)
{
	char name[MAX_NAME_LENGTH];
	getname(id, (unsigned char *) name);

	int buffer = buffers->getBufferByFriend(id);
	if(buffer == -1)
	{
		buffer = buffers->getFirstFree();
		if(buffer == -1)
		{
			buffers->appendf(Buffers::CoreBuffer, "[!] No free buffers available while receiving a messege from %s.", name);
			return;
		}

		buffers->assign(buffer, id);
		buffers->appendf(Buffers::CoreBuffer, "[#] New conversation started with %s at buffer #%d (/buffer %d to switch).", name, buffer, buffer);
	}

	if(strlen(name) == 0)
		buffers->appendf(buffer, "[%s] * %d %s", getTime(true).c_str(), id, data);
	else
		buffers->appendf(buffer, "[%s] * %s %s", getTime(true).c_str(), name, data);

	if(config->getBoolValue("bell.action"))
		std::cout << "\a" << std::flush;
}

void Callbacks::NickChange(int id, unsigned char *data, unsigned short length)
{
	char name[MAX_NAME_LENGTH];
	getname(id, (unsigned char *) name);

	int buffer = buffers->getBufferByFriend(id);
	if(buffer == -1)
		buffer = Buffers::CoreBuffer;

	if(strlen(name) == 0)
		buffers->appendf((unsigned int) buffer, "[#] %d is now known as %s.", id, data);
	else
		buffers->appendf((unsigned int) buffer, "[#] %s is now known as %s.", name, data);

	if(config->getBoolValue("bell.nick"))
		std::cout << "\a" << std::flush;
}

void Callbacks::StatusChange(int id, USERSTATUS status)
{
	static std::string StatusName[] = {"online", "away", "busy", "invalid"};

	char name[MAX_NAME_LENGTH];
	getname(id, (unsigned char *) name);

	int buffer = buffers->getBufferByFriend(id);
	if(buffer == -1)
		buffer = Buffers::CoreBuffer;

	if(strlen(name) == 0)
		buffers->appendf((unsigned int) buffer, "[#] %d is now %s.", id, StatusName[status].c_str());
	else
		buffers->appendf((unsigned int) buffer, "[#] %s is now %s.", name, StatusName[status].c_str());

	if(config->getBoolValue("bell.status"))
		std::cout << "\a" << std::flush;
}

void Callbacks::StatusMessageChange(int id, unsigned char *data, unsigned short length)
{
	char name[MAX_NAME_LENGTH];
	getname(id, (unsigned char *) name);

	int buffer = buffers->getBufferByFriend(id);
	if(buffer == -1)
		buffer = Buffers::CoreBuffer;

	if(strlen(name) == 0)
		buffers->appendf((unsigned int) buffer, "[#] %d changed their status message to %s", id, data);
	else
		buffers->appendf((unsigned int) buffer, "[#] %s changed their status message to %s", name, data);

	if(config->getBoolValue("bell.status"))
		std::cout << "\a" << std::flush;
}
