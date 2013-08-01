#ifndef CORE_HPP
#define CORE_HPP

#include <memory>

class Core
{
	public:
		Core();
		~Core();

		bool isRunning() const { return m_running; }
		void setRunning(bool running) { m_running = running; }

	private:
		bool m_running;
};

extern std::shared_ptr<Core> core;

#endif
