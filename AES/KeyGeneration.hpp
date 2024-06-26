#ifndef KEY_GENERATION_HEADER
#define KEY_GENERATION_HEADER

#include "CipherBlock128.hpp"
#include "Utillity.hpp"

const unsigned int ROUND_CONSTANTS_128[ROUNDS_128] = { 0x01000000 ,
													   0x02000000 ,
													   0x04000000 ,
													   0x08000000 ,
													   0x10000000 ,
													   0x20000000 ,
													   0x40000000 ,
													   0x80000000 ,
													   0x1B000000 ,
													   0x36000000 };

											  
class KeyGeneration							  
{
public:
	static void generateKeys128(CipherBlock128 key, CipherBlock128* output);
	//CipherBlock128* GenerateKeys(CipherBlock192 key);
	//CipherBlock128* GenerateKeys(CipherBlock256 key);

private:
	static unsigned int g(unsigned int word, int round);
};


#endif