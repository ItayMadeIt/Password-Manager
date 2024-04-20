#include "KeyGeneration.hpp"

void KeyGeneration::generateKeys128(CipherBlock128 key, CipherBlock128* output)
{
    unsigned int words[(ROUNDS_128 + 1) * BLOCK_SIZE];

    // Generate first key
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        words[i] = key.getColumn(i);
    }
    output[0] = CipherBlock128(words, false);

    // Generate keys for all rounds ('ROUNDS_128' additional keys)
    for (int i = 0; i < ROUNDS_128; i++)
    {
        int curWordsIndex = (i + 1) * BLOCK_SIZE;
        int lastWordsIndex = i * BLOCK_SIZE;

        unsigned int gOutcome = g(words[lastWordsIndex + (BLOCK_SIZE - 1)], i);

        words[curWordsIndex] = words[lastWordsIndex] ^ gOutcome;

        for (int j = 1; j < BLOCK_SIZE; j++)
        {
            words[curWordsIndex + j] = words[curWordsIndex + j - 1] ^ words[lastWordsIndex + j];
        }

        output[i + 1] = CipherBlock128(words + curWordsIndex, false);
    }
}

unsigned int KeyGeneration::g(unsigned int word, int round)
{
    // left rotation
    unsigned int result = (word << BYTE_TO_BIT) | (word >> BYTE_TO_BIT * 3);

    // sub word
    result = Utillity128::subWord(result);

    // xor by round constant
    result ^= ROUND_CONSTANTS_128[round];

    return result;
}
