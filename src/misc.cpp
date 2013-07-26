#include "misc.hpp"

std::string getTime()
{
	std::stringstream stream;
	time_t rawtime = time(NULL);
	const tm *timestamp = localtime(&rawtime);

	stream << "[" << timestamp->tm_hour << ":" << timestamp->tm_min << "]";
	return stream.str();
}
