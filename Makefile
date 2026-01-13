build: ./src/* ./include/*
	g++ main.cpp ./src/* ./include/* -o game -lSDL3 -lSDL3_image -lSDL3_ttf -g
clean:
	rm -r ./game
