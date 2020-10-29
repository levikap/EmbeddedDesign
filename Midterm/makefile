SnakesAndLadders: DE1SoCfpga.o main.o SnakesAndLadders.o MenuHandler.o TonePlayer.o
	g++ DE1SoCfpga.o main.o SnakesAndLadders.o MenuHandler.o TonePlayer.o -o SnakesAndLadders

DE1SoCfpga.o: DE1Socfpga.cpp DE1SoCfpga.h
	g++ -g -Wall -c DE1SoCfpga.cpp

main.o: main.cpp MenuHandler.h
	g++ -g -Wall -c main.cpp

SnakesAndLadders.o: SnakesAndLadders.cpp SnakesAndLadders.h
	g++ -g -Wall -c SnakesAndLadders.cpp

MenuHandler.o: MenuHandler.cpp MenuHandler.h
	g++ -g -Wall -c MenuHandler.cpp

TonePlayer.o: TonePlayer.cpp TonePlayer.h
	g++ -g -Wall -c TonePlayer.cpp

clean:
	rm DE1SoCfpga.o main.o SnakesAndLadders.o MenuHandler.o TonePlayer.o SnakesAndLadders
