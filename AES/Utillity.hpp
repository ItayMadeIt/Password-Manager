#ifndef UTILLITY_128_HEADER
#define UTILLITY_128_HEADER

#include "CipherBlock128.hpp"
#include "SBox.hpp"
#include <iostream>

class Utillity128
{
public:
	static CipherBlock128 subByte(CipherBlock128 data);
	static CipherBlock128 shiftRow(CipherBlock128 data);
	static CipherBlock128 mixColumn(CipherBlock128 data);
	static CipherBlock128 addRoundKey(CipherBlock128 data, CipherBlock128* keys, int round);

	static SBox getSBox()
	{
		return PREDEFINED_SBOX;
	}
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
};

#endif