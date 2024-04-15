#ifndef TEMP_HASH_HEADER
#define TEMP_HASH_HEADER

#include <random>
class TemparoryHash
{
public:


	static const int HASH_PARTS = 10000;

	static unsigned int simpleHash(const char* str)
	{
		int seed = strlen(str);
		for (int i = 0; i < strlen(str); i++)
		{
			seed += str[i];
		}
		srand(seed);


		unsigned int value = 0;
		for (int i = 0; i < HASH_PARTS; i++)
		{
			value += rand() * HASH_PARTS;
		}

		return value;
	}
};

#endif