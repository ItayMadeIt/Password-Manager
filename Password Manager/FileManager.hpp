#ifndef FILE_MANAGER_HEADER
#define FILE_MANAGER_HEADER

#include <iostream>
#include <cstdio>
#include "Settings.hpp"

#define MAX_LINE_LEN MAX_USERNAME_LENGTH + strlen("4294967294") + 1

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
	static bool strInLineStartFile(const char* fileName, char* str)
	{
		FILE* file = fopen(fileName, "r");

		char* buffer = (char*)malloc(sizeof(char) * MAX_LINE_LEN);

		while (fgets(buffer, MAX_LINE_LEN, file))
		{
			buffer[strcspn(buffer, "\n")] = 0;

			if (strcmp(str, buffer) == 0)
			{
				return true;
			}
		}

		free(buffer);
		fclose(file);

		return false;
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

		free(buffer);
		fclose(file);
	
		return false;
	}

};


#endif