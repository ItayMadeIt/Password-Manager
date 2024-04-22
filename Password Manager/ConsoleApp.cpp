#include "ConsoleApp.hpp"

void ConsoleApp::printWelcome()
{

	// Simple welcome msg
	printf("Welcome to PASSWORD-MANAGER program (by ItayMadeIt) Your trusted companion in the digital realm.\n");
	printf("Here, your passwords, credit card details, secure notes, and more find a secure home, accessible only to you.\n");
	printf("With our robust encryption, your data remains shielded from any unauthorized access.\n\n");

	// ascii art: https://www.asciiart.eu/text-to-ascii-art
	printf(";-.   ,.   ,-.   ,-.  ,   .  ,-.  ,-.  ,-. \n");
	printf("|  ) /  \\ (   ` (   ` | . | /   \\ |  ) |  \\\n");
	printf("|-'  |--|  `-.   `-.  | | | |   | |-<  |  |\n");
	printf("|    |  | .   ) .   ) |/|/  \\   / |  \\ |  /\n");
	printf("'    '  '  `-'   `-'  ' '    `-'  '  ' `-' \n");
	printf("                                           \n");
	printf(".   ,  ,.  .  .  ,.   ,-. ,--. ,-.         \n");
	printf("|\\ /| /  \\ |\\ | /  \\ /    |    |  )         \n");
	printf("| V | |--| | \\| |--| | -. |-   |-<     \n");
	printf("|   | |  | |  | |  | \\  | |    |  \\      \n");
	printf("'   ' '  ' '  ' '  '  `-' `--' '  '     \n");
	printf("\n");

}

void ConsoleApp::inputOptionMenu(char* username, int* outputOption)
{
	printf("What would you like to do? [%s]\n", username);
	printf(" (%d) Daily tip\n", DAILY_TIP_MENU_OPTION);
	printf(" (%d) Modify data\n", MODIFY_DATA_MENU_OPTION);
	printf(" (%d) Search data\n", SEARCH_DATA_MENU_OPTION);
	printf(" (%d) Exit data\n", EXIT_MENU_OPTION);
	printf(" Enter an option (%d - %d): ", MIN_MENU_OPTION, MAX_MENU_OPTION);

	// gather input
	scanf("%d", outputOption);
	getchar();
	
	while (!(MIN_MENU_OPTION <= *outputOption  && *outputOption <= MAX_MENU_OPTION))
	{
		printf("\t%d is an invalid option\n\ttry again:", *outputOption);
		scanf("%d", outputOption);
		getchar();
	}
	printf("\n");
}

void ConsoleApp::inputLogin(char** username, char** password)
{
	// create memory for the username and password
	*username = (char*)malloc(sizeof(char) * MAX_USERNAME_LENGTH);
	*password = (char*)malloc(sizeof(char) * MAX_PASSWORD_LENGTH);

	// input from user
	printf("Enter profile details (Verification of user)\n");
	printf("Username:\n\t");
	fgets(*username, MAX_USERNAME_LENGTH, stdin);
	(*username)[strcspn(*username, "\n")] = 0;

	printf("password:\n\t");
	fgets(*password, MAX_PASSWORD_LENGTH, stdin);
	(*password)[strcspn(*password, "\n")] = 0;

	// validity of user and input
	while (!LoginHandler::verifyLoginValid(*username, *password, NULL))
	{
		printf("Invalid profile details: \n\tusername: %s\n\tpassword: %s\n", *username, *password);
		printf("Enter profile details (Verification of user)\n");
		printf("Username:\n\t");
		fgets(*username, MAX_USERNAME_LENGTH, stdin);
		(*username)[strcspn(*username, "\n")] = 0;

		printf("password:\n\t");
		fgets(*password, MAX_PASSWORD_LENGTH, stdin);
		(*password)[strcspn(*password, "\n")] = 0;
	}

}

bool ConsoleApp::handleInvalidUser(char* username, char* password)
{
	// User exists
	if (FileManager::strInLineStartFile(USERS_FILE, username))
	{
		printf("Wrong password, try again later... \n");
		return false;
	}

	printf("User is invalid...\n");
	printf("Do you want to create such user with such password? (y/n) ");
	char response = getchar();

	if (response == 'y')
	{
		LoginHandler::createUser(username, password);
		return true;
	}
	
	return false;
}
