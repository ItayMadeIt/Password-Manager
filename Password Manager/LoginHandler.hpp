#ifndef LOGIN_HANDLER_HEADER
#define LOGIN_HANDLER_HEADER

#include <string>
#include "Settings.hpp"


class LoginHandler
{
public:
	static bool verifyLogin(char* username, char* password, char* errorMsg);
	static int encryptPassword(char* password);

};



#endif