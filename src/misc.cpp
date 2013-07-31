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

#include "misc.hpp"

std::string getTime()
{
	std::stringstream stream;
	time_t rawtime = time(NULL);
	const tm *timestamp = localtime(&rawtime);

	stream << "[" << std::setw(2) << std::setfill('0') << timestamp->tm_hour << ":" << std::setw(2) << std::setfill('0') << timestamp->tm_min << "]";
	return stream.str();
}

bool verifyKey(const std::string &key)
{
	if(key.length() != 64)
		return false;

	char value = 0;
	for(int i = 0; i < 64; ++i)
	{
		value = key[i];
		if(value >= '0' && value <= '9')
			continue;

		if(value >= 'A' && value <= 'F')
			continue;

		if(value >= 'a' && value <= 'f')
			continue;

		return false;
	}

	return true;
}
