all: sum-nbo

sum-nbo: sum-nbo.cpp
	g++ -g -o sum-nbo sum-nbo.cpp

clean:
	rm -f sum-nbo
	rm -f *.o

