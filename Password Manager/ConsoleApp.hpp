#ifndef CONSOLE_APP_HEADER
#define CONSOLE_APP_HEADER


#include <iostream>
#include "Settings.hpp"
#include "LoginHandler.hpp"

class ConsoleApp {
public:
	static void printWelcome();
	static void inputOptionMenu(char* username, int* outputOption);
	static void inputLogin(char** username, char** password);

};


#endif