#ifndef BITS
#define BITS
#include <bits/stdc++.h>
#endif
#ifndef UTIL_IO
#define UTIL_IO
#include "util_io.h"
#endif
#ifndef ENC
#define ENC
#include "enc.h"
#endif

#define OUT_DEF "out/out.txt"

// Modes
#define M_DEF "default"
#define M_TEST "test"
#define M_BASIC "basic"
#define M_DEC_BASIC "dec_basic"


using namespace std;

int main(int argc, char *argv[]) {
   if(argc < 2 || argc > 4) {
      narrator("Usage:");
      narrator("CFP {-mode} [file] {output}");
      return 0;
   }

   vector<string> modes = { M_DEF, M_TEST, M_BASIC, M_DEC_BASIC };

   string token, file, out;
   int fstart=1, mode=0;
   
   // Mode
   if(argv[1][0] == '-') {
      fstart++;
      token = argv[1];
      if(token.size() == 1) {
         narrator("Unrecognized option \"\"");
         return 0;
      }
      token = token.substr(1);
      
      int flag=0;
      for(int i=0; i<modes.size(); i++) {
         if(modes[i] == token) {
            flag = 1;
            mode = i;
            break;
         }
      }
      if(!flag) {
         narrator("Unrecognized option \"", token, "\"");
         return 0;
      }
   }

   // File
   if(argc > fstart) {
      file = argv[fstart];
   }
   if(argc > ++fstart) {
      out = argv[fstart];
   } else {
      narrator("No outfile provided. Using default", OUT_DEF);
      out = OUT_DEF;
   }

   // Ex
   switch(mode) {
      case 0 : // M_DEF
               narrator("No default implemented");
               break;
      case 1 : // DEBUG
               narrator("Debug mode");
               enc_test(file, out);
               break;
      case 2 : // M_BASIC
               narrator("Basic mode");
               enc_basic(file, out);
               break;
      case 3 : // M_DEC_BASIC
               narrator("Decoding basic mode");
               dec_basic(file, out);
               break;
      default: 
               narrator("No default implemented");
               break;
   }

   return 0;
}
