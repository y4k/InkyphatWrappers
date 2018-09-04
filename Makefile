CC=g++
CXXFLAGS=Wall -g
DEPS=main.cpp inkyphat.cpp
LINKS=-lwiringPi

all:
	mkdir -p build
	$(CC) -$(CXXFLAGS) -std=c++11 $(DEPS) $(LINKS) -o build/main.out

clean:
	rm build/*
