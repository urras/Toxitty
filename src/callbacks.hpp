#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

class Callbacks
{
	public:
		Callbacks() = delete;
		~Callbacks() = delete;

		static void FriendRequest(unsigned char *key, unsigned char *data, unsigned short length);
		static void Message(unsigned char *key, unsigned char *data, unsigned short length);
		static void NickChange(unsigned char *key, unsigned char *data, unsigned short length);
		static void StatusChange(unsigned char *key, unsigned char *data, unsigned short length);
};

#endif

