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
#ifndef UTIL_KEY
#define UTIL_KEY
#include "util_key.h"
#endif

using namespace std;


bit_word::bit_word() {
   bsize = 0;
   bword = vector<bitset<B_SIZE>>();
}
bit_word::bit_word(vector<bitset<B_SIZE>> word, int size)
   : bsize(size)
   , bword(word)
{
/*
   debug("bit_word|from bitset vector", "Constructing from word");
   for(int i=0;i<word.size();i++) {
      narrator(word[i]);
   }
   debug("bit_word|from bitset vector", "Size", bsize, "| Constructed word");
   for(int i=0;i<word.size();i++) {
      narrator(bword[i]);
   }
*/
}

bit_word::bit_word(bit_word& to_copy, int start_c, int no_char) { // Not tested
   bsize = no_char;
   //debug("bit_word|from copy", "Making copy of len", no_char, "starting at", start_c);

   if(to_copy.bsize <= start_c || to_copy.bsize < start_c + no_char) {
      debug("bit_word", "Copying beyond size of word to copy");
      debug("bit_word", "Word:", to_copy);
      debug("bit_word", "Len:", to_copy.bsize);
      debug("bit_word", "start_c:", start_c);
      debug("bit_word", "no_char:", no_char);
      exit(-1);
   }
   if(start_c < 0 || no_char < 0) {
      debug("bit_word", "Negative index/number of characters to copy");
      debug("bit_word", "Word:", to_copy);
      debug("bit_word", "Len:", to_copy.bsize);
      debug("bit_word", "start_c:", start_c);
      debug("bit_word", "no_char:", no_char);
   }

   int start_buff = start_c/B_SIZE;
   int end_buff = (start_c+no_char) / B_SIZE - ((start_c+no_char%B_SIZE == 0) ? 1 : 0); // <0 shouldn't be an issue.
   int pos = 0, no_buff=end_buff-start_buff+1;
   //debug("bit_word|from copy", "sb", start_buff, "| eb", end_buff);
   //debug("bit_word|from copy", "Using", no_buff, "buffers");

   bword = vector<bitset<B_SIZE>>(no_buff);
   for(int i=0; i<no_char; i++) {
      (*this)[i] = to_copy[i+start_c];
   }
}

void bit_word::append(bit_word& word) { // Not tested
   //bit_word* ret = new bit_word(*this, 0, this->bsize);
   for(int i=0; i<word.bsize; i++) {
      if(this->bsize % B_SIZE == 0) { // Used up all space
         this->bword.push_back(bitset<B_SIZE>());
      }
      (*this)[bsize] = word[i];
      this->bsize++;
   }
}

char* bit_word::tochar(void) {
   return 0;
}
bool bit_word::operator==(const bit_word& c) {
   return false;
}

bitset<B_SIZE>::reference bit_word::operator[](int k) { // Tested
   int r = bsize%B_SIZE;
   int sig=k/B_SIZE, left=k%B_SIZE;
   if(k>=bsize || k < 0) {
      debug("bit_word[]", "Error: Index", k, "out of range 0 -", bsize-1, ". Exiting.");
      exit(-1);
   }
   
   if(r == 0) { // Last buffer is not weird
      return bword[sig][B_SIZE-1-left];
   } else { // Last buffer is weird
      if(sig == bsize/B_SIZE) {
         auto b = bword[sig][(bsize%B_SIZE)-1-left];
         return b;
      } else {
         auto b = bword[sig][B_SIZE-1-left];
         return b;
      }
   }
}

bool bit_word::bit_compare(const bit_word& c, int index) { // Not tested
   bit_word tmp(c);
   bool a = (*this)[index], b = tmp[index];
   return (a == b);
}

ostream& operator<<(ostream& out, const bit_word& c) { // Tested
   //debug("bit_word<<", "Printing word of size", c.bsize);
   bit_word tmp_word(c); // Cannot use [] with const argument
   for(int i=0; i<c.bsize; i++) {
      cout << tmp_word[i];
   }
   return out;
}


// --------------------------------------------------------

trie<bit_word&>::trie()
   : w(*(new bit_word())) 
   , no_app(0)
   , dic_index(0)
   , depth(0)
   , papa(0)
   , lchild(0)
   , rchild(0)
{ }

trie<bit_word&>::trie(bit_word& word, int index, int d) 
   : w(word)
   , no_app(0)
   , dic_index(index)
   , depth(d)
   , papa(0)
   , lchild(0)
   , rchild(0)
{ 
//narrator("New node with Index ", dic_index, "| Depth ", depth);
}

