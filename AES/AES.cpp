#include "AES.hpp"

CipherBlock128 AES::encrypt128(CipherBlock128 data, CipherBlock128 key)
{
	CipherBlock128 encryptedData;

	// generate keys
	// CipherBlock128 keys[ROUNDS_128] = KeyGenerator::generateKeys(ROUNDS_128);

	// initial key (I want to use the function for no reason)
	// encryptedData = Utillity128::addRoundKey(data, (*CipherBlock128)key, 0);

	for (int round = 0; round < ROUNDS_128; round++)
	{
		encryptedData = Utillity128::subByte(encryptedData);

		encryptedData = Utillity128::shiftRow(encryptedData);
		
		if (round != ROUNDS_128 - 1)
		{
			encryptedData = Utillity128::mixColumn(encryptedData);
		}

		//encryptedData = Utillity128::addRoundKey(encryptedData, keys[round]);
	}

	return encryptedData;
}

CipherBlock128 AES::decrypt128(CipherBlock128 data, CipherBlock128 key)
{
	return CipherBlock128();
}
