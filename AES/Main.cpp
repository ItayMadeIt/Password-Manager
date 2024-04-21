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
    return std::chrono::duration<double, std::micro>(end_time - start_time).count();
}

int main()
{


    unsigned int dataValues[BLOCK_SIZE] =
    { 0x00000101,
      0x03030707,
      0x0f0f1f1f,
      0x3f3f7f7f };

    //unsigned char keyValues[BLOCK_SIZE * BLOCK_SIZE] = 
    //                            { 0x54 , 0x68 , 0x61 , 0x74,
    //                              0x73 , 0x20 , 0x6D , 0x79,
    //                              0x20 , 0x4B , 0x75 , 0x6E,
    //                              0x67 , 0x20 , 0x46 , 0x75 };
    //

    CipherBlock128 data = CipherBlock128(dataValues, false);

    CipherBlock128 key = CipherBlock128((unsigned char)(0));

    CipherBlock128 result;

    auto start = start_timer();
    result = AES::encrypt128(data, key);
    auto end = end_timer(start);
    printf("%f\n", end);
    result.printHexLine();


    return 0;
}