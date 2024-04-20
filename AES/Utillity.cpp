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


std::pair<unsigned char, unsigned char> Utillity128::byteToPos(unsigned char value)
{
	return { (value & 0xf0) >> BYTE_TO_BIT / 2,  value & 0x0f };
}
