#ifndef CORE_HPP
#define CORE_HPP

#include <chrono>
#include <memory>
#include <thread>

#include "buffers.hpp"
#include "config.hpp"
#include "misc.hpp"

#include "../tox/core/Messenger.h"
#include "../tox/core/network.h"

class Core
{
	public:
		Core();
		~Core();

		void start();
		void thread();

		bool isRunning() const { return m_running; }
		void setRunning(bool running) { m_running = running; }

	private:
		bool m_running;
		bool m_connected;
};

extern std::shared_ptr<Core> core;

#endif
