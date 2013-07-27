#include "misc.hpp"

std::string getTime()
{
	std::stringstream stream;
	time_t rawtime = time(NULL);
	const tm *timestamp = localtime(&rawtime);

	stream << "[" << std::setw(2) << std::setfill('0') << timestamp->tm_hour << ":" << std::setw(2) << std::setfill('0') << timestamp->tm_min << "]";
	return stream.str();
}
