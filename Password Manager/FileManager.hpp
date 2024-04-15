#ifndef FILE_MANAGER_HEADER
#define FILE_MANAGER_HEADER

#include <iostream>
#include <cstdio>
#include "Settings.hpp"

#define MAX_LINE_LEN std::max(MAX_USERNAME_LENGTH, MAX_PASSWORD_LENGTH) + 1

class FileManager
{
public:
	static void addToFile(const char* fileName, char* addition)
	{
		FILE* file = fopen(fileName, "a");
		if (file == NULL)
		{
			return;
		}


		fprintf(file, "%s\n", addition);

		fclose(file);
	}
	static bool isLineInFile(const char* fileName, char* line)
	{
		FILE* file = fopen(fileName, "r");

		char* buffer = (char*)malloc(sizeof(char) * MAX_LINE_LEN);

		while (fgets(buffer, MAX_LINE_LEN, file))
		{
			buffer[strcspn(buffer, "\n")] = 0;

			if (strcmp(buffer, line) == 0)
			{
				return true;
			}
		}

		fclose(file);
	
		return false;
	}

};


#endif