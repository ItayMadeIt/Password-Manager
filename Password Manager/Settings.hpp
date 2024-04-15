#ifndef SETTINGS_HEADER
#define SETTINGS_HEADER

// Login Settings
#define MIN_USERNAME_LENGTH 4
#define MAX_USERNAME_LENGTH 20

#define MIN_PASSWORD_LENGTH 4
#define MAX_PASSWORD_LENGTH 16

#define MIN_LOWERCASE 'a'
#define MAX_LOWERCASE 'z'

#define MIN_UPPERCASE 'A'
#define MAX_UPPERCASE 'Z'

#define MIN_NUMBERS '0'
#define MAX_NUMBERS '9'

#define SYMBOLS std::string("!@#$%^&*|")

#define USERS_FILE "Files/User-Records.txt"

// user options

#define MIN_MENU_OPTION DAILY_TIP_MENU_OPTION
#define DAILY_TIP_MENU_OPTION 1
#define MODIFY_DATA_MENU_OPTION 2
#define SEARCH_DATA_MENU_OPTION 3
#define EXIT_MENU_OPTION 4
#define MAX_MENU_OPTION EXIT_MENU_OPTION


#endif