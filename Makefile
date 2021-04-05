.default: all

all: assignment1

clean:
	rm -f assignment1 *.o

assignment1: Node.o NodeList.o PathSolver.o main.o
	g++ -Wall -Werror -std=c++14 -g -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -c $^