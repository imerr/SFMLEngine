cmake_minimum_required(VERSION 2.8.4)
project(SFMLEngine)
# TODO: c++11 for non-visual c++ compilers

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
                 src/util/Box2dDebugDraw.cpp
                 src/util/Random.cpp
)
add_library(SFMLEngine STATIC ${SOURCE_FILES})
