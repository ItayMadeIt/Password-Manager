#ifndef CIPHER_BLOCK_128_HEADER
#define CIPHER_BLOCK_128_HEADER

const int BLOCK_SIZE = 4;

typedef struct CipherBlock128 
{
	unsigned char data[BLOCK_SIZE][BLOCK_SIZE];

	// taking 32 + 32 + 32 + 32 = 128 bits
	void init(const int values[BLOCK_SIZE ])
	{
		for (int i = 0; i < BLOCK_SIZE; ++i) 
		{
			*((int*)data[i]) = values[i];
		}
	}

	// taking 4 * 4  * 8 = 128 bits
	void init(const unsigned char values[BLOCK_SIZE][BLOCK_SIZE])
	{
		for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE; ++i) 
		{
			data[0][i] = values[0][i];
		}
	}

	// taking (4 * 4) array as bytes, 16 * 8 as bits = 128 bits
	void init(const unsigned char values[BLOCK_SIZE * BLOCK_SIZE])
	{
		for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE; ++i)
		{
			data[0][i] = values[i];
		}
	}

	void printHex()
	{
		for (int i = 0; i < BLOCK_SIZE; i++)
		{
			for (int j = 0; j < BLOCK_SIZE; j++)
			{
				printf("%02X ", data[i][j]);
			}
			printf("\n");
		}
	}


} CipherBlock128;

#endif