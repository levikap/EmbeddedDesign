# SevenSegment program Makefile
SevenSegment: DE1SoCfpga.o main.o SevenSegment.o
	g++ DE1SoCfpga.o main.o SevenSegment.o -o SevenSegment

main.o: main.cpp SevenSegment.h
	g++ -g -Wall -c main.cpp

SevenSegment.o: SevenSegment.cpp SevenSegment.h
	g++ -g -Wall -c SevenSegment.cpp

clean:
	rm DE1SoCfpga.o main.o SevenSegment.o SevenSegment
