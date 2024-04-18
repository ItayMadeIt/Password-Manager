#ifndef AES_HEADER
#define AES_HEADER


#include <stdio.h>
#include "CipherBlock128.hpp"
#include "Utillity.hpp"

class AES
{
public:
    static CipherBlock128 encrypt128(CipherBlock128 data, CipherBlock128 key);
    //static CipherBlock128 encrypt192(CipherBlock128 data, CipherBlock128 key);
    //static CipherBlock128 encrypt256(CipherBlock128 data, CipherBlock128 key);
    
    
    static CipherBlock128 decrypt128(CipherBlock128 data, CipherBlock128 key);
    //static CipherBlock128 decrypt192(CipherBlock128 data, CipherBlock128 key);
    //static CipherBlock128 decrypt256(CipherBlock128 data, CipherBlock128 key);

private:
    static const int ROUNDS_128 = 10;
    static const int ROUNDS_192 = 12;
    static const int ROUNDS_256 = 14;
};


#endif