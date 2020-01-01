#ifndef BITS
#define BITS
#include <bits/stdc++.h>
#endif

#define C_NO 4
#define C_SIZE 8
#define B_SIZE (C_NO*C_SIZE)
#define BUFFER_SIZE (8*B_SIZE) // Arbitrary for now

#ifndef UTIL_KEY
#define UTIL_KEY
#include "util_key.h" // Uses the above defs, keep this here
#endif

using namespace std;

bitset<B_SIZE> br(ifstream& in, int n=C_NO); // n is bytes
int bw(ofstream& out, bitset<B_SIZE> word, int n=B_SIZE); 
string btos(const char bword[], int n=C_NO);
string btos(char bword[], int n=C_NO);
char* stob(bitset<B_SIZE> word);
int read_bit_file(ifstream &fin, vector<bitset<B_SIZE>> &buff, int size); // size is bits
int rc_file(ifstream &fin, bit_word& buff, int n=BUFFER_SIZE); // size in bits
