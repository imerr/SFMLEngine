cmake_minimum_required(VERSION 2.8.4)
project(Engine)
set(EXTERNAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external" CACHE STRING "Path to external libs (SFML, Box2D, json-cpp)")
set(SFMLENGINE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "Path to Engine")
message(STATUS "${EXTERNAL_PATH}")
include("includes.cmake")
include("compiler.cmake")
include_directories(${SFMLENGINE_PATH}/include/Engine)

set(JSONCPP_WITH_TESTS OFF CACHE BOOL "Dont want jsoncpp tests")
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "Dont want jsoncpp unit tests to be run")
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "Dont want box2d examples")
set(BOX2D_BUILD_STATIC ON CACHE BOOL "Build box2d as static lib")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build jsoncpp as static lib" FORCE)
add_subdirectory(${EXTERNAL_PATH}/jsoncpp ${CMAKE_CURRENT_BINARY_DIR}/external/jsoncpp/)
add_subdirectory(${EXTERNAL_PATH}/box2d/Box2D ${CMAKE_CURRENT_BINARY_DIR}/external/box2d)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build sfml as shared lib" FORCE)
add_subdirectory(${EXTERNAL_PATH}/SFML ${CMAKE_CURRENT_BINARY_DIR}/external/sfml/)

set(SOURCE_FILES src/Button.cpp
                 src/Factory.cpp
                 src/Game.cpp
                 src/Light.cpp
                 src/LightSystem.cpp
                 src/Node.cpp
                 src/ObjectPlacer.cpp
                 src/ParallaxBackground.cpp
                 src/ParticleSystem.cpp
                 src/ResourceManager.cpp
                 src/Scene.cpp
                 src/LoadingScene.cpp
                 src/Text.cpp
                 src/SpriteNode.cpp
                 src/util/Box2dDebugDraw.cpp
                 src/util/Random.cpp
                 src/util/math.cpp
        src/util/json.cpp)
add_library(Engine STATIC ${SOURCE_FILES})
target_link_libraries(Engine jsoncpp_lib_static
							   Box2D
                               sfml-window
                               sfml-audio
                               sfml-system
                               sfml-network
                               sfml-graphics)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_link_libraries(Engine sfml-main)
endif()
if (ANDROID)
	set(BLA -Wl,--whole-archive sfml-main -Wl,--no-whole-archive)
	target_link_libraries(Engine ${BLA})
endif()