trie<bit_word&>* trie<bit_word&>::insert(bit_word& new_word, int no, int len) { // Tested
   //debug("trie|insert", "Insert attempt; len", len);
   int index = len;
   if(index<0) index=0;

   if(len>=new_word.bsize) {
      cout << endl;
      debug("trie|insert", "End of file reached.");
      return 0;
   }

   bool value = new_word[index];

   if(value){ // Right
      if(rchild) {
         //debug("trie|insert", "Right");
         return rchild->insert(new_word, no, len+1);
      } else {
         //debug("trie|insert", "Insert Success r", len+1);
         bit_word* token = new bit_word(new_word, 0, len+1);
         trie<bit_word&>* new_trie = new trie(*token, no, len+1);
         rchild = new_trie;
         //debug("trie|insert", "Node", new_trie, "| I", new_trie->dic_index, "| d", new_trie->depth);
         //debug("trie|insert", "Node", rchild, "| I", rchild->dic_index, "| d", rchild->depth);
         //new_trie->papa = this;
         return rchild;
      }
   } else {   // Left
      if(lchild) {
         //debug("trie|insert", "Left");
         return lchild->insert(new_word, no, len+1);
      } else {
         //debug("trie|insert", "Insert Success l", len+1);
         bit_word* token = new bit_word(new_word, 0, len+1);
         trie<bit_word&>* new_trie = new trie(*token, no, len+1);
         lchild = new_trie;
         //debug("trie|insert", "Node", new_trie, "| I", new_trie->dic_index, "| d", new_trie->depth);
         //debug("trie|insert", "Node", lchild, "| I", lchild->dic_index, "| d", lchild->depth);
         //new_trie->papa = this;
         return lchild;
      }
   }
   debug("trie|insert", "Potential bug?");
   return 0;
} 

trie<bit_word&>* trie<bit_word&>::insert_lz(bit_word& buffer, ifstream& in, ofstream& out, int no, int len) { // Not tested
   //debug("trie|insert_lz", "Insert attempt; len", len);
   int index = len;
   if(index<0) index=0;

   if(len>=buffer.bsize) {
      debug("trie|insert", "End of buffer reached. Reading...");
      int n = rc_file(in, buffer, BUFFER_SIZE);
      if(n==0) {
         debug("trie|insert", "End of file reached.");
         // TAKE CARE OF LAST THING 
         // Convention: always end with index
      }
      return 0;
   }

   bool value = buffer[index];

   if(value){ // Right
      if(rchild) {
         //debug("trie|insert", "Right");
         return rchild->insert(buffer, no, len+1);
      } else {
         //debug("trie|insert", "Insert Success r", len+1);
         bit_word* token = new bit_word(buffer, 0, len+1);
         trie<bit_word&>* new_trie = new trie(*token, no, len+1);
         rchild = new_trie;
         //debug("trie|insert", "Node", new_trie, "| I", new_trie->dic_index, "| d", new_trie->depth);
         //debug("trie|insert", "Node", rchild, "| I", rchild->dic_index, "| d", rchild->depth);
         //new_trie->papa = this;
         return rchild;
      }
   } else {   // Left
      if(lchild) {
         //debug("trie|insert", "Left");
         return lchild->insert(buffer, no, len+1);
      } else {
         //debug("trie|insert", "Insert Success l", len+1);
         bit_word* token = new bit_word(buffer, 0, len+1);
         trie<bit_word&>* new_trie = new trie(*token, no, len+1);
         lchild = new_trie;
         //debug("trie|insert", "Node", new_trie, "| I", new_trie->dic_index, "| d", new_trie->depth);
         //debug("trie|insert", "Node", lchild, "| I", lchild->dic_index, "| d", lchild->depth);
         //new_trie->papa = this;
         return lchild;
      }
   }
   debug("trie|insert", "Potential bug?");
   return 0;
} 

int trie<bit_word&>::pprint(int depth, int cnt) {
   narrator("Node", cnt, "|", "Depth", depth, "| Word");
   narrator(w);
   narrator("----------------");
   if(lchild) {
      cnt = lchild->pprint(depth+1, cnt+1);
   }
   if(rchild) {
      cnt = rchild->pprint(depth+1, cnt+1);
   }
   return cnt;
}
int trie<bit_word&>::cprint(int depth, int cnt) {
   narrator("N", cnt, "|", "D", depth, "| W", w);
   if(lchild) {
      cnt = lchild->cprint(depth+1, cnt+1);
   }
   if(rchild) {
      cnt = rchild->cprint(depth+1, cnt+1);
   }
   return cnt;
}

