all: jaria

jaria: jaria.o
	g++ libjAria.o -shared -m64 -fPIC -laria2 -o libjAria.dylib

jaria.o:
	g++ -m64 -c main.cpp  -laria2 -o libjAria.o