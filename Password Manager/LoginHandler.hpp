#ifndef LOGIN_HANDLER_HEADER
#define LOGIN_HANDLER_HEADER

#include <string>
#include "Settings.hpp"
#include "FileManager.hpp"
#include "TemparoryHash.h"


class LoginHandler
{
public:
	static bool verifyLoginValid(char* username, char* password, char* errorMsg);
	static bool doesUserExist(char* username, char* password);
	static void createUser(char* username, char* password);
	static int encryptPassword(char* password);
private:
	static void createLoginLine(char* username, char* password, char** output);
};



#endif