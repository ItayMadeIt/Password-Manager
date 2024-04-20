#include "Utillity.hpp"

CipherBlock128 Utillity128::subBytes(CipherBlock128 data)
{
	return CipherBlock128();
}

CipherBlock128 Utillity128::shiftRow(CipherBlock128 data)
{
	return CipherBlock128();
}

CipherBlock128 Utillity128::mixColumn(CipherBlock128 data)
{
	Utillity128::getConstMatrix();
	return CipherBlock128();
}

CipherBlock128 Utillity128::addRoundKey(CipherBlock128 data, CipherBlock128* keys, int round)
{
	return CipherBlock128();
}

int Utillity128::subByte(int byte)
{
	std::pair<unsigned char, unsigned char> pos = byteToPos(byte);

	return PREDEFINED_SBOX[pos.first][pos.second];
}


std::pair<unsigned char, unsigned char> Utillity128::byteToPos(unsigned char value)
{
	return { (value & 0xf0) << BYTE_TO_BIT / 2,  value & 0x0f };
}
