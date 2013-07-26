#ifndef BUFFERS_HPP
#define BUFFERS_HPP

#include <cstdarg>
#include <cstring>
#include <memory>
#include <curses.h>
#include <string>
#include <vector>

class Buffers
{
	public:
		static const unsigned int MaxBuffers = 20;
		static const unsigned int CoreBuffer = 0;

		Buffers();
		~Buffers();

		void append(unsigned int buffer, const std::string &data);
		void appendf(unsigned int buffer, const char *format, ...);
		void erase(unsigned int buffer);

		unsigned int getSize(unsigned int buffer);
		std::string getData(unsigned int buffer, unsigned int position);

		unsigned int getCurrent() const { return m_current; }
		void setCurrent(unsigned int current) { if(current > 0 && current < Buffers::MaxBuffers) m_current = current; }

		void prev();
		void next();

	private:
		std::vector<std::string> m_buffer[Buffers::MaxBuffers];
		unsigned int m_current;
};

extern std::shared_ptr<Buffers> buffers;

#endif
