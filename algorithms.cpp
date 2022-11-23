// ***************************************************************************
// Multiprocessors Final Project
// 'algorithms.cpp'
// Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.
// ***************************************************************************

#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <chrono>
#include "algorithms.hpp"
#include "matrix.hpp"

namespace algorithms {

    void SerialAlgorithm(matrix_utils::Matrix& matrix_A, matrix_utils::Matrix& matrix_B, matrix_utils::Matrix& matrix_serial, std::vector<double>& times) {

        auto start = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < matrix_A.GetNumberRows(); ++i) {
            for(int j = 0; j < matrix_B.GetNumberColumns(); ++j) {
                double current_multiplication {};
                for(int k = 0; k < matrix_A.GetNumberColumns(); ++k) {
                    current_multiplication += *(matrix_A.GetMatrix() + (i * matrix_A.GetNumberColumns()) + k) * *(matrix_B.GetMatrix() + (j * matrix_B.GetNumberRows()) + k);
                } 
                *(matrix_serial.GetMatrix() + (i * matrix_B.GetNumberColumns()) + j) = current_multiplication;
            }
        }

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::stringstream time_ss {};
        time_ss << duration.count();
        double ellapsed_time = std::stod(time_ss.str()) / 1000000.0;
        times.push_back(ellapsed_time);
    }

    void ParallelOMPAlgorithm(matrix_utils::Matrix& matrix_A, matrix_utils::Matrix& matrix_B, matrix_utils::Matrix& matrix_parallel_omp, std::vector<double>& times) {

        int number_elements = matrix_parallel_omp.GetNumberRows() * matrix_parallel_omp.GetNumberColumns();

        int current_number_threads = number_threads;
        if((number_elements) < current_number_threads)
            current_number_threads = number_elements;

        auto start = std::chrono::high_resolution_clock::now();

        #pragma omp parallel for num_threads(current_number_threads)
        for(int matrix_index = 0; matrix_index < number_elements; ++matrix_index) {
            int j = matrix_index - ((matrix_index / matrix_B.GetNumberColumns()) * matrix_B.GetNumberColumns());
            int i = (matrix_index - j) / matrix_B.GetNumberColumns();
            double current_multiplication {};
            for(int k = 0; k < matrix_A.GetNumberColumns(); ++k) {
                current_multiplication += *(matrix_A.GetMatrix() + (i * matrix_A.GetNumberColumns()) + k) * *(matrix_B.GetMatrix() + (j * matrix_B.GetNumberRows()) + k);
            } 
            *(matrix_parallel_omp.GetMatrix() + matrix_index) = current_multiplication;
        }
        
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::stringstream time_ss {};
        time_ss << duration.count();
        double ellapsed_time = std::stod(time_ss.str()) / 1000000.0;
        times.push_back(ellapsed_time);
    }

    void ParallelPOSIXThreadsAlgorithm(matrix_utils::Matrix& matrix_A, matrix_utils::Matrix& matrix_B, matrix_utils::Matrix& matrix_parallel_threads, std::vector<double>& times) {

        int number_elements = matrix_parallel_threads.GetNumberRows() * matrix_parallel_threads.GetNumberColumns();

        std::vector<std::thread> threads;

        int current_number_threads = number_threads;
        if((number_elements) < current_number_threads)
            current_number_threads = number_elements;

        auto start = std::chrono::high_resolution_clock::now();

        for(int thread_number = 0; thread_number < current_number_threads; ++thread_number) {
            int start = thread_number * (number_elements / current_number_threads);
            int stop = start + (number_elements / current_number_threads);
            threads.push_back(std::thread(POSIXThreadWorker, start, stop, matrix_A, matrix_B, matrix_parallel_threads));
        }

        // Serial leftover
        if(number_elements %  current_number_threads) {
            int start = number_elements - (number_elements %  current_number_threads);
            int stop = start + (number_elements %  current_number_threads);
            POSIXThreadWorker(start, stop, matrix_A, matrix_B, matrix_parallel_threads);
        }
        
        for(auto& thread : threads)
            thread.join();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::stringstream time_ss {};
        time_ss << duration.count();
        double ellapsed_time = std::stod(time_ss.str()) / 1000000.0;
        times.push_back(ellapsed_time);
    }

    void POSIXThreadWorker(int start, int stop, matrix_utils::Matrix matrix_A, matrix_utils::Matrix matrix_B, matrix_utils::Matrix matrix_parallel_threads) {

        for(int matrix_index = start; matrix_index < stop; ++matrix_index) {
            int j = matrix_index - ((matrix_index / matrix_B.GetNumberColumns()) * matrix_B.GetNumberColumns());
            int i = (matrix_index - j) / matrix_B.GetNumberColumns();
            double current_multiplication {};
            for(int k = 0; k < matrix_A.GetNumberColumns(); ++k) {
                current_multiplication += *(matrix_A.GetMatrix() + (i * matrix_A.GetNumberColumns()) + k) * *(matrix_B.GetMatrix() + (j * matrix_B.GetNumberRows()) + k);
            } 
            *(matrix_parallel_threads.GetMatrix() + matrix_index) = current_multiplication;
        }
    }

}