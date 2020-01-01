#ifndef UTIL_IO
#define UTIL_IO
#include "util_io.h"
#endif
#ifndef BITOP
#define BITOP
#include "bitop.h"
#endif
#ifndef UTIL_KEY
#define UTIL_KEY
#include "util_key.h"
#endif
#ifndef BITS
#define BITS
#include <bits/stdc++.h>
#endif
#ifndef ENC
#define ENC
#include "enc.h"
#endif

using namespace std;

int dec_basic(string file, string out) {
   streampos size;
   ifstream inptr;
   ofstream outptr;
   inptr.open(file, ios::in|ios::ate);
   outptr.open(out, ios::out);

   size = inptr.tellg();
   inptr.seekg(0, ios::beg);
   debug("dec_basic", "File size (bytes):", size);

// Reading (needs to be done in chuncks)

   int len = size % C_NO;
   debug("dec_basic", "len (bytes)", len);

// dictionary setup
   vector<string> dictionary;

// Writing file
   string buffer;
   dictionary.push_back(buffer);
   int index=1;
   bool read_flag=true;

   while(getline(inptr, buffer, '\0')) {
      index = atoi(buffer.c_str());
      debug("dec_basic", "Index", index);
      if(index >= dictionary.size()) {
         debug("dec_basic", "Index", index, "exceeding dictionary size", dictionary.size());
         exit(-1);
      }
      outptr << dictionary[index];
      if(getline(inptr, buffer, '\0')) {
         debug("dec_basic", "buff", buffer);
         outptr << buffer;
         string tmp(dictionary[index]);
         tmp = tmp+buffer;
         dictionary.push_back(tmp);
      } else {
         debug("dec_basic", "No buffer read");
         break;
      }
   }

   inptr.close();
   outptr.close();
   return 0;
}

int enc_basic(string file, string out) {
   streampos size;
   ifstream inptr;
   ofstream outptr;
   inptr.open(file, ios::in|ios::ate);
   outptr.open(out, ios::out);

   size = inptr.tellg();
   inptr.seekg(0, ios::beg);
   debug("enc_basic", "Input file size (bytes):", size);


// Reading needs to be done in chuncks
// Trie setup
   trie<string>* root = new trie<string>();
   trie<string>* ret = root;


// Writing file
   string* buffer = new string();
   int index=1;
   bool read_flag=true;

// Header (not needed, null separated index/characters)

// LZW
   while(ret) {
      //cout << inptr.tellg() << " ";
      ret = root->LZW(*buffer, inptr, outptr, read_flag, index, 0);
      index++;
   }

// Exit script (Add stats?)

   debug("enc_basic", "Deleting trie...");
   delete root;
   cout << endl;

   inptr.close();
   outptr.close();
   return 0;
}

int enc_test(string file, string out) {
   streampos size;
   ifstream inptr;
   ofstream outptr;
   //inptr.open(file, ios::in|ios::binary|ios::ate);
   //outptr.open(out, ios::out|ios::binary);
   inptr.open(file, ios::in|ios::ate);
   outptr.open(out, ios::out);
   
   size = inptr.tellg();
   inptr.seekg(0, ios::beg);

/*
   char* memblock;
   memblock = new char[B_SIZE];
   inptr.read(memblock, size*C_SIZE);
   cout << memblock;
   inptr.seekg(0, ios::beg);
*/

/*
   narrator("B_SIZE", B_SIZE, "| C_NO", C_NO, "| C_SIZE", C_SIZE);
   debug("enc_test", "File size (bytes):", size);

   vector<bitset<B_SIZE>> t = vector<bitset<B_SIZE>>();
   int n=read_bit_file(inptr, t, size*C_SIZE);
   narrator("Read", n, "bits");
   bit_word obj(t, n);
   narrator("Input in bits:");
   narrator(obj);
*/


/*
   debug("enc_test", "Testing bit_word");
   narrator("Read", n, "bits");
   bit_word obj(t, n);
   narrator("Input in bits:");
   narrator(obj);
*/
/*
   debug("enc_test", "Testing bitop");

   int len=size%C_NO;
   bw(outptr, tmp, len);
   debug("enc_test", "len (bytes)", len);
*/
   

/*
   debug("enc_test", "Testing bit_word::operator[]");

   for(int i=0; i<296; i++) {
      int nmbr = obj[i];
      cout << nmbr;
      if(i % 32 == 31) {
         cout << endl;
      }
   }
   cout << endl;
*/

/*
   debug("enc_test", "Testing bit_word from copy");
   int start=205, len=90;
   bit_word cop(obj, start, len);
   narrator(cop);
   
   int flag=0;
   for(int i=start; i<start+len-1; i++) {
      if(!obj.bit_compare(cop, i-start)) flag++;
   }
   narrator("Number of differences:", flag);
*/   

/*
   debug("enc_test", "Testing trie<bit_word&>");

   bit_word empty(obj,0,0);
   trie<bit_word&> *root = new trie<bit_word&>(empty,0,0); // To be able to free afterwards
   int pos=0, cnt=0;
   
   while(pos < obj.bsize) {
      cnt++;
      bit_word rest(obj, pos, obj.bsize-pos);
      int tok_len=0;
      trie<bit_word&>* node;
      node = root->insert(rest, cnt);
      if(node == 0) {
         debug("enc_test", "Finished file");
         break;
      } else if(node < 0) {
         debug("enc_test", "Error. Exiting.");
         exit(-1);
      } else {
         //debug("enc_test", "Node", node, "| Index ", node->dic_index, "| Depth ", node->depth);
         tok_len = node->depth;
         pos += tok_len;
         //narrator("pos", pos);
         cout << pos << " ";
      }
   }

   root->cprint(0,1);
*/
   narrator("B_SIZE", B_SIZE, "| C_NO", C_NO, "| C_SIZE", C_SIZE);
   debug("enc_test", "File size (bytes):", size);

   debug("enc_test", "Testing trie<string>");
   trie<string>* root = new trie<string>();
   trie<string>* ret = root;
   string* buffer = new string();
   int index=1;
   bool read_flag=true;

   while(ret) {
      //cout << inptr.tellg() << " ";
      ret = root->LZW(*buffer, inptr, outptr, read_flag, index, 0);
      index++;
   }

   debug("enc_test", "Deleting trie...");
   delete root;
   cout << endl;
   debug("enc_test", "End of test");

   inptr.close();
   outptr.close();
   return 0;
}
