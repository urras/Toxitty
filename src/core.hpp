#ifndef CORE_HPP
#define CORE_HPP

#include <memory>
#include <string>
#include <boost/thread.hpp>

#include "buffers.hpp"
#include "config.hpp"
#include "misc.hpp"

#include "../tox/core/Messenger.h"
#include "../tox/core/network.h"

class Core
{
	public:
		static const int MaxRequests = 255;

		Core();
		~Core();

		void start();
		void thread();

		bool isRunning() const { return m_running; }
		void setRunning(bool running) { m_running = running; }

		std::string getNick() const { return m_nick; }
		void setNick(const std::string &nick) { m_nick = nick; }

		std::string getStatusMessage() const { return m_statusMessage; }
		void setStatusMessage(const std::string &status) { m_statusMessage = status; }

		USERSTATUS getStatus() const { return m_status; }
		void setStatus(USERSTATUS status) { m_status = status; }

		int getNumRequests() const { return m_numRequests; }
		void setNumRequests(int num) { m_numRequests = num; }

		void addRequest(int request, unsigned char *key);
		bool acceptRequest(int request);

	private:
		bool m_running;
		bool m_connected;

		std::string m_nick;
		std::string m_statusMessage;
		USERSTATUS m_status;

		int m_numRequests;
		unsigned char m_requests[MaxRequests][CLIENT_ID_SIZE];
};

extern std::shared_ptr<Core> core;

#endif
