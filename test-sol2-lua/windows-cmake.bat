@ECHO OFF

rem Make the bin dir.
IF EXIST bin (
	rd /s /q bin
)
mkdir bin

rem Make the build dir.
IF EXIST build (
	rd /s /q build
)
mkdir build
cd build

rem Because Windows is a piece of
rem set WINDOWS_LIB_DIR				= "C:\programming\libraries\lib"
rem set WINDOWS_INCLUDE_DIR			= "C:\programming\libraries\include"
rem set WINDOWS_DEPENDENCIES_ROOT	= "C:\programming\dependencies"

cmake -G "Visual Studio 14 2015" -DWINDOWS_DEPENDENCIES_ROOT="C:\programming\dependencies" -DCMAKE_TOOLCHAIN_FILE=C:/programming/dependencies/vcpkg-master/vcpkg-master/scripts/buildsystems/vcpkg.cmake ../
rem cmake -G "Visual Studio 15 2017"  ../source/
rem cmake --build .


cd ..
