#ifndef INPUT_HPP
#define INPUT_HPP

#include <memory>
#include <string>
#include <vector>

#include "buffers.hpp"

class Input
{
	public:
		Input();
		~Input();

		std::string data[Buffers::MaxBuffers];
		std::vector<std::string> history[Buffers::MaxBuffers];

		void prevCaret(unsigned int buffer);
		void nextCaret(unsigned int buffer);

		void prevHistory(unsigned int buffer);
		void nextHistory(unsigned int buffer);

		int getPosCaret(unsigned int buffer);
		void setPosCaret(unsigned int buffer, int position);

		int getPosHistory(unsigned int buffer);
		void setPosHistory(unsigned int buffer, int position);

	private:
		int m_posHistory[Buffers::MaxBuffers];
		int m_posCaret[Buffers::MaxBuffers];
};

extern std::shared_ptr<Input> input;

#endif
