#ifndef UTIL_IO
#define UTIL_IO
#include "util_io.h"
#endif
#ifndef BITS
#define BITS
#include <bits/stdc++.h>
#endif
#ifndef BITOP
#define BITOP
#include "bitop.h"
#endif

using namespace std;

class bit_word {
      friend class bitset; // To access bitset<T>::reference
   public:
      vector<bitset<B_SIZE>> bword;
      int bsize;
      // CONSTRUCTORS
      bit_word();
      bit_word(vector<bitset<B_SIZE>> word, int size);
      bit_word(bit_word& to_copy, int start_c, int no_c);
      
      // METHODS
      char* tochar(void); // delete when done
      bool operator==(const bit_word&);
      bitset<B_SIZE>::reference operator[](int);
      //int &operator[](int);
      bool bit_compare(const bit_word&, int index);
      void append(bit_word& word); // Appends directly to this
};
ostream& operator<<(ostream &out, const bit_word& word);

template <class T>
class trie {
   private:
      trie* papa;    // Pointers are better here.
      trie* lchild;
      trie* rchild;

   public:
      T w;
      int no_app;
      int dic_index;
      int depth;
 
      // CONSTRUCTORS
      trie();
      trie(T word, int index, int depth);
      // DESTRUCTOR
      ~trie();

      // METHODS
      int num_children(void);
      bool is_leaf(void);
      bool has_lchild(void);
      bool has_rchild(void);
      trie& get_lchild(void);
      trie& get_rchild(void);

      trie<T>* LZW(T&, ifstream&, ofstream&, bool&, int, int); // bool& should be true at start
      int cprint(int depth=0, int cnt=1);
      int pprint(int depth=0, int cnt=1);
      //trie& find(bit_word&); // returns leaf if not found
};

// --------------------------------------------------------
template <>
class trie<bit_word&> { // Specializing to bit_word
   private:
      trie* papa;    // Pointers are better here.
      trie* lchild;
      trie* rchild;

   public:
      bit_word& w;
      int no_app;
      int dic_index;
      int depth;

      // CONSTRUCTORS
      trie();
      trie(bit_word&, int index, int depth);

      // METHODS
      // Inherited?
      int num_children(void);
      bool is_leaf(void);
      bool has_lchild(void);
      bool has_rchild(void);
      trie& get_lchild(void);
      trie& get_rchild(void);

      // New
      trie<bit_word&>* insert(bit_word&, int no=0, int count=0); // inserts and returns inserted node
      trie<bit_word&>* insert_lz(bit_word&, ifstream& in, ofstream& out, int no=0, int count=0); // Lempel-Ziv insert
//      bool path(trie&, bit_word&); // writes it in bit_word
      int cprint(int depth=0, int cnt=1);
      int pprint(int depth=0, int cnt=1);
      //trie& find(bit_word&); // returns leaf if not found
};

// Have to put this here (template shitfuck)
template <class T>
trie<T>::trie()
   : w(*(new T())) 
   , no_app(0)
   , dic_index(0)
   , depth(0)
   , papa(0)
   , lchild(0)
   , rchild(0)
{ }

template <class T>
trie<T>::trie(T word, int index, int d) 
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


template <class T>
trie<T>::~trie() {
   //cout << this << endl;
   if(lchild) {
      //cout << "l " << flush;
      delete lchild;
      this->lchild = 0;
   }
   if(rchild) {
      //cout << "r " << flush;
      delete rchild;
      this->rchild = 0;
   }
   cout << "X" << flush;
}


template <class T>
int trie<T>::num_children(void) {
   return 0;
}
template <class T>
bool trie<T>::is_leaf(void) { // Not tested
   if(w.bsize == 0) 
      return true;
   return false;
}
template <class T>
bool trie<T>::has_lchild(void) {
   if(this->lchild == 0) return false;
   else return true;
}
template <class T>
bool trie<T>::has_rchild(void) {
   if(this->rchild == 0) return false;
   else return true;
}
template <class T>
trie<T>& trie<T>::get_lchild(void) {
   return *lchild;
}
template <class T>
trie<T>& trie<T>::get_rchild(void) {
   return *rchild;
}

