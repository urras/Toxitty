#ifndef BUFFERS_HPP
#define BUFFERS_HPP

#include <memory>
#include <string>
#include <sstream>

class Buffers
{
	public:
		static const unsigned int MaxBuffers = 20;
		static const unsigned int CoreBuffer = 0;

		Buffers();
		~Buffers();

		void append(unsigned int buffer, const std::string &data);
		void erase(unsigned int buffer);
		std::string getData(unsigned int buffer);

	private:
		std::stringstream m_buffer[Buffers::MaxBuffers]; 
};

extern std::shared_ptr<Buffers> buffers;

#endif
