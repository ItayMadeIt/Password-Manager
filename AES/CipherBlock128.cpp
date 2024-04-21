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

CipherBlock128::CipherBlock128(const unsigned int values[BLOCK_SIZE], const bool isRows)
{
	// if is columns
	if (!isRows)
	{
		for (int i = 0; i < BLOCK_SIZE; i++)
		{
			*(((int*)data) + i) = values[i];
		}

		return;
	}

	// if is rows
	for (int srcRow = 0; srcRow < BLOCK_SIZE; srcRow++)
	{
		int dstRow = BLOCK_SIZE - 1 - srcRow;
		
		for (int srcCol = 0; srcCol < BLOCK_SIZE; srcCol++)
		{
			int dstCol = BLOCK_SIZE - 1 - srcCol;
		
			data[dstCol][dstRow] = (values[srcRow] >> (srcCol * BYTE_TO_BIT));
		}
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
	int index = 0;
	//  for (int i = 0; i < BLOCK_SIZE; i++)
	//  {
	//  	  for (int j = BLOCK_SIZE - 1; j >= 0 ; j--)
	//  	  {
	//  	  	  data[i][j] = values[index++];
	//  	  }
	//  }	  
	//   
	// Created a more efficient but harder loop
	
	for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE; i += BLOCK_SIZE)
	{
		for (int j = BLOCK_SIZE - 1; j >= 0; j--)
		{
			data[0][i + j] = values[index++];
		}
	}
}

void CipherBlock128::printHex()
{
	for (int i = BLOCK_SIZE - 1; i >= 0; i--)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			printf("%02X ", data[j][i]);
		}
		printf("\n");
	}
}

void CipherBlock128::printHexLine()
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		for (int j = BLOCK_SIZE - 1; j >= 0; j--)
		{
			printf("%02X ", data[i][j]);
		}
	}
	printf("\n");
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

int CipherBlock128::getRow(int rowIndex) const
{
	return ((data[0][BLOCK_SIZE - 1 - rowIndex] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 1)) +
			(data[1][BLOCK_SIZE - 1 - rowIndex] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 2)) +
			(data[2][BLOCK_SIZE - 1 - rowIndex] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 3)) +
			(data[3][BLOCK_SIZE - 1 - rowIndex] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 4)));
}
void CipherBlock128::getRowAsChars(int rowIndex, unsigned char row[BLOCK_SIZE]) const
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		row[i] = data[BLOCK_SIZE - 1 - i][BLOCK_SIZE - 1 - rowIndex];
	}
}
int CipherBlock128::shiftRow(int rowIndex, int shift) const
{
	shift &= (BLOCK_SIZE-1); // taking advantage of binary operations to modulo by 4

	return ((data[0][BLOCK_SIZE - 1 - rowIndex] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 1 + shift)) +
		    (data[1][BLOCK_SIZE - 1 - rowIndex] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 2 + shift)) +
		    (data[2][BLOCK_SIZE - 1 - rowIndex] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 3 + shift)) +
		    (data[3][BLOCK_SIZE - 1 - rowIndex] << sizeof(char) * BYTE_TO_BIT * (BLOCK_SIZE - 4 + shift)));
}

int CipherBlock128::getColumn(int columnIndex) const
{
	return *((int*)(data)+columnIndex);
}

void CipherBlock128::getColumnAsChars(int columnIndex, unsigned char column[BLOCK_SIZE]) const
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		column[i] = data[columnIndex][BLOCK_SIZE-1-i];
	}
}

int CipherBlock128::shiftColumn(int columnIndex, int shift) const
{
	int column = *((int*)(data)+columnIndex);

	return (column << BYTE_TO_BIT * BLOCK_SIZE * shift) | (column >> BYTE_TO_BIT * BLOCK_SIZE * (BLOCK_SIZE-shift) );
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

bool operator==(const CipherBlock128& lhs, const CipherBlock128& rhs)
{
	for (int column = 0; column < BLOCK_SIZE; column++)
	{
		if (lhs.getColumn(column) != rhs.getColumn(column))
		{
			return false;
		}
	}

	return true;
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
