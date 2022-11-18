output: main.o matrix.o utils.o algorithms.o
	g++ main.o matrix.o utils.o algorithms.o -o output -fopenmp
	rm *.o

main.o: main.cpp
	g++ -c main.cpp -fopenmp

matrix.o: matrix.cpp matrix.hpp
	g++ -c matrix.cpp -fopenmp

utils.o: utils.cpp utils.hpp
	g++ -c utils.cpp -fopenmp

algorithms.o: algorithms.cpp algorithms.hpp
	g++ -c algorithms.cpp -fopenmp

clean:
	rm *.o output