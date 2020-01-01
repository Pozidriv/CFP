util_key.cpp:188:18: error: template-id ‘insert<>’ for ‘trie<bit_word&>* trie<bit_word&>::insert(bit_word&, int, int)’ does not match any template declaration
 trie<bit_word&>* trie<bit_word&>::insert(bit_word& new_word, int no, int len) { // Tested
                  ^~~~~~~~~~~~~~~
In file included from bitop.h:13:0,
                 from util_key.cpp:7:
util_key.h:83:24: note: candidate is: trie<bit_word&>* trie<bit_word&>::insert(bit_word&, int, int)
       trie<bit_word&>* insert(bit_word&, int no=0, int count=0); // inserts and returns inserted node
                        ^~~~~~
util_key.cpp:246:18: error: template-id ‘insert_lz<>’ for ‘trie<bit_word&>* trie<bit_word&>::insert_lz(bit_word&, std::istream&, std::ostream&, int, int)’ does not match any template declaration
 trie<bit_word&>* trie<bit_word&>::insert_lz(bit_word& buffer, istream& in, ostream& out, int no, int len) { // Not tested
                  ^~~~~~~~~~~~~~~
In file included from bitop.h:13:0,
                 from util_key.cpp:7:
util_key.h:84:24: note: candidate is: trie<bit_word&>* trie<bit_word&>::insert_lz(bit_word&, std::istream&, std::ostream&, int, int)
       trie<bit_word&>* insert_lz(bit_word&, istream& in, ostream& out, int no=0, int count=0); // Lempel-Ziv insert
                        ^~~~~~~~~
util_key.cpp:298:5: error: template-id ‘pprint<>’ for ‘int trie<bit_word&>::pprint(int, int)’ does not match any template declaration
 int trie<bit_word&>::pprint(int depth, int cnt) {
     ^~~~~~~~~~~~~~~
In file included from bitop.h:13:0,
                 from util_key.cpp:7:
util_key.h:87:11: note: candidate is: int trie<bit_word&>::pprint(int, int)
       int pprint(int depth=0, int cnt=1);
           ^~~~~~
util_key.cpp:311:5: error: template-id ‘cprint<>’ for ‘int trie<bit_word&>::cprint(int, int)’ does not match any template declaration
 int trie<bit_word&>::cprint(int depth, int cnt) {
     ^~~~~~~~~~~~~~~
In file included from bitop.h:13:0,
                 from util_key.cpp:7:
util_key.h:86:11: note: candidate is: int trie<bit_word&>::cprint(int, int)
       int cprint(int depth=0, int cnt=1);
           ^~~~~~
util_key.cpp:323:6: error: template-id ‘path<>’ for ‘bool trie<bit_word&>::path(trie<bit_word&>&, bit_word&)’ does not match any template declaration
 bool trie<bit_word&>::path(trie<bit_word&> &t, bit_word &word) { // not needed?
      ^~~~~~~~~~~~~~~
In file included from bitop.h:13:0,
                 from util_key.cpp:7:
util_key.h:85:12: note: candidate is: bool trie<bit_word&>::path(trie<bit_word&>&, bit_word&)
       bool path(trie&, bit_word&); // writes it in bit_word
            ^~~~
make: *** [util_key.o] Error 1
