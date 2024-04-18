#ifndef CIPHER_BLOCK_128_HEADER
#define CIPHER_BLOCK_128_HEADER

#include <iostream>
#include <bitset>
#include<iomanip>
#include<sstream>

const int BLOCK_SIZE = 4;

class CipherBlock128 
{
public:
	unsigned char data[BLOCK_SIZE][BLOCK_SIZE];

	CipherBlock128();
	CipherBlock128(const int values[BLOCK_SIZE]);
	CipherBlock128(const unsigned char values[BLOCK_SIZE][BLOCK_SIZE]);
	CipherBlock128(const unsigned char values[BLOCK_SIZE * BLOCK_SIZE]);

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
	void printBinary()
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

	// xor operation
	CipherBlock128 operator^(const CipherBlock128& b)
	{
		CipherBlock128 result;

		// Perform element-wise addition for row as int
		for (int i = 0; i < BLOCK_SIZE; i++) 
		{
			*(int*)(result.data[0] + i) = *(int*)(data[0] + i) ^ *(int*)(b.data[0] + i);
		}

		return result;
	}

	friend inline std::ostream& operator<<(std::ostream& _stream, CipherBlock128 const& v) {
		for (int i = 0; i < BLOCK_SIZE; i++)
		{
			for (int j = 0; j < BLOCK_SIZE; ++j) {
				_stream << std::setw(2) << std::setfill('0') << std::hex
					<< static_cast<unsigned>(v.data[i][j]) << " ";
			}
			_stream << std::endl;
		}
		return _stream;
	}
};

#endif