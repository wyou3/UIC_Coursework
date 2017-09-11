
vcs: main.o car.o carPtr.o string.o date.o
	g++ main.o car.o carPtr.o string.o date.o -o vcs

main.o: main.cpp
	g++ -c main.cpp

car.o: car.cpp car.hpp
	g++ -c car.cpp

carPtr: carPtr.cpp carPtr.hpp
	g++ -c carPtr.cpp

string: string.cpp string.hpp
	g++ -c string.cpp

date: date.cpp date.hpp
	g++ -c date.cpp

clean:
	rm *.o vcs