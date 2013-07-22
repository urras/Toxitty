#ifndef INPUT_HPP
#define INPUT_HPP

#include <memory>
#include <string>

#include "buffers.hpp"

class Input
{
	public:
		Input();
		~Input();

		std::string data[Buffers::MaxBuffers];
};

extern std::shared_ptr<Input> input;

#endif
