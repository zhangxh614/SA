all:sa

sa:main.cpp sa.cpp
	g++ -o sa.out main.cpp sa.cpp -g -std=c++11

TSPtest:TSPtest.cpp
	g++ -o TSPtest.out TSPtest.cpp -g -std=c++11

KnapsackTest:KnapsackTest.cpp
	g++ -o KnapsackTest.out KnapsackTest.cpp -g -std=c++11

clean:
	rm *.out
