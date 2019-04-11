T3: T3.o tictactoe.o
	g++ -g -o T3 T3.o tictactoe.o

T3.o: T3.cpp
	g++ -o T3.o -c T3.cpp

tictactoe.o: tictactoe.cpp
	g++ -o tictactoe.o -c tictactoe.cpp

clean:
	$[rm] *.o T3
