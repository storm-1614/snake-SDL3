build: ./src/* ./include/*
	g++ main.cpp ./src/* ./include/* -o game -lSDL3 -g
clean:
	rm -r ./game
