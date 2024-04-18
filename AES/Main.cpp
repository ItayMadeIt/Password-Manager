#include <iostream>
#include "CipherBlock128.hpp"

/*
Timers for debug purposes
*/
#include <chrono>
auto start_timer() {
    return std::chrono::high_resolution_clock::now();
}

// Get the duration in milliseconds since the start time
double end_timer(std::chrono::time_point<std::chrono::high_resolution_clock> start_time) {
    auto end_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end_time - start_time).count();
}

int main() 
{
	int values[BLOCK_SIZE] = { 0x13222110 , 0x27261514 , 0x2b1a2928 , 0x2f1e2d1c };

	unsigned char values1[BLOCK_SIZE * BLOCK_SIZE] = 
                                { 0x11 , 0x21 , 0x22 , 0x13 
                                , 0x14 , 0x15 , 0x26 , 0x27 
                                , 0x28 , 0x29 , 0x1a , 0x2b 
                                , 0x1c , 0x2d , 0x1e , 0x2f };


    CipherBlock128 block = CipherBlock128(values);
    printf("Values 0:\n");
    block.printBinary();
    
    CipherBlock128 block1 = CipherBlock128(values1);
    printf("\nValues 1:\n");
    block1.printBinary();

    double timers[10000] = { 0 };

    CipherBlock128 newBlock;
    for (size_t a = 0; a < 100; a++)
    {
        for (size_t i = 0; i < 10000; i++)
        {
            newBlock = block ^ block1;
            //printf("\nValues addition\n");
            //newBlock.printBinary();

            newBlock = newBlock ^ block1;
            //printf("\nValues addition\n");
            //newBlock.printBinary();
        }
    }
   


    return 0;
}