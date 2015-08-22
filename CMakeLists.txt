cmake_minimum_required(VERSION 2.8.4)
project(Engine)
set(EXTERNAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external" CACHE STRING "Path to external libs (SFML, Box2D, json-cpp)")
set(SFMLENGINE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "Path to Engine")
message(STATUS "${EXTERNAL_PATH}")
include("includes.cmake")
# TODO: is this a good idea?
include_directories(${SFMLENGINE_PATH}/include/Engine)
message(STATUS "${INCLUDE_DIRECTORIES}")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "/Zm256 /Gy /GR- /W2 /wd4275 /wd4530 /wd4566 /FS")
	set(CMAKE_CXX_FLAGS_DEBUG "/MDd /DDEBUG /RTCsu /Od /Zi")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/GL /GS- /O2 /MD /fp:fast /DNDEBUG /Zi")
	set(CMAKE_CXX_FLAGS_RELEASE "/GL /GS- /O2 /MD /fp:fast /DNDEBUG")

	set(CMAKE_C_FLAGS "/Zm256 /Gy /W2 /wd4566  /FS")
	set(CMAKE_C_FLAGS_DEBUG "/MDd /DDEBUG /RTCsu /Od /Zi /D_SECURE_SCL=0 /D_HAS_ITERATOR_DEBUGGING=0")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "/GL /GS- /O2 /MD /fp:fast /DNDEBUG /Zi")
	set(CMAKE_C_FLAGS_RELEASE "/GL /GS- /O2 /MD /fp:fast /DNDEBUG")

	#
	# Workaround for "LINK : fatal error LNK1104: cannot open file 'XXX.map'" issue
	# see http://social.msdn.microsoft.com/Forums/en-US/vcprerelease/thread/19804537-05ba-4adf-8273-68d2450401e0
	#

	set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /MAP /OPT:ICF /OPT:REF /INCREMENTAL:NO")
	set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} /MAP /DEBUG /OPT:ICF /OPT:REF /LTCG /INCREMENTAL:NO")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /MAP /OPT:ICF /OPT:REF /LTCG /INCREMENTAL:NO")

	set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /MAP /OPT:ICF /OPT:REF /INCREMENTAL:NO")
	set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} /MAP /OPT:ICF /OPT:REF /LTCG /INCREMENTAL:NO")
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /MAP /OPT:ICF /OPT:REF /LTCG /INCREMENTAL:NO")
else ()
	set(CMAKE_CXX_FLAGS "-Wall -march=pentium4 -mmmx -msse -msse2 -std=c++11 -fno-rtti")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -g")
	set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

	set(CMAKE_C_FLAGS "-Wall -march=pentium4 -mmmx -msse -msse2")
	set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
	set(CMAKE_C_FLAGS_RELEASE "-O2")

	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpmath=sse")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpmath=sse")
	endif ()
endif ()

set(JSONCPP_WITH_TESTS OFF CACHE BOOL "Dont want jsoncpp tests")
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "Dont want jsoncpp unit tests to be run")
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "Dont want box2d examples")
set(BOX2D_BUILD_STATIC ON CACHE BOOL "Build box2d as static lib")
add_subdirectory(${EXTERNAL_PATH}/jsoncpp ${CMAKE_CURRENT_BINARY_DIR}/external/jsoncpp/)
add_subdirectory(${EXTERNAL_PATH}/liquidfun/liquidfun/Box2D ${CMAKE_CURRENT_BINARY_DIR}/external/liquidfun)
add_subdirectory(${EXTERNAL_PATH}/SFML ${CMAKE_CURRENT_BINARY_DIR}/external/sfml/)

set(SOURCE_FILES src/Button.cpp
                 src/Factory.cpp
                 src/Game.cpp
                 src/Light.cpp
                 src/LightSystem.cpp
                 src/Node.cpp
                 src/ObjectPlacer.cpp
                 src/ParticleSystem.cpp
                 src/ResourceManager.cpp
                 src/Scene.cpp
                 src/LoadingScene.cpp
                 src/Text.cpp
                 src/SpriteNode.cpp
                 src/util/Box2dDebugDraw.cpp
                 src/util/Random.cpp
                 src/util/math.cpp
)
add_library(Engine STATIC ${SOURCE_FILES})
target_link_libraries(Engine jsoncpp_lib_static
							   Box2D
                               sfml-window
                               sfml-audio
                               sfml-system
                               sfml-graphics)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_link_libraries(Engine sfml-main)
endif()