#include "callbacks.hpp"

void Callbacks::FriendRequest(unsigned char *key, unsigned char *data, unsigned short length)
{
	(void) key;
	(void) data;
	(void) length;
}

void Callbacks::Message(unsigned char *key, unsigned char *data, unsigned short length)
{
	(void) key;
	(void) data;
	(void) length;
}

void Callbacks::NickChange(unsigned char *key, unsigned char *data, unsigned short length)
{
	(void) key;
	(void) data;
	(void) length;
}

void Callbacks::StatusChange(unsigned char *key, unsigned char *data, unsigned short length)
{
	(void) key;
	(void) data;
	(void) length;
}
