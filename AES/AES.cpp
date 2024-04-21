#include "AES.hpp"

CipherBlock128 AES::encrypt128(CipherBlock128 data, CipherBlock128 key)
{
	CipherBlock128 encryptedData;

	// generate keys
	CipherBlock128 keys[ROUNDS_128 + 1];
	KeyGeneration::generateKeys128(key, keys);

	// initial key (I want to use the function for no reason)
	encryptedData = Utillity128::addRoundKey(data, keys, 0);

	for (int round = 0; round < ROUNDS_128;)
	{
		Utillity128::subBytes(&encryptedData);

		Utillity128::shiftRow(&encryptedData);
		
		if (round != ROUNDS_128 - 1)
		{
			Utillity128::mixColumn(&encryptedData);
		}

		encryptedData = Utillity128::addRoundKey(encryptedData, keys, ++round);
	}

	return encryptedData;
}

CipherBlock128 AES::decrypt128(CipherBlock128 data, CipherBlock128 key)
{
	CipherBlock128 decryptedData = data;
	
	// keys
	CipherBlock128 keys[ROUNDS_128 + 1];
	KeyGeneration::generateKeys128(key, keys);

	decryptedData = Utillity128::addRoundKey(decryptedData, keys, ROUNDS_128);

	for (int round = ROUNDS_128; round >= 1;)
	{

		if (round != ROUNDS_128)
		{
			Utillity128::invMixColumn(&decryptedData);
		}

		Utillity128::invShiftRow(&decryptedData);
		
		Utillity128::invSubBytes(&decryptedData);
		
		decryptedData = Utillity128::addRoundKey(decryptedData, keys, --round);
	}



	return decryptedData;
}
