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


Objectplacer controls:
==========
 Left-Click move current object
 Middle-Click delete current object
 Right-Click create new object
 NumPad 0 - Save to out.json
 NumPad + - Next object (replaces current)
 NumPad - - Previous object (replaces current)
 Arrow keys: Move current object by 1px
 Numpad *: rotate by +15°
 Numpad /: rotate by -15°
 Comma ,: sets rotation to °0
More documentation coming soon(tm)
