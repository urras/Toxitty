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

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstdlib>
#include <fstream>
#include <map>
#include <memory>
#include <string>

#include <json/reader.h>
#include <json/writer.h>

#include "buffers.hpp"

class Config
{
	public:
		Config();
		~Config();

		bool load();
		bool save();

		void setValue(const std::string &key, const std::string &value);

		std::string getValue(const std::string &key);
		int getIntValue(const std::string &key);
		bool getBoolValue(const std::string &key);

		std::map<std::string, std::string> getValues() const { return m_values; }

	private:
		std::map<std::string, std::string> m_values;
};

extern std::shared_ptr<Config> config;

#endif
