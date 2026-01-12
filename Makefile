build: ./src/* ./include/*
	g++ main.cpp ./src/* ./include/* -o game -lSDL3 -lSDL3_image -g
clean:
	rm -r ./game
