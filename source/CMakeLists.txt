# All rights reserved.

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(lua)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

IF ( NOT CMAKE_BUILD_TYPE )
	SET(CMAKE_BUILD_TYPE Release)
ENDIF ( NOT CMAKE_BUILD_TYPE )

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

SET(Windows 0)
SET(Linux 0)
IF ( NOT WINDOWS_DEPENDENCIES_ROOT )	#Otherwise will complain an unused local variable was passed in to CMake.
	SET(WINDOWS_DEPENDENCIES_ROOT "")
ENDIF ()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

#Fixes for different platforms & compilers.
SET(NOT_DWORD_DEFINED 0)

IF ( NOT WIN32 )
	#Global Linux/BSD/Mac/OSX flags. But only Linux is supported!
	SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -pg -ffast-math -funroll-loops -fstrict-aliasing")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pg")
	SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math -funroll-loops -fstrict-aliasing")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

	#Linux specific.
	SET(Linux 1) #Should not assume this. What if BSD/DOS/whatever-have-you? Too bad, we're assuming this.
	SET(NOT_DWORD_DEFINED 1)
	IF ( NOT DISABLE_MALIGN_DOUBLE ) #Only compile with -malign-double if not told to disable. Pass via command line flags.
		SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -malign-double")
		SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -malign-double")
	ENDIF ()
	SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -rdynamic -Wl,-rpath=$ORIGIN")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -rdynamic -Wl,-rpath=$ORIGIN")
	SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wl,-rpath=$ORIGIN -Wno-write-strings")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wl,-rpath=$ORIGIN -Wno-write-strings")
ELSE () #Windows
  SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -pg -O3 -ffast-math -funroll-loops -malign-double -fstrict-aliasing -mwindows")
  SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math -funroll-loops -malign-double -fstrict-aliasing -mwindows")
  SET(Windows 1)
ENDIF ()

IF ( ARCHITECTURE )
	SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mcpu=${ARCHITECTURE}")
	SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_DEBUG} -mcpu=${ARCHITECTURE}")
ENDIF ( ARCHITECTURE )

SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS}")


#Find packages.
IF ( WIN32 )
	#Windows
	FIND_PACKAGE(LuaJIT REQUIRED)
ELSE ( NOT WIN32 )
	#Linux.
	FIND_PACKAGE(LuaJIT REQUIRED)
ENDIF ()

#Include directories.
IF ( WIN32 )
	#INCLUDE_DIRECTORIES(${WHATEVER_INCLUDE_DIRS})
	INCLUDE_DIRECTORIES(${LUAJIT_INCLUDE_DIR})
ELSE ()
	#INCLUDE_DIRECTORIES(${WHATEVER_INCLUDE_DIRS})
	INCLUDE_DIRECTORIES(${LUAJIT_INCLUDE_DIR})
	MESSAGE("LUAJIT Include dir: " ${LUAJIT_INCLUDE_DIR})
ENDIF ()

#Library directories.
IF ( WIN32 )
	#LINK_DIRECTORIES(${WHATEVER_LINK_DIRS})
ELSE ()
	#LINK_DIRECTORIES(${WHATEVER_LINK_DIRS})
ENDIF ()

#Include definitions from dependencies.
IF ( WIN32 )
	#ADD_DEFINITIONS(${WHATEVER_FLAGS_INCLUDES})
ELSE ()
	#ADD_DEFINITIONS(${WHATEVER_FLAGS_INCLUDES})
ENDIF ()


CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/src/Config.hpp.in" "${PROJECT_SOURCE_DIR}/src/Config.hpp")

MESSAGE("***************************")
MESSAGE("Debug flags: ")
MESSAGE("${CMAKE_C_FLAGS_DEBUG}")
MESSAGE("${CMAKE_CXX_FLAGS_DEBUG}")
MESSAGE("Release flags: ")
MESSAGE("${CMAKE_C_FLAGS_RELEASE}")
MESSAGE("${CMAKE_CXX_FLAGS_RELEASE}")
MESSAGE("***************************")


#Source-code files.
ADD_SUBDIRECTORY(src)

IF ( WIN32 )
ELSE ()
	IF ( "${CMAKE_SIZEOF_VOID_P}" EQUAL "8" )
		# 64 bit
	ELSE ()
		#This would be 32 bit...unsupported!
		MESSAGE(FATAL_ERROR "32-bit Linux build unsupported!")
	ENDIF ()
ENDIF()
