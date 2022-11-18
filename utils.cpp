// ***************************************************************************
// Multiprocessors Final Project
// 'utils.cpp'
// Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.
// ***************************************************************************

#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "matrix.hpp"

namespace matrix_utils {

    void CheckMatrixAvailability(Matrix& matrix) {
        std::string error_ss {};
        try {
            int number_elements {};
            std::string line {};
            std::ifstream matrix_file(matrix.GetPath());

            if(!matrix_file.good()) {
                error_ss.append("The file '" + matrix.GetPath() + "' does not exist.");
                throw std::runtime_error(error_ss);
            }

            while (std::getline(matrix_file, line)) ++number_elements;

            int minimum_elements = matrix.GetNumberRows() * matrix.GetNumberColumns();

            if(minimum_elements > number_elements) {
                error_ss.append("'" + matrix.GetName() + "' requires at least " + std::to_string(minimum_elements) + " elements but only " + std::to_string(number_elements) + " were found in file '" + matrix.GetPath() + "'.");
                throw std::runtime_error(error_ss);
            }
        } catch(...) {
            error_ss.append(" An error ocurred while trying to check availability for '" + matrix.GetName() + "' with file '" + matrix.GetPath() + "'.");
            throw std::runtime_error(error_ss);
        }
    }

    void AllocateMatrixMemory(Matrix& matrix) {
        double* ptr = (double*) malloc(sizeof(double) * matrix.GetNumberRows() * matrix.GetNumberColumns());
        if(ptr == NULL) {
            std::string error_ss {};
            error_ss.append("Not enough memory available to allocate content for '" + matrix.GetName() + "'.");
            throw std::runtime_error(error_ss);
        }
        matrix.SetMatrix(ptr);
    }

    void FillMatrix(Matrix& matrix) {
        std::string error_ss {}; 
        try {
            int number_filled_elements {};
            int number_required_elements {matrix.GetNumberRows() * matrix.GetNumberColumns()};
            std::string line {};
            std::ifstream matrix_file(matrix.GetPath());

            if(!matrix_file.good()) {
                error_ss.append("The file '" + matrix.GetPath() + "' does not exist.");
                throw std::runtime_error(error_ss);
            }

            double* ptr = matrix.GetMatrix();
            while (std::getline(matrix_file, line) && (number_filled_elements < number_required_elements)) {
                *ptr = std::stod(line);
                ptr++;
                number_filled_elements++;
            }

        } catch(...) {
            error_ss.append(" An error ocurred while trying to fill '" + matrix.GetName() + "' with file '" + matrix.GetPath() + "'.");
            throw std::runtime_error(error_ss);
        }
    }

    void TransposeMatrix(Matrix& matrix) {
        double* ptr_transposed = (double*) malloc(sizeof(double) * matrix.GetNumberRows() * matrix.GetNumberColumns());
        for(int i = 0; i < matrix.GetNumberRows(); ++i) {
            for(int j = 0; j < matrix.GetNumberColumns(); ++j) {
                *(ptr_transposed + (j * matrix.GetNumberRows()) + i) = *(matrix.GetMatrix() + (i * matrix.GetNumberColumns()) + j);
            }
        }
        matrix.FreeMatrix();
        matrix.SetMatrix(ptr_transposed);
    }

    void WriteToFile(Matrix& matrix) {
        std::string error_ss {}; 
        try {
            std::ofstream matrix_file(matrix.GetPath());

            if(!matrix_file.good()) {
                error_ss.append("The file '" + matrix.GetPath() + "' does not exist.");
                throw std::runtime_error(error_ss);
            }

            matrix_file << std::fixed;

            double* ptr = matrix.GetMatrix();
            for(int i = 0; i < (matrix.GetNumberRows() * matrix.GetNumberColumns()); ++i) {
                matrix_file << std::setprecision(10) << *(ptr) << "\n";
                ptr++;
            }

        } catch(...) {
            error_ss.append(" An error ocurred while trying to write to file '" + matrix.GetPath() + "' with matrix '" + matrix.GetName() + "'.");
            throw std::runtime_error(error_ss);
        }
    }

    void PrintResults(std::vector<double>& serial_times, std::vector<double>& parallel_omp_times, std::vector<double>& parallel_threads_times) {
        std::cout << "\n- Iteration  |  Serial Algorithm (ms)  |  Parallel OMP Algorithm (ms)  |  Parallel POSIX Threads Algorithm (ms)\n";
        std::cout << "---------------------------------------------------------------------------------------------------------------\n";
        for(size_t i = 0; i < serial_times.size(); ++i)
            std::cout << std::setw(1) << "-" << std::setw(6) << (i+1) << std::setw(7) << "|" << std::setw(13) << serial_times[i] << std::setw(13) << "|" << std::setw(16) << parallel_omp_times[i] << std::setw(16) << "|" << std::setw(20) << parallel_threads_times[i] << "\n";
        
        double avg_serial {std::accumulate(serial_times.begin(), serial_times.end(), 0.0) / serial_times.size()};
        double avg_parallel_omp {std::accumulate(parallel_omp_times.begin(), parallel_omp_times.end(), 0.0) / parallel_omp_times.size()};
        double avg_parallel_threads {std::accumulate(parallel_threads_times.begin(), parallel_threads_times.end(), 0.0) / parallel_threads_times.size()};

        std::cout << "---------------------------------------------------------------------------------------------------------------\n";
        std::cout << std::setw(1) << "-  " << std::setw(6) << "Average" << std::setw(4) << "|" << std::setw(13) << avg_serial << std::setw(13) << "|" << std::setw(16) << avg_parallel_omp << std::setw(16) << "|" << std::setw(20) << avg_parallel_threads << "\n";

        double performance_increase_parallel_omp {((avg_serial - avg_parallel_omp) / avg_serial) * 100.0};
        double performance_increase_parallel_threads {((avg_serial - avg_parallel_threads) / avg_serial) * 100.0};

        std::cout << "---------------------------------------------------------------------------------------------------------------\n";
        std::cout << std::fixed;
        std::cout << std::setw(1) << " " << std::setw(6) << "% vs Serial" << std::setw(2) << "|" << std::setw(12) << "-" << std::setw(14) << "|" << std::setw(15) << std::setprecision(1) << performance_increase_parallel_omp << "%" << std::setw(16) << "|" << std::setw(19) << std::setprecision(1) << performance_increase_parallel_threads << "%" << "\n";

        std::cout << std::fixed;
        std::cout << "\n<> Best performing algorithm is: ";
        if(avg_parallel_omp < avg_serial && avg_parallel_omp < avg_parallel_threads) {
            std::cout << "Parallel OMP Algorithm with an average of " << std::setprecision(1) << avg_parallel_omp << " (ms).\n\n";
        } else if(avg_parallel_threads < avg_serial && avg_parallel_threads < avg_parallel_omp) {
            std::cout << "Parallel POSIX Threads Algorithm with an average of " << std::setprecision(1) << avg_parallel_threads << " (ms).\n\n";
        } else {
            std::cout << "Serial Algorithm with an average of " << std::setprecision(1) << avg_serial << " (ms).\n\n";
        }
    }

    bool MatricesAreEqual(Matrix& matrix_1, Matrix& matrix_2) {
        double* ptr_matrix_1 = matrix_1.GetMatrix();
        double* ptr_matrix_2 = matrix_2.GetMatrix();

        for(int i = 0; i < (matrix_1.GetNumberRows() * matrix_1.GetNumberColumns()); ++i){
            if(*ptr_matrix_1 != *ptr_matrix_2) return false;
            ptr_matrix_1++;
            ptr_matrix_2++;
        }
        return true;
    }

}