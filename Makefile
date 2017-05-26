CC = g++

all:
	$(CC) *.cpp -lglut -lassimp -lGLU -lGL -lSOIL -I. -o lostinmit -std=gnu++11

clean:
	rm lostinmit
