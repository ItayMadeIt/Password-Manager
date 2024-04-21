#ifndef UTILLITY_128_HEADER
#define UTILLITY_128_HEADER

#include "CipherBlock128.hpp"
#include "SBox.hpp"
#include <iostream>

const int ROUNDS_128 = 10;
const int ROUNDS_192 = 12;
const int ROUNDS_256 = 14;

class Utillity128
{
public:
	static void subBytes(CipherBlock128* data);
	static void shiftRow(CipherBlock128* data);
	static void mixColumn(CipherBlock128* data);
	static CipherBlock128 addRoundKey(CipherBlock128 data, CipherBlock128* keys, int round);

	static unsigned int subWord(unsigned int word);
	static unsigned char subByte(unsigned char byte);

	static unsigned short polynomialMultiplyGF28(unsigned char value, unsigned char addition);
	static unsigned char polynomialReduceGF28(unsigned short value);
	static unsigned char dotProduct(unsigned char bytesA[sizeof(int)], unsigned char bytesB[sizeof(int)]);

	static CipherBlock128& getConstMatrix()
	{
		static CipherBlock128 constMatrix;
		static bool isConstMatrixCreated = false;

		if (!isConstMatrixCreated)
		{
			unsigned char data[BLOCK_SIZE][BLOCK_SIZE] = { {0x02, 0x03, 0x01, 0x01},
														   {0x01, 0x02, 0x03, 0x01},
														   {0x01, 0x01, 0x02, 0x03},
														   {0x03, 0x01, 0x01, 0x02} };
			constMatrix = CipherBlock128(data);
			isConstMatrixCreated = true;
		}

		return constMatrix;
	}

private:
	static int countLeftStartBit(unsigned short value);
	static const unsigned short IRREDUCIBLE_POLYNOMIAL = 0b100011011;
	static const unsigned short IRREDUCIBLE_POLYNOMIAL_MAX_BIT = 8;
								
};

#endif