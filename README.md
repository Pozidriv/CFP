# Compressed File Protocols

Compilation: if necessary change the compiler flags, the default is `g++`. Make sure you compile with `c++11` or higher.

Then run
```
make
```

Usage:
```
CFP [-option] [input file] [output file]
```

Currently implemented options (very incomplete):
* `basic` a basic LZW implementation. Unfortunately the decoder for the output still needs to be implemented.
