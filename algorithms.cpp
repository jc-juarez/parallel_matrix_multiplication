// Multiprocessors Final Project
// 'algorithms.hpp'
// Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <omp.h>
#include "matrix.hpp"

namespace algorithms {

    void SerialAlgorithm(matrix_utils::Matrix& matrix_A, matrix_utils::Matrix& matrix_B, matrix_utils::Matrix& matrix_serial, std::vector<double>& times) {

        static double current_multiplication {};

        auto start = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < matrix_A.GetNumberRows(); ++i) {
            for(int j = 0; j < matrix_B.GetNumberColumns(); ++j) {
                current_multiplication = 0.0;
                for(int k = 0; k < matrix_A.GetNumberColumns(); ++k) {
                    current_multiplication += *(matrix_A.GetMatrix() + (i * matrix_A.GetNumberColumns()) + k) * *(matrix_B.GetMatrix() + (j * matrix_B.GetNumberRows()) + k);
                } 
                *(matrix_serial.GetMatrix() + (i * matrix_B.GetNumberColumns()) + j) = current_multiplication;
            }
        }

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::stringstream time_ss {};
        time_ss << duration.count();
        double ellapsed_time = std::stod(time_ss.str());
        times.push_back(ellapsed_time);
    }

    void ParallelOMPAlgorithm(matrix_utils::Matrix& matrix_A, matrix_utils::Matrix& matrix_B, matrix_utils::Matrix& matrix_parallel_threads, std::vector<double>& times) {

        double current_multiplication {};

        auto start = std::chrono::high_resolution_clock::now();

        #pragma omp parallel for num_threads(omp_get_max_threads()) reduction(+:current_multiplication)
        for(int i = 0; i < matrix_A.GetNumberRows(); ++i) {
            for(int j = 0; j < matrix_B.GetNumberColumns(); ++j) {
                current_multiplication = 0.0;
                for(int k = 0; k < matrix_A.GetNumberColumns(); ++k) {
                    current_multiplication += *(matrix_A.GetMatrix() + (i * matrix_A.GetNumberColumns()) + k) * *(matrix_B.GetMatrix() + (j * matrix_B.GetNumberRows()) + k);
                } 
                *(matrix_parallel_threads.GetMatrix() + (i * matrix_B.GetNumberColumns()) + j) = current_multiplication;
            }
        }
        
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::stringstream time_ss {};
        time_ss << duration.count();
        double ellapsed_time = std::stod(time_ss.str());
        times.push_back(ellapsed_time);
    }

}