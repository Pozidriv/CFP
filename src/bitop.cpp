#ifndef BITS
#define BITS
#include <bits/stdc++.h>
#endif
#ifndef BITOP
#define BITOP
#include "bitop.h"
#endif
#ifndef UTIL_IO
#define UTIL_IO
#include "util_io.h"
#endif

using namespace std;

bitset<B_SIZE> br(ifstream& in, int n) { // Tested
//   debug("br", "Reading", n, "bytes from a file");
   char *memblock;
   string tmp;

   memblock = new char[C_NO+1]; // +1 for eob
   memblock[(C_NO>n ? n : C_NO)] = 0;
   in.read(memblock, n);
//   debug("br", "Read string", memblock);
   tmp = btos(memblock, n);
   bitset<B_SIZE> buff (tmp);

//   debug("br", "tmp:", tmp);

   delete[] memblock;
   return buff;
}

int bw(ofstream& out, bitset<B_SIZE> word, int n) { // Not tested
   debug("bw", "Binary write to file");
   char* buff;

   buff = stob(word);
//   debug("bw", "buff:", buff);

   out.write(buff, ((n<C_NO) ? n : C_NO));

   delete[] buff;
   return 0;
}

string btos(char bword[], int n) {
   return btos(const_cast<const char*>(bword), n);
}

string btos(const char bword[], int n) { // Tested
//   debug("btos", "Converting binary word to string");
   stringstream buffer;

//   debug("btos", "cr:");
   for(int i=0; i<(C_NO>n ? n : C_NO); i++) {
      int bin[C_SIZE], cr;
      cr = bword[i];
//      cout << cr << " ";
      for(int j=1; j<=8; j++) {
         bin[C_SIZE-j] = cr % 2;
         cr = (cr >> 1);
//         debug("btos", "cr:", cr);
      }
      for(int j=0; j<8; j++) {
         buffer << bin[j];
      }
   }
//   cout << endl;

   return buffer.str();
}

char* stob(bitset<B_SIZE> word) { // Tested
   //debug("stob", "Converting bitset to binary");
   char* ret = new char[C_NO];

   debug("stob", "cr:");
   for(int i=0; i<C_NO; i++) {
      int cr=0;
//      debug("stob", "cr");
      for(int j=0; j<8; j++) {
         if(word[B_SIZE-(8*i + j+1)]) {
            cout << "1 ";
            cr++;
         } else {
            cout << "0 ";
         }
         
//         debug("stob", cr);
         if(j<7) 
            cr = (cr << 1);
      }
      cout << cr << " ";
      ret[i] = cr;
   }
   cout << endl;

   return ret;
}

int read_bit_file(ifstream &fin, vector<bitset<B_SIZE>> &buff, int size) { // Tested
//   debug("read_bit_file", "Reading", size, "bits");
//   debug("read_bit_file", "Using around", size/B_SIZE, "buffers");
   int n=0;
   for(int i=0; i<(size/B_SIZE); i++) {
//      debug("read_bit_file", "Filling buffer", i);
      bitset<B_SIZE> tmp = br(fin);
      buff.push_back(tmp);
      n+=B_SIZE;
   }
   if(size%B_SIZE != 0) {
//      debug("read_bit_file", "Filling buffer", (size/B_SIZE));
      int r_bits = size%B_SIZE;
      //int extra = ((r_bits%C_SIZE) == 0); 

//      debug("read_bit_file", "Remaining bits", r_bits);
      bitset<B_SIZE> tmp = br(fin, r_bits/C_SIZE); //(r_bits/C_SIZE) should be an integer
      buff.push_back(tmp);
      n+=size%B_SIZE;
   }

   return n;
}

int rc_file(ifstream &fin, bit_word& buff, int n) { // Not tested
   vector<bitset<B_SIZE>> t = vector<bitset<B_SIZE>>();
   int count=read_bit_file(fin, t, BUFFER_SIZE);
   narrator("Read", n, "bits");
   
   bit_word obj(t,n);
   buff.append(obj);
   return n;
}
