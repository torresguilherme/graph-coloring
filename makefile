CC = g++
CFLAGS = -g3 -Wall -Wextra -pedantic -std=c++11
VFLAGS = valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all
SOURCE = main.cpp graph.cpp dsatur.cpp tabucol.cpp
EXEC = exec

all: exec

exec: FORCE
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXEC)
valgrind: exec
	$(VFLAGS) ./$(EXEC) g1
FORCE:
	
