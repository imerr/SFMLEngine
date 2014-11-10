SFMLEngine
==========
A simple game engine based on SFML & Box2D.
Implements dynamic light and some other stuff

Made for my (iMers) convenience

Compiling
==========
Uses cmake now, so just generate a makefile for the toolchain of your choosing.. or just add all the files to your ide and it'll work too.

It needs a C++11 compatible compiler and makes use of std::thread, so 'default' MinGW [wont work](http://stackoverflow.com/questions/21211980/mingw-error-thread-is-not-a-member-of-std).

Usage
==========
Link the engine, SFML, Box2D and json-cpp, inherit game, create a scene and other stuff and enjoy!


More documentation coming soon(tm)
