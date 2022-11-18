# ***************************************************************************
# Multiprocessors Final Project
# 'Makefile'
# Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.
# ***************************************************************************

output: main.o matrix.o utils.o algorithms.o
	g++ main.o matrix.o utils.o algorithms.o -o output -fopenmp -pthread
	rm *.o

main.o: main.cpp
	g++ -c main.cpp -fopenmp -pthread

matrix.o: matrix.cpp matrix.hpp
	g++ -c matrix.cpp -fopenmp -pthread

utils.o: utils.cpp utils.hpp
	g++ -c utils.cpp -fopenmp -pthread

algorithms.o: algorithms.cpp algorithms.hpp
	g++ -c algorithms.cpp -fopenmp -pthread

clean:
	rm *.o output