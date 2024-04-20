#include <iostream>
#include "CipherBlock128.hpp"

/*
Timers for debug purposes
*/
#include <chrono>
#include "AES.hpp"
#include "KeyGeneration.hpp"
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
                                { 0x54 , 0x68 , 0x61 , 0x74 
                                , 0x73 , 0x20 , 0x6D , 0x79 
                                , 0x20 , 0x4B , 0x75 , 0x6E 
                                , 0x67 , 0x20 , 0x46 , 0x75 };

    int values2[BLOCK_SIZE] =   { 0x73617469 
                                , 0x7368636a
                                , 0x6973626f
                                , 0x72696e67 };


    CipherBlock128 v1 = CipherBlock128(values1);
    CipherBlock128 v2 = CipherBlock128(values2);

    printf("Char Constructor:\n");
    v1.printHex();
    printf("\n\n");
    printf("Int Constructor:\n");
    v2.printHex();

    printf("Row:%08X\n", v1.getRow(1));
    printf("Column:%08X\n", v1.getColumn(1));

    CipherBlock128 key = CipherBlock128(values1);
    
    for (size_t i = 0; i < 4; i++)
    {
        printf("%08X\n", key.getColumn(i));
    }
    
    CipherBlock128 keys[ROUNDS_128 + 1] = {};
    
    KeyGeneration::GenerateKeys(key, keys);

    printf("\n\n");
    for (size_t i = 0; i < ROUNDS_128 + 1; i++)
    {
        keys[i].printHexLine();
    }
    
    //AES::encrypt128(block, key);

    return 0;
}