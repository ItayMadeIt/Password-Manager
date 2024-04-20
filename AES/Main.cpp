#include <iostream>
#include "CipherBlock128.hpp"
#include "Utillity.hpp"

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
    unsigned short value = Utillity128::polynomialMultiplyGF28(0b11010110, 0b00110110);
    unsigned short result = Utillity128::polynomialReduceGF28(value);
    std::cout << std::bitset<16>(result) << std::endl;

    printf("\n\n\n\n\------\n");


	unsigned char dataValues[BLOCK_SIZE * BLOCK_SIZE] = 
                                { 0x54 , 0x77 , 0x6F , 0x20 
                                , 0x4F , 0x6E , 0x65 , 0x20 
                                , 0x4E , 0x69 , 0x6E , 0x65 
                                , 0x20 , 0x54 , 0x77 , 0x6F };

    unsigned char keyValues[BLOCK_SIZE * BLOCK_SIZE] = 
                                { 0x54 , 0x68 , 0x61 , 0x74,
                                  0x73 , 0x20 , 0x6D , 0x79,
                                  0x20 , 0x4B , 0x75 , 0x6E,
                                  0x67 , 0x20 , 0x46 , 0x75 };

    unsigned int keyRowValues[BLOCK_SIZE] = 
                                { 0x54732067,
                                  0x68204B20,
                                  0x616D7546,
                                  0x74796E75 };
     unsigned int keyColValues[BLOCK_SIZE] = 
                                { 0x54686174 
                                , 0x73206D79 
                                , 0x204B756E 
                                , 0x67204675 };


    CipherBlock128 data = CipherBlock128(dataValues);

    CipherBlock128 key = CipherBlock128(keyValues);
    key.printHex();
    printf("\n");
    CipherBlock128 keyRow = CipherBlock128(keyRowValues, true);
    keyRow.printHex();
    printf("\n");
    CipherBlock128 keyCol = CipherBlock128(keyColValues, false);
    keyRow.printHex();
    printf("\n");

    if (keyCol == keyRow && keyCol == key)
    {
        printf("Keys are equal\n");
    }

    CipherBlock128 keys[ROUNDS_128 + 1] = {};
    


    KeyGeneration::generateKeys128(key, keys);
    
    AES::encrypt128(data, key);

    return 0;
}