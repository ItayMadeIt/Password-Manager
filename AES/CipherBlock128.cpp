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
			printf("%02X ", data[j][i]);
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
			std::bitset<8> binary(data[j][i]);
			std::cout << binary << " ";
		}
		printf("\n");
	}
}

int CipherBlock128::getRow(int row)
{
	return ((data[0][row] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 1)) +
		(data[1][row] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 2)) +
		(data[2][row] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 3)) +
		(data[3][row] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 4)));
}
int CipherBlock128::shiftRow(int row, int shift)
{
	return ((data[0][row] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 1 + shift)) +
		    (data[1][row] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 2 + shift)) +
		    (data[2][row] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 3 + shift)) +
		    (data[3][row] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 4 + shift)));
}

int CipherBlock128::getColumn(int column)
{
	int revColumn = *((int*)(data)+column);

	unsigned char b0 = (revColumn >> BYTE_TO_BIT * 0) & 0xFF; // Byte 0
	unsigned char b1 = (revColumn >> BYTE_TO_BIT * 1) & 0xFF; // Byte 1
	unsigned char b2 = (revColumn >> BYTE_TO_BIT * 2) & 0xFF; // Byte 2
	unsigned char b3 = (revColumn >> BYTE_TO_BIT * 3) & 0xFF; // Byte 3

	return (b0 << BYTE_TO_BIT * 3) | (b1 << BYTE_TO_BIT * 2) | (b2 << BYTE_TO_BIT * 1) | b3;
}

int CipherBlock128::shiftColumn(int column, int shift)
{
	int revColumn = *((int*)(data)+column);

	unsigned char b0 = (revColumn >> BYTE_TO_BIT * 0) & 0xFF; // Byte 0
	unsigned char b1 = (revColumn >> BYTE_TO_BIT * 1) & 0xFF; // Byte 1
	unsigned char b2 = (revColumn >> BYTE_TO_BIT * 2) & 0xFF; // Byte 2
	unsigned char b3 = (revColumn >> BYTE_TO_BIT * 3) & 0xFF; // Byte 3

	return (b0 << BYTE_TO_BIT * (BLOCK_SIZE + shift + 3)) | 
		   (b1 << BYTE_TO_BIT * (BLOCK_SIZE + shift + 2)) | 
		   (b2 << BYTE_TO_BIT * (BLOCK_SIZE + shift + 1)) | 
		   (b3 << BYTE_TO_BIT * (BLOCK_SIZE + shift + 0));
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
