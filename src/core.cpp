#include "core.hpp"

std::shared_ptr<Core> core(new Core());

Core::Core()
{
	m_running = true;
	m_connected = false;

	m_numRequests = 0;
}

Core::~Core()
{
}

void Core::start()
{
	initMessenger();

	buffers->appendf(Buffers::CoreBuffer, "[#] ID: %s", dataToPublicKey((char *) self_public_key).c_str());

	IP_Port data;
	data.port = htons(config->getIntValue("dht.port"));

	int resolved = resolve_addr(config->getValue("dht.server").c_str());
	if(resolved == -1)
	{
		buffers->appendf(Buffers::CoreBuffer, "[!] Failed to resolve DHT server address (%s).", config->getValue("dht.server").c_str());
	}
	else
	{
		data.ip.i = resolved;

		DHT_bootstrap(data, (unsigned char *) publicKeyToData(config->getValue("dht.key")).c_str());
		boost::thread(boost::bind(&Core::thread, this));
	}
}

void Core::thread()
{
	while(m_running)
	{
		if(!m_connected && DHT_isconnected())
		{
			m_connected = true;

			std::string nick = config->getValue("nick");
			setname((unsigned char *) nick.c_str(), nick.length());
			core->setNick(nick);

			std::string status = config->getValue("status");
			m_set_userstatus((unsigned char *) status.c_str(), status.length());
			core->setStatus(status);

			buffers->append(Buffers::CoreBuffer, "[#] Connected to a DHT node.");
		}
		else if(m_connected && !DHT_isconnected())
		{
			m_connected = false;
			buffers->append(Buffers::CoreBuffer, "[!] Disconnected from a DHT node.");
		}

		doMessenger();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
}

void Core::addRequest(int request, unsigned char *key)
{
	memcpy(m_requests[request], key, CLIENT_ID_SIZE);
}

bool Core::acceptRequest(int request)
{
	return (m_addfriend_norequest(m_requests[request]) != -1);
}
