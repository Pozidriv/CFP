run : main.cpp util_io.o enc.o bitop.o util_key.o
	g++ -o CPF -std=c++11 main.cpp util_io.o util_key.o bitop.o enc.o

util_io.o : util_io.h util_io.cpp util_io.inl
	g++ -c util_io.cpp

enc.o : enc.h enc.cpp bitop.o util_key.o
	g++ -c enc.cpp

bitop.o : bitop.h bitop.cpp
	g++ -c bitop.cpp

util_key.o : util_key.h util_key.cpp bitop.o
	g++ -c util_key.cpp

clean : 
	rm *.o CPF
