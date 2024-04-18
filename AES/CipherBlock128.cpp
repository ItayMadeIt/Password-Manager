#include "CipherBlock128.hpp"

CipherBlock128::CipherBlock128() {}

CipherBlock128::CipherBlock128(const int values[BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; ++i)
	{
		*((int*)data[i]) = values[i];
	}
}

CipherBlock128::CipherBlock128(const unsigned char values[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE; ++i)
	{
		data[0][i] = values[0][i];
	}
}

CipherBlock128::CipherBlock128(const unsigned char values[BLOCK_SIZE * BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE; ++i)
	{
		data[0][i] = values[i];
	}
}
