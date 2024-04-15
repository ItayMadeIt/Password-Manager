#include <iostream>
#include "Settings.hpp"
#include "ConsoleApp.hpp"
#include "LoginHandler.hpp"
#include "FileManager.hpp"
#include <random>

void handleMenu(int option);

int main()
{
	
	char* usernameInput = NULL;
	char* passwordInput = NULL;

	ConsoleApp::printWelcome();

	ConsoleApp::inputLogin(&usernameInput, &passwordInput);
	
	if (!LoginHandler::doesUserExist(usernameInput, passwordInput))
	{
		if (!ConsoleApp::handleInvalidUser(usernameInput, passwordInput))
		{
			return 0;
		}
	}
	

	int userOption = 0;
	while (userOption != EXIT_MENU_OPTION)
	{
		ConsoleApp::inputOptionMenu(usernameInput, &userOption);

		handleMenu(userOption);
	}

	printf("Thank you for using the weirdest password manager!\n");

	getchar();

	return 0;
}

void handleMenu(int option)
{
	switch (option)
	{
		case DAILY_TIP_MENU_OPTION:
		{
			printf("There are no tips currently, I'm deeply sorry . . .\n");
			break;
		}
		case MODIFY_DATA_MENU_OPTION:
		{
			printf("There is no modify option yet . . .\n");
			break;
		}
		case SEARCH_DATA_MENU_OPTION:
		{
			printf("There is no search option yet . . .\n");
			break;
		}
		case EXIT_MENU_OPTION:
		{
			break;
		}
		default:
		{
			printf("Should never occur");
		}
	}
}