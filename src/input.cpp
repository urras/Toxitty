#include "input.hpp"

std::shared_ptr<Input> input(new Input());

Input::Input()
{
	for(unsigned int i = 0; i < Buffers::MaxBuffers; ++i)
	{
		m_posHistory[i] = -1;
	}
}

Input::~Input()
{
}

void Input::prevHistory(unsigned int buffer)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return;

	if(history[buffer].size() == 0)
		return;

	if(m_posHistory[buffer] == -1)
		m_posHistory[buffer] = history[buffer].size() - 1;
	else if(m_posHistory[buffer] > 0)
		--m_posHistory[buffer];

	data[buffer] = history[buffer].at(m_posHistory[buffer]);
}

void Input::nextHistory(unsigned int buffer)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return;

	if(history[buffer].size() == 0)
		return;

	if(m_posHistory[buffer] < (int) history[buffer].size() - 1)
		++m_posHistory[buffer];

	data[buffer] = history[buffer].at(m_posHistory[buffer]);
}

int Input::getPosHistory(unsigned int buffer)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return -1;

	return m_posHistory[buffer];
}

void Input::setPosHistory(unsigned int buffer, int position)
{
	if(buffer < 0 || buffer > Buffers::MaxBuffers)
		return;

	m_posHistory[buffer] = position;
}