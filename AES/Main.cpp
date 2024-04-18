#include <iostream>
#include "CipherBlock128.hpp"

/*
Timers for debug purposes
*/
#include <chrono>
#include "AES.hpp"
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

	unsigned char values1[BLOCK_SIZE * BLOCK_SIZE] = 
                                { 0x11 , 0x11 , 0x12 , 0x13 
                                , 0x14 , 0x15 , 0x26 , 0x64 
                                , 0x28 , 0x29 , 0x1a , 0x52 
                                , 0x23 , 0x64 , 0x52 , 0x11 };


    CipherBlock128 block = CipherBlock128();
    printf("Values 0:\n");
    block.printHex();
    
    CipherBlock128 block1 = CipherBlock128(values1);
    printf("\nValues 1:\n");
    block1.printHex();

    CipherBlock128 result = block ^ block1;
    printf("\nResult:\n");
    result.printHex();

    std::cout << std::hex << result.getRow(3) << std::endl;
    std::cout << std::hex << result.shiftRow(3, 1) << std::endl;
    std::cout << std::hex << result.getColumn(3) << std::endl;
    std::cout << std::hex << result.shiftColumn(3, 1) << std::endl;

    AES::encrypt128(block, block1);

    return 0;
}