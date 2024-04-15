#include "LoginHandler.hpp"
#include "TemparoryHash.h"

bool LoginHandler::verifyLogin(char* username, char* password, char* errorMsg)
{
	int usernameLen = strlen(username);
	int passwordLen = strlen(password);

	if (!(MIN_USERNAME_LENGTH <= usernameLen && usernameLen <= MAX_USERNAME_LENGTH)) 
	{
		printf("Username length is invalid\n");
		return false;
	}

	if (!(MIN_PASSWORD_LENGTH <= passwordLen && passwordLen <= MAX_PASSWORD_LENGTH)) 
	{
		printf("Password length is invalid\n");
		return false;
	}

	// Checks if username has only letters or numbers
	for (int i = 0; i < usernameLen; i++)
	{
		if (!((MIN_LOWERCASE <= username[i] && username[i] <= MAX_LOWERCASE) ||
			(MIN_UPPERCASE <= username[i] && username[i] <= MAX_UPPERCASE) ||
			(MIN_NUMBERS <= username[i] && username[i] <= MAX_NUMBERS)))
		{
			printf("Username at %d is invalid: %c\n", i, username[i]);
			return false;
		}
	}

	// Checks if password has only letters, numbers or allowed symbol
	for (int i = 0; i < passwordLen; i++)
	{

		// if has a letter or a number, its good
		if (((MIN_LOWERCASE <= password[i] && password[i] <= MAX_LOWERCASE) ||
			(MIN_UPPERCASE  <= password[i] && password[i] <= MAX_UPPERCASE) ||
			(MIN_NUMBERS    <= password[i] && password[i] <= MAX_NUMBERS  )))
		{
			continue;
		}

		// if the character is a symbol
		if (SYMBOLS.find(password[i]) != std::string::npos)
		{
			continue;
		}

		printf("Password at %d is invalid (not a symbol, letter or number): %c\n", i, password[i]);
		return false;
	}

	return true;
}

int LoginHandler::encryptPassword(char* password)
{
	return TemparoryHash::simpleHash(password);
}
