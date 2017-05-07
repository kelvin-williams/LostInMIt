CC = g++

all:
	$(CC) main.cpp -lglut -lassimp -lGLU -lGL -I. -o lostinmit -std=gnu++11

clean:
	rm lostinmit
