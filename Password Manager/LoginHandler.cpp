#include "LoginHandler.hpp"

/// <summary>
/// A simple check if the login is valid, not if it exists 
/// 
/// 1. Checks the lengths of the username and password.
/// 2. Checks if the username has only letters and numbers.
/// 3. Checks if the password has only letters, numbers and symbols.
/// </summary>
/// <param name="username">Username</param>
/// <param name="password">Password</param>
/// <param name="errorMsg">The occured error if there is one</param>
/// <returns></returns>
bool LoginHandler::verifyLoginValid(char* username, char* password, char* errorMsg)
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

bool LoginHandler::doesUserExist(char* username, char* password)
{
	char* line = NULL;
	
	createLoginLine(username, password, &line);
	
	bool returnValue = FileManager::isLineInFile(USERS_FILE, line);

	free(line);

	return returnValue;
}

void LoginHandler::createUser(char* username, char* password)
{
	char* line = NULL;

	createLoginLine(username, password, &line);

	FileManager::addToFile(USERS_FILE, line);

	free(line);
}

int LoginHandler::encryptPassword(char* password)
{
	return TemparoryHash::simpleHash(password);
}

void LoginHandler::createLoginLine(char* username, char* password, char** output)
{
	std::string stringPassword = std::to_string(TemparoryHash::simpleHash(password));
	// size based on the username, space, password, \n and \0
	int newLineSize = (strlen(username) + 1 + stringPassword.size() + 1 + 1);

	*output = (char*)malloc(newLineSize * sizeof(char));

	strcpy(*output, username);
	strcpy(*output + strlen(username), " ");
	strcpy(*output + strlen(username) + 1, stringPassword.c_str());

}
