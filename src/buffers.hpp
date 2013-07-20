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

		unsigned int getCurrent() const { return m_current; }
		void prev();
		void next();

	private:
		std::stringstream m_buffer[Buffers::MaxBuffers]; 
		unsigned int m_current;
};

extern std::shared_ptr<Buffers> buffers;

#endif
