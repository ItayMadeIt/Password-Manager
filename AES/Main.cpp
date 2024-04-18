#include <iostream>
#include "CipherBlock128.hpp"




int main() 
{
    CipherBlock128 block;

	int values[BLOCK_SIZE] = { 0x13222110 , 0x27261514 , 0x2b1a2928 , 0x2f1e2d1c };

	unsigned char values1[BLOCK_SIZE * BLOCK_SIZE] = 
                                { 0x10 , 0x21 , 0x22 , 0x13 
                                , 0x14 , 0x15 , 0x26 , 0x27 
                                , 0x28 , 0x29 , 0x1a , 0x2b 
                                , 0x1c , 0x2d , 0x1e , 0x2f };

    unsigned char values2[BLOCK_SIZE][BLOCK_SIZE] = {
                                 { 0x10 , 0x21 , 0x22 , 0x13},
                                 { 0x14 , 0x15 , 0x26 , 0x27},
                                 { 0x28 , 0x29 , 0x1a , 0x2b},
                                 { 0x1c , 0x2d , 0x1e , 0x2f} };

    block.init(values);
    printf("Values 0:\n");
    block.printHex();
    
    block.init(values1);
    printf("\nValues 1:\n");
    block.printHex();
    
    block.init(values2);
    printf("\nValues 2:\n");
    block.printHex();


    return 0;
}