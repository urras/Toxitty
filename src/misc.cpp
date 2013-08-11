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

std::string getTime(bool seconds)
{
	std::stringstream stream;
	time_t rawtime = time(NULL);
	const tm *timestamp = localtime(&rawtime);

	stream << std::setw(2) << std::setfill('0') << timestamp->tm_hour << ':' << std::setw(2) << std::setfill('0') << timestamp->tm_min;

	if(seconds)
		stream << ':' << std::setw(2) << std::setfill('0') << timestamp->tm_sec;

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

StringVec split(const std::string &data, const std::string &separator)
{
	StringVec ret;

	if(data.empty())
		return ret;

	size_t start = 0, end = 0;

	while((end = data.find(separator, start)) != std::string::npos)
	{
		ret.push_back(data.substr(start, end - start));
		start = end + separator.size();
	}

	ret.push_back(data.substr(start));
	return ret;
}

std::string join(const StringVec &data, const std::string &separator)
{
	std::string ret;

	if(data.empty())
		return ret;

	for(const auto &str : data)
	{
		ret += str;
		ret += separator;
	}

	for(size_t i = 0; i < separator.length(); ++i)
		ret.pop_back();

	return ret;
}

std::string publicKeyToData(const std::string &key)
{
	std::string ret;

	const char *characters = key.c_str();
	int i = 0, length = key.length();

	if(length != crypto_box_PUBLICKEYBYTES * 2)
		return ret;

	char bytes[3] = {0, 0, 0};
	unsigned char byte = 0;
	while(i < length)
	{
		bytes[0] = characters[i++];
		bytes[1] = characters[i++];

		byte = strtoul(bytes, NULL, 16);
		ret += byte;
	}

	return ret;
}

std::string privateKeyToData(const std::string &key)
{
	std::string ret;

	const char *characters = key.c_str();
	int i = 0, length = key.length();

	if(length != crypto_box_SECRETKEYBYTES * 2)
		return ret;

	char bytes[3] = {0, 0, 0};
	unsigned char byte = 0;
	while(i < length)
	{
		bytes[0] = characters[i++];
		bytes[1] = characters[i++];

		byte = strtoul(bytes, NULL, 16);
		ret += byte;
	}

	return ret;
}

std::string dataToPublicKey(unsigned char *data)
{
	std::string ret;

	char buffer[255];
	for(unsigned int i = 0; i < crypto_box_PUBLICKEYBYTES; ++i)
	{
		sprintf(buffer, "%02X", data[i]);
		ret += buffer;
	}

	return ret;
}

std::string dataToPrivateKey(unsigned char *data)
{
	std::string ret;

	char buffer[255];
	for(unsigned int i = 0; i < crypto_box_SECRETKEYBYTES; ++i)
	{
		sprintf(buffer, "%02X", data[i]);
		ret += buffer;
	}

	return ret;
}

std::string getConfigDir()
{
	std::string ret;
	struct passwd *pw = getpwuid(getuid());

	ret += pw->pw_dir;
	ret += "/.config/toxitty/";

	mkdir(ret.c_str(), 0700);

	return ret;
}
