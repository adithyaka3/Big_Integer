// CopyRight: Adithya K Anil
// credits: google, chatGPT
#ifndef BIGINT_H
#define BIGINT_H
#include <stdbool.h>
#include <stdlib.h>
#include <string>
using namespace std;

// Define a structure to represent the big integer
typedef struct {
    string digits;    // Array to store the digits of the big integer
    bool is_negative; // Flag to indicate if the number is negative
} BigInt;

BigInt *createBigIntFromString(const char *str);

// Arithmetic functions
BigInt *addBigInts(const BigInt *a, const BigInt *b);
BigInt *subtractBigInts(const BigInt *a, const BigInt *b);
int compare(const BigInt *a, const BigInt *b);

#endif // BIGINT_H
