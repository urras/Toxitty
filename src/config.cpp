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

#include "config.hpp"

std::shared_ptr<Config> config(new Config());

Config::Config()
{
}

Config::~Config()
{
}

bool Config::load()
{
	std::ifstream data(getConfigDir() + "config.json");
	Json::Value root;
	Json::Reader reader;

	m_values["bell.request"] = "1";
	m_values["bell.message"] = "1";
	m_values["bell.nick"] = "0";
	m_values["bell.status"] = "0";

	m_values["dht.server"] = "198.46.136.167";
	m_values["dht.port"] = "33445";
	m_values["dht.key"] = "728925473812C7AAC482BE7250BCCAD0B8CB9F737BF3D42ABD34459C1768F854";

	m_values["limit.input"] = "100";
	m_values["limit.buffer"] = "500";

	if(!reader.parse(data, root))
	{
		buffers->append(Buffers::CoreBuffer, "[!] Failed to load the config file, using defaults.");
		return false;
	}

	for(unsigned int i = 0; i < root.size(); ++i)
	{
		const Json::Value node = root[i];
		if(node.isNull() || node.size() != 2)
			continue;

		m_values[node.get("key", "").asString()] = node.get("value", "").asString();
	}

	data.close();
	return true;
}

bool Config::save()
{
	std::ofstream data(getConfigDir() + "config.json");
	Json::Value root;
	Json::StyledWriter writer;

	if(!data.is_open())
	{
		buffers->append(Buffers::CoreBuffer, "[!] Failed to save the config file.");
		return false;
	}

	int counter = 0;
	for(std::map<std::string, std::string>::iterator it = m_values.begin(); it != m_values.end(); ++it, ++counter)
	{
		Json::Value node;
		node["key"] = it->first;
		node["value"] = it->second;

		root[counter] = node;
	}

	data << writer.write(root);
	return true;
}

void Config::setValue(const std::string &key, const std::string &value)
{
	m_values[key] = value;
}

std::string Config::getValue(const std::string &key)
{
	std::map<std::string, std::string>::iterator it = m_values.find(key);
	if(it != m_values.end())
		return it->second;

	return "";
}

int Config::getIntValue(const std::string &key)
{
	std::string value = getValue(key);
	if(value.empty())
		return -1;

	return atoi(value.c_str());
}

bool Config::getBoolValue(const std::string &key)
{
	return getIntValue(key) != 0;
}
