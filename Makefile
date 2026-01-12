build: ./src/* ./include/*
	g++ main.cpp ./src/* ./include/* -o game -lSDL3
clean:
	rm -r ./game
