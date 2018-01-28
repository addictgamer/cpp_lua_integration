/*
 * main.cpp
 */

#include <iostream>
using std::cout;

#include <luajit-2.0/lua.hpp>

int main(int argc, char** argv)
{
	lua_State *lua = lua_open();

	cout << "Potato.\n";

	luaL_openlibs(lua);

	luaL_dofile(lua, "foo.lua");

	lua_close(lua);

	return 0;
}
