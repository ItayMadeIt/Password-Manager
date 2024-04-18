#ifndef KEY_GENERATION_HEADER
#define KEY_GENERATION_HEADER

#include "CipherBlock128.hpp"

class KeyGeneration
{
public:
	CipherBlock128* GenerateKeys(CipherBlock128 key);
	//CipherBlock128* GenerateKeys(CipherBlock192 key);
	//CipherBlock128* GenerateKeys(CipherBlock256 key);
};


#endif