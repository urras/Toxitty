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

#ifndef MISC_HPP
#define MISC_HPP

#include <ctime>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "../tox/core/net_crypto.h"

typedef std::vector<std::string> StringVec;

std::string getTime();
bool verifyKey(const std::string &key);

StringVec split(const std::string &data, const std::string &separator);
std::string join(const StringVec &data, const std::string &separator);

std::string publicKeyToData(const std::string &key);
std::string privateKeyToData(const std::string &key);

std::string dataToPublicKey(const std::string &data);
std::string dataToPrivateKey(const std::string &data);

#endif
