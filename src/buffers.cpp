#include "buffers.hpp"

std::shared_ptr<Buffers> buffers(new Buffers());

Buffers::Buffers()
{
	m_current = Buffers::CoreBuffer;

	for(unsigned int i = 0; i < Buffers::MaxBuffers; ++i)
		m_scroll[i] = -1;
}

Buffers::~Buffers()
{
}

void Buffers::append(unsigned int buffer, const std::string &data)
{
	if(buffer > Buffers::MaxBuffers || data.length() == 0)
		return;

	m_buffer[buffer].push_back(data);
	clear();
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

	m_buffer[buffer].push_back(data);
	clear();
}

void Buffers::erase(unsigned int buffer)
{
	if(buffer > Buffers::MaxBuffers)
		return;

	m_buffer[buffer].clear();
	clear();
}

unsigned int Buffers::getSize(unsigned int buffer)
{
	if(buffer > Buffers::MaxBuffers)
		return 0;

	return m_buffer[buffer].size();
}

std::string Buffers::getData(unsigned int buffer, unsigned int position)
{
	if(buffer > Buffers::MaxBuffers)
		return "";

	if(position > m_buffer[buffer].size() - 1)
		return "";

	return m_buffer[buffer].at(position);
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

void Buffers::prevScroll(unsigned int buffer)
{
	if(buffer > Buffers::MaxBuffers)
		return;

	if(m_scroll[buffer] > 0)
		--m_scroll[buffer];
}

void Buffers::nextScroll(unsigned int buffer)
{
	if(buffer > Buffers::MaxBuffers)
		return;

	if(m_scroll[buffer] < (int) getSize(buffer) - 1)
		++m_scroll[buffer];
	else
		m_scroll[buffer] = -1;
}
