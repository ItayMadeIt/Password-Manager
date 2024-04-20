#include "AES.hpp"

CipherBlock128 AES::encrypt128(CipherBlock128 data, CipherBlock128 key)
{
	CipherBlock128 encryptedData;

	// generate keys
	CipherBlock128 keys[ROUNDS_128 + 1];
	KeyGeneration::generateKeys128(key, keys);

	// initial key (I want to use the function for no reason)
	encryptedData = Utillity128::addRoundKey(data, keys, 0);

	encryptedData.printHex();

	for (int round = 0; round < ROUNDS_128;)
	{
		Utillity128::subBytes(&encryptedData);

		printf("SUB BYTES [Round %d]\n", round + 1);
		encryptedData.printHex();
		printf("\n");

		Utillity128::shiftRow(&encryptedData);
		
		printf("SHIFT ROWS [Round %d]\n", round + 1);
		encryptedData.printHex();
		printf("\n");

		if (round != ROUNDS_128 - 1)
		{
			encryptedData = Utillity128::mixColumn(encryptedData);
		}

		encryptedData = Utillity128::addRoundKey(encryptedData, keys, ++round);
	}

	return encryptedData;
}

CipherBlock128 AES::decrypt128(CipherBlock128 data, CipherBlock128 key)
{
	return CipherBlock128();
}
