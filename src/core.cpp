#include "core.hpp"

std::shared_ptr<Core> core(new Core());

Core::Core()
{
	m_running = true;
	m_connected = false;
}

Core::~Core()
{
}

void Core::start()
{
	initMessenger();

	buffers->appendf(Buffers::CoreBuffer, "[#] Your public key: %s", dataToPublicKey((char *) self_public_key).c_str());

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

		DHT_bootstrap(data, (unsigned char *) config->getValue("dht.key").c_str());
		// std::thread(std::bind(&Core::thread, this));
	}
}

void Core::thread()
{
	if(!m_connected && DHT_isconnected())
	{
		m_connected = true;
		buffers->append(Buffers::CoreBuffer, "[#] Connected to a DHT node.");
	}
	else if(m_connected && DHT_isconnected() == -1)
	{
		m_connected = false;
		buffers->append(Buffers::CoreBuffer, "[!] Disconnected from a DHT node.");
	}

	doMessenger();
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
