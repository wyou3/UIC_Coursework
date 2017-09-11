
collections: main.o Collection.o Array.o BST.o Node.o
	g++ -std=c++11 main.o Collection.o Array.o BST.o Node.o -o collections

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Collection.o: Collection.cpp Collection.hpp
	g++ -std=c++11 -c Collection.cpp

Array.o: Array.cpp Array.hpp
	g++ -std=c++11 -c Array.cpp

BST.o: BST.cpp BST.hpp 
	g++ -std=c++11 -c BST.cpp

Node.o: Node.cpp Node.hpp
	g++ -std=c++11 -c Node.cpp

clean:
	rm *.o collections