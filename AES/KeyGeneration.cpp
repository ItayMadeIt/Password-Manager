#include "KeyGeneration.hpp"

void KeyGeneration::GenerateKeys(CipherBlock128 key, CipherBlock128* output)
{
    int wordsAmount = (ROUNDS_128 + 1) * BLOCK_SIZE;
    int* words = (int*)malloc(wordsAmount * sizeof(int));

    // Generate first key
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        words[i] = key.getColumn(i);
    }
    output[0] = CipherBlock128(words);
    output[0].printHexLine();

    // Generate keys for all rounds ('ROUNDS_128' additional keys)
    for (int i = 0; i < ROUNDS_128; i++)
    {
        int curWordsIndex = (i + 1) * BLOCK_SIZE;
        int lastWordsIndex = i * BLOCK_SIZE;

        int gOutcome = g(words[lastWordsIndex + (BLOCK_SIZE - 1)], i);

        words[curWordsIndex] = words[lastWordsIndex] ^ gOutcome;

        for (int j = 1; j < BLOCK_SIZE; j++)
        {
            words[curWordsIndex + j] = words[curWordsIndex + j - 1] ^ words[lastWordsIndex];
        }

        output[i + 1] = CipherBlock128(words + curWordsIndex);
    }

    free(words);
}

int KeyGeneration::g(int word, int round)
{
    int result = word;
    
    // left rotation
    result = result << BYTE_TO_BIT * 3 | result >> BYTE_TO_BIT;

    // sub word
    result = Utillity128::subByte(word);

    // xor by round constant
    result ^= ROUND_CONSTANTS_128[round];

    return result;
}