/*
template <>
bool trie<bit_word&>::path(trie<bit_word&> &t, bit_word &word) { // not needed?
   return false;
} 
*/

// Read call
template <>
trie<string>* trie<string>::LZW(
   string& thing, ifstream& fin, ofstream& fout
   , bool& read_flag, int index, int d
   ){ // Not tested
   //debug("trie|insert", "Depth", d, "Current buff:", "\""+thing+"\"");
   if(index<0) index=0;

   if(d>=C_SIZE*thing.size() && !read_flag) { // Last buffer and exceeding size of buffer
      debug("trie|insert", "Writing last index.");
      
      // TAKE CARE OF LAST THING 
      // Convention: always end with index
      fout << this->dic_index;
      return 0; // Indicate end
   }
   while(d>=C_SIZE*thing.size() && read_flag) { // Mult by C_SIZE since sorting wrt bits; Note: should not loop more than once...
      debug("trie|insert", "End of buffer reached. d: ", d, "| Current:", "\""+thing+"\"", "| Reading...");
      char *ptr = new char[BUFFER_SIZE+1];
      ptr[BUFFER_SIZE] = 0; // To avoid major fuckups
      fin.read(ptr, BUFFER_SIZE);
      int n = fin.gcount();

      if(n == BUFFER_SIZE) {
         debug("trie|insert", "Read full buffer.");
         string tmp(ptr);
         thing.append(tmp);
         debug("trie|insert", "New thing:", "\""+thing+"\"");
      } else {
         debug("trie|insert", "End of file reached,", n, "bytes left.");
         ptr[n] = 0; // Terminate char array before string conversion
         string tmp(ptr);
         thing.append(tmp);
         debug("trie|insert", "New thing:", "\""+thing+"\"");
         read_flag=false; // No more reading 
      }
      delete ptr;
   }
   int wi = d/C_SIZE, bi = d%C_SIZE;
   string cchar = thing.substr(wi, 1);
   //debug("trie|insert", "cchar:", "\""+cchar+"\"");
   
   if(cchar == "") {
      debug("trie|insert", "Invalid cchar", cchar.size(), "| ", cchar, "| buff", "\""+thing+"\"");
      exit(-1);
   }
   string tmp = btos(cchar.c_str(), 1);
   //debug("trie|insert", "ib:", "\""+tmp+"\"");
   bitset<C_SIZE> cword(tmp);
   //debug("trie|insert", "cchar:", "\""+cchar+"\"", "| cword:", cword, "| cbit:", bi);

   bool cbit = cword[C_SIZE-bi-1]; // Note: doing a standard bit by bit sorting

   if(cbit){ // Right
      if(rchild) {
         //debug("trie|insert", "Right");
         return rchild->LZW(thing, fin, fout, read_flag, index, d+1);
      } else {
         int ch_d = d+1;
         int tok_len = (ch_d/8)+(ch_d%C_SIZE == 0 ? 0 : 1); 
         string token = thing.substr(0, tok_len);
         thing = thing.substr(tok_len, thing.size()-1);
         trie<string>* new_trie = new trie(token, index, ch_d);
         rchild = new_trie;
         //debug("trie|insert", "Insert Success r", ch_d, "| value:", "\""+token+"\"", "| tok_len", tok_len);
         //debug("trie|insert", "Node", new_trie, "| I", new_trie->dic_index, "| d", new_trie->depth);
         //debug("trie|insert", "Node", rchild, "| I", rchild->dic_index, "| d", rchild->depth);
         //new_trie->papa = this;

         fout << this->dic_index << token[token.size()-1];
         return rchild;
      }
   } else {   // Left
      if(lchild) {
         //debug("trie|insert", "Left");
         return lchild->LZW(thing, fin, fout, read_flag, index, d+1);
      } else {
         int ch_d = d+1;
         int tok_len = (ch_d/8)+(ch_d%C_SIZE == 0 ? 0 : 1); 
         string token = thing.substr(0, tok_len);
         thing = thing.substr(tok_len, thing.size()-1);
         trie<string>* new_trie = new trie(token, index, ch_d);
         lchild = new_trie;
         //debug("trie|insert", "Insert Success l", ch_d, "| value:", "\""+token+"\"", "| tok_len", tok_len);
         //debug("trie|insert", "Node", new_trie, "| I", new_trie->dic_index, "| d", new_trie->depth);
         //debug("trie|insert", "Node", lchild, "| I", lchild->dic_index, "| d", lchild->depth);
         //new_trie->papa = this;

         fout << this->dic_index << token[token.size()-1];
         return lchild;
      }
   }
   debug("trie|insert", "Potential bug?");
   return 0;
}

