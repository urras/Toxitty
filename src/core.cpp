#include "core.hpp"

std::shared_ptr<Core> core(new Core());

Core::Core()
{
	m_running = true;
}

Core::~Core()
{
}
