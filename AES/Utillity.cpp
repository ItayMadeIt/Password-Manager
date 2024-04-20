#include "Utillity.hpp"

void Utillity128::subBytes(CipherBlock128* data)
{
	for (int i = 0; i < BLOCK_SIZE * BLOCK_SIZE; i++)
	{
		data->data[0][i] = subByte(data->data[0][i]);
	}
}

void Utillity128::shiftRow(CipherBlock128* data)
{
	unsigned int rows[BLOCK_SIZE];

	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		rows[i] = data->shiftRow(i, i);
	}

	*data = CipherBlock128(rows, true);
}

CipherBlock128 Utillity128::mixColumn(CipherBlock128 data)
{
	Utillity128::getConstMatrix();
	return CipherBlock128();
}

CipherBlock128 Utillity128::addRoundKey(CipherBlock128 data, CipherBlock128* keys, int round)
{
	return data ^ keys[round];
}

unsigned int Utillity128::subWord(unsigned int word)
{
	int result = 0;

	result |= subByte( word & 0x000000ff);
	result |= subByte((word & 0x0000ff00) >> BYTE_TO_BIT    ) << BYTE_TO_BIT;
	result |= subByte((word & 0x00ff0000) >> BYTE_TO_BIT * 2) << BYTE_TO_BIT * 2;
	result |= subByte((word & 0xff000000) >> BYTE_TO_BIT * 3) << BYTE_TO_BIT * 3;

	return result;
}


unsigned char Utillity128::subByte(unsigned char byte)
{
	std::pair<unsigned char, unsigned char> pos = byteToPos(byte);

	return PREDEFINED_SBOX[pos.first][pos.second];
}

unsigned short Utillity128::polynomialMultiplyGF28(unsigned char a, unsigned char b)
{
	unsigned short result = 0;
	int index = 0;

	while (b)
	{
		if (b & 0b00000001)
		{
			result ^= a << index;
		}

		index++;
		b >>= 1;
	}

	return result;
}

unsigned char Utillity128::polynomialReduceGF28(unsigned short a)
{
	unsigned short result = a;
	int index = countLeftStartBit(a);
	unsigned short divisor = IRREDUCIBLE_POLYNOMIAL << (index - IRREDUCIBLE_POLYNOMIAL_MAX_BIT);

	while (result > IRREDUCIBLE_POLYNOMIAL)
	{
		if (!(result & 0b1 << index))
		{
			index--;
			divisor >>= 1;
			continue;
		}

		result ^= divisor;
		divisor >>= 1;
		index--;
	}

	return result;
}

int Utillity128::countLeftStartBit(unsigned short value)
{
	int count = 0;

	while (value)
	{
		count++;
		value >>= 1;
	}

	return count;
}

std::pair<unsigned char, unsigned char> Utillity128::byteToPos(unsigned char value)
{
	return { (value & 0xf0) >> BYTE_TO_BIT / 2,  value & 0x0f };
}
