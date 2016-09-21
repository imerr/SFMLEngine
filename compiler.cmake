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
    set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -fexceptions -fno-rtti -Wno-unused-value")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
	if (ANDROID) 
		set(CMAKE_SHARED_LINKER_FLAGS  "--sysroot=$ENV{SYSROOT} ${CMAKE_SHARED_LINKER_FLAGS}")
		set(CMAKE_EXE_LINKER_FLAGS  "--sysroot=$ENV{SYSROOT} ${CMAKE_EXE_LINKER_FLAGS}")
	endif()
    set(CMAKE_C_FLAGS "-Wall")
    set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
    set(CMAKE_C_FLAGS_RELEASE "-O2")
endif ()