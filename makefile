all:
	g++ -Wall -Werror -std=c++14 -o hoarding.out *.cpp

clean:
	rm *.*.out

sortedverification: sortedverification.o
	g++ -Wall -Werror -std=c++14 -o sortedverification.o

sortedverification.o: sortedverification.cxx
	g++ -c sortedverification.cxx

consistentresultverification: consistentresultverification.o
	g++ -Wall -Werror -std=c++14 -o consistentresultverification.o

consistentresultverification.o: sortedverification.cxx
	g++ -c consistentresultverification.cxx