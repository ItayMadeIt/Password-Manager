#include "CipherBlock128.hpp"

CipherBlock128::CipherBlock128() 
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		*((int*)data[i]) = 0;
	}
}

CipherBlock128::CipherBlock128(const unsigned char value)
{
	for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE; i++)
	{
		this->data[0][i] = value;
	}
}

CipherBlock128::CipherBlock128(const int values[BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		*((int*)data[i]) = values[i];
	}
}

CipherBlock128::CipherBlock128(const unsigned char values[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE; i++)
	{
		data[0][i] = values[0][i];
	}
}

CipherBlock128::CipherBlock128(const unsigned char values[BLOCK_SIZE * BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE; i++)
	{
		data[0][i] = values[i];
	}
}

void CipherBlock128::printHex()
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

void CipherBlock128::printBinary()

{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			std::bitset<8> binary(data[i][j]);
			std::cout << binary << " ";
		}
		printf("\n");
	}
}

CipherBlock128 CipherBlock128::operator^(const CipherBlock128& other)

{
	CipherBlock128 result;

	// Perform element-wise addition for each int (because I don't have a 128 bit type int so long is the longest)
	for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE * (sizeof(unsigned char)) / sizeof(int); i++)
	{
		// going over each row of result, and setting it to xor of same row of data and other.data
		*((int*)(result.data[0]) + i) = *((int*)(data[0]) + i) ^ *((int*)(other.data[0]) + i);
	}

	return result;
}

inline std::ostream& operator<<(std::ostream& _stream, CipherBlock128 const& v)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; ++j)
		{
			_stream << std::setw(2) << std::setfill('0') << std::hex
				<< static_cast<unsigned>(v.data[i][j]) << " ";
		}
		_stream << std::endl;
	}
	return _stream;
}
