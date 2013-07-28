Toxitty
=======

Toxitty is an experimental CLI based client for Tox. It is written in C++ using the new features of C++11.
Toxitty bases on ncurses library for the user interface, its primary goals are simplicity, flexibility and extensibility.

Compiling
=========
* Compile and install [libsodium](https://github.com/jedisct1/libsodium).
* Compile and install [JsonCpp](http://jsoncpp.sourceforge.net/).
* Clone Toxitty.
* Clone [Tox](https://github.com/irungentoo/ProjectTox-Core) and copy their core directory into /core.
* `# cd Toxitty`
* `# mkdir build`
* `# cd build`
* `# cmake ..`
* `# make`

Features
========
* Simple yet elegant text interface.
* Commands handler.
* Keyboard handler.
* Buffers per chat.
* Input and command history.
* Input per buffer.
* Interactive input bar.

License
=======

Toxitty is released under GPLv3 license, you can find the complete license file in [doc/LICENSE.md](doc/LICENSE.md).

Help
====

You can find a simple FAQ in [doc/HELP.md](doc/HELP.md).

Contribute
==========

If you found a bug you can report it using our [issue tracker](https://github.com/diath/Toxitty/issues).

If you want to contribute some code - fork my repository, commit your changes and send me a pull request!
