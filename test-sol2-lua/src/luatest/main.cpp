/*
 * main.cpp
 */

#include <iostream>
#include <exception>
using std::cout;

#include "sol.hpp"

//Inline C++ call to just print out a string or something (basic integration test).
void unitTestOne(sol::state& lua)
{
	cout << "\n*****Unit Test 1*****\n";
	cout << "simple inline print script\n\n";

	lua.script("print('bark bark bark!')");
	cout << "\n\n*********************\n";
}

//Execute an actual script file, foo.lua.
void unitTestTwo(sol::state& lua)
{
	cout << "\n*****Unit Test 2*****\n";

	try
	{
		cout << "calling script file unit_Test_2.lua\n\n";

		lua.script_file("unit_test_2.lua");
	}
	catch(const sol::error& e)
	{
		cout << "\ncaught sol exception in unitTestTwo: \n\"" << e.what() << "\"\n";
	}
	catch(const std::exception& e)
	{
		cout << "\ncaught std exception in unitTestTwo: \n\"" << e.what() << "\"\n";
	}
	catch(...)
	{
		cout << "\nSome exception or other caught in unitTestTwo() (mumble mumble)\n";
	}

	cout << "\n\n*********************\n";
}

int main(int argc, char** argv)
{
	sol::state lua;

	lua.open_libraries(sol::lib::base, sol::lib::io);

	cout << "Potato.\n";

	unitTestOne(lua);
	unitTestTwo(lua);

	return 0;
}
