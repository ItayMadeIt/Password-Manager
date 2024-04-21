#ifndef CIPHER_BLOCK_128_HEADER
#define CIPHER_BLOCK_128_HEADER

#include <iostream>
#include <bitset>
#include<iomanip>
#include<sstream>

#define BYTE_TO_BIT 8

const int BLOCK_SIZE = 4;

class CipherBlock128 
{
public:
	unsigned char data[BLOCK_SIZE][BLOCK_SIZE];

	// instructors
	CipherBlock128();
	CipherBlock128(const unsigned char value);
	CipherBlock128(const unsigned int values[BLOCK_SIZE], const bool isRows);
	CipherBlock128(const unsigned char values[BLOCK_SIZE][BLOCK_SIZE]);
	CipherBlock128(const unsigned char values[BLOCK_SIZE * BLOCK_SIZE]);

	// print
	void printHex();
	void printHexLine();
	void printBinary();

	// get row and column as integers (4 chars = 4 bytes = int)
	int getRow(int rowIndex) const;
	void getRowAsChars(int rowIndex, unsigned char row[BLOCK_SIZE]) const;
	int shiftRow(int rowIndex, int shift) const;
	int getColumn(int columnIndex) const;
	void getColumnAsChars(int columnIndex, unsigned char column[BLOCK_SIZE]) const;
	int shiftColumn(int columnIndex, int shift) const;

	// xor operation
	CipherBlock128 operator^(const CipherBlock128& other);
	// equal
	friend bool operator==(const CipherBlock128& lhs, const CipherBlock128& rhs);

	// "to string" function (easy to pring using std::cout)
	friend inline std::ostream& operator<<(std::ostream& _stream, CipherBlock128 const& v);
};

#endif