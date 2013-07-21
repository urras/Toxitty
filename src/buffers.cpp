#include "buffers.hpp"

std::shared_ptr<Buffers> buffers(new Buffers());

Buffers::Buffers()
{
	m_current = Buffers::CoreBuffer;
}

Buffers::~Buffers()
{
}

void Buffers::append(unsigned int buffer, const std::string &data)
{
	if(buffer > Buffers::MaxBuffers || data.length() == 0)
		return;

	m_buffer[buffer] << data;

	if(*(data.end() - 1) != '\n')
		m_buffer[buffer] << '\n';
}

void Buffers::appendf(unsigned int buffer, const char *format, ...)
{
	if(buffer > Buffers::MaxBuffers || strlen(format) == 0)
		return;

	char data[1024];
	va_list args;

	va_start(args, format);
	vsprintf(data, format, args);
	va_end(args);

	append(buffer, std::string(data));
}

void Buffers::erase(unsigned int buffer)
{
	if(buffer > Buffers::MaxBuffers)
		return;

	m_buffer[buffer].clear();
}

std::string Buffers::getData(unsigned int buffer)
{
	if(buffer > Buffers::MaxBuffers)
		return "";

	return m_buffer[buffer].str();
}

void Buffers::prev()
{
	if(m_current > 0)
		--m_current;
}

void Buffers::next()
{
	if(m_current < Buffers::MaxBuffers - 1)
		++m_current;
}
