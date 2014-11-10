cmake_minimum_required(VERSION 2.8.4)
project(SFMLEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/Button.cpp
                 src/Factory.cpp
                 src/Game.cpp
                 src/Light.cpp
                 src/LightSystem.cpp
                 src/Node.cpp
                 src/ParticleSystem.cpp
                 src/ResourceManager.cpp
                 src/Scene.cpp
                 src/SpriteNode.cpp
                 src/util/Box2dDebugDraw.cpp)
add_library(SFMLEngine ${SOURCE_FILES})
