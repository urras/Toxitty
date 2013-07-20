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
	if(buffer > Buffers::MaxBuffers)
		return;

	m_buffer[buffer] << data;
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
