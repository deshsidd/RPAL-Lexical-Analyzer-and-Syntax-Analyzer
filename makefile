all:
	g++ -g -w -Wall -o p1 main.cpp parser.cpp scanner.cpp token.cpp tree.cpp
cl:
	rm -f *.o p1

