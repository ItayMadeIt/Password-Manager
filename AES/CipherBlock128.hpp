#ifndef CIPHER_BLOCK_128_HEADER
#define CIPHER_BLOCK_128_HEADER

#include <iostream>
#include <bitset>
#include<iomanip>
#include<sstream>

const int BLOCK_SIZE = 4;

class CipherBlock128 
{
public:
	unsigned char data[BLOCK_SIZE][BLOCK_SIZE];

	// instructors
	CipherBlock128();
	CipherBlock128(const unsigned char value);
	CipherBlock128(const int values[BLOCK_SIZE]);
	CipherBlock128(const unsigned char values[BLOCK_SIZE][BLOCK_SIZE]);
	CipherBlock128(const unsigned char values[BLOCK_SIZE * BLOCK_SIZE]);

	// print
	void printHex();
	void printBinary();

	// xor operation
	CipherBlock128 operator^(const CipherBlock128& other);

	// "to string" function (easy to pring using std::cout)
	friend inline std::ostream& operator<<(std::ostream& _stream, CipherBlock128 const& v);
};

#endif