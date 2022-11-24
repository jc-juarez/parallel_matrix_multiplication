// ***************************************************************************
// Multiprocessors Final Project
// 'main.cpp'
// Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.
// ***************************************************************************

#include <iostream>
#include <string>
#include <vector>
#include "algorithms.hpp"
#include "matrix.hpp"
#include "utils.hpp"

int main() {

    // Welcome message
    std::cout << "\n<<< Serial and Parallel Algorithms for Matrix Multiplication >>>\n";

    // Initial matrices creation
    matrix_utils::Matrix matrix_A("Matrix A", "matrixA.txt");
    matrix_utils::Matrix matrix_B("Matrix B", "matrixB.txt");

    // Input number iterator
    int input_number {};

    // Matrices dimensions
    std::cout << "\n- Enter number of rows of Matrix A: ";
    std::cin >> input_number;
    matrix_A.SetNumberRows(input_number);
    std::cout << "- Enter number of columns of Matrix A: ";
    std::cin >> input_number;
    matrix_A.SetNumberColumns(input_number);
    std::cout << "- Enter number of rows of Matrix B: ";
    std::cin >> input_number;
    matrix_B.SetNumberRows(input_number);
    std::cout << "- Enter number of columns of Matrix B: ";
    std::cin >> input_number;
    matrix_B.SetNumberColumns(input_number);
    std::cout << "\n";

    // Check multiplication possibility
    if(matrix_A.GetNumberColumns() != matrix_B.GetNumberRows())
        throw std::runtime_error("Matrices cannot be multiplied due to dimensions mismatching.");

    // Check matrices population availability
    matrix_utils::CheckMatrixAvailability(matrix_A);
    matrix_utils::CheckMatrixAvailability(matrix_B);

    // Resulting matrices creation
    matrix_utils::Matrix matrix_serial("Matrix Serial", "matrixC.txt");
    matrix_utils::Matrix matrix_parallel_omp("Matrix Parallel OMP", "");
    matrix_utils::Matrix matrix_parallel_threads("Matrix Parallel Threads", "");

    // Resulting matrices dimensions
    matrix_serial.SetNumberRows(matrix_A.GetNumberRows());
    matrix_serial.SetNumberColumns(matrix_B.GetNumberColumns());
    matrix_parallel_omp.SetNumberRows(matrix_A.GetNumberRows());
    matrix_parallel_omp.SetNumberColumns(matrix_B.GetNumberColumns());
    matrix_parallel_threads.SetNumberRows(matrix_A.GetNumberRows());
    matrix_parallel_threads.SetNumberColumns(matrix_B.GetNumberColumns());

    // Memory allocation
    matrix_utils::AllocateMatrixMemory(matrix_A);
    matrix_utils::AllocateMatrixMemory(matrix_B);
    matrix_utils::AllocateMatrixMemory(matrix_serial);
    matrix_utils::AllocateMatrixMemory(matrix_parallel_omp);
    matrix_utils::AllocateMatrixMemory(matrix_parallel_threads);

    // Matrices filling
    matrix_utils::FillMatrix(matrix_A);
    matrix_utils::FillMatrix(matrix_B);

    // Transpose Matrix B for multiplying on same number of rows and columns
    matrix_utils::TransposeMatrix(matrix_B);

    // Vectors for storing ellapsed times for each algorithm
    std::vector<double> serial_times {};
    std::vector<double> parallel_omp_times {};
    std::vector<double> parallel_threads_times {};

    // Serial algorithm matrix multiplication
    for(int i = 0; i < algorithms::number_iterations; ++i)
        algorithms::SerialAlgorithm(matrix_A, matrix_B, matrix_serial, serial_times);

    // Serial algorithm matrix file writing
    matrix_utils::WriteToFile(matrix_serial);

    // Parallel algorithms number of threads designation
    int number_elements = matrix_serial.GetNumberRows() * matrix_serial.GetNumberColumns();
    int current_number_threads = algorithms::number_threads;
    if((number_elements) < current_number_threads)
        current_number_threads = number_elements;
    std::cout << "< Parallel algorithms running on " << current_number_threads << " threads >\n\n";

    // Parallel OpenMP algorithm matrix multiplication
    for(int i = 0; i < algorithms::number_iterations; ++i)
        algorithms::ParallelOMPAlgorithm(matrix_A, matrix_B, matrix_parallel_omp, parallel_omp_times);

    // Parallel POSIX Threads matrix multiplication
    for(int i = 0; i < algorithms::number_iterations; ++i)
        algorithms::ParallelPOSIXThreadsAlgorithm(matrix_A, matrix_B, matrix_parallel_threads, parallel_threads_times);

    // Print out to console if parallel matrices are equal to serial matrix
    std::cout << "<> Matrix '" << matrix_serial.GetName() << "' and Matrix '" << matrix_parallel_omp.GetName() << "' are ";
    if(matrix_utils::MatricesAreEqual(matrix_serial, matrix_parallel_omp)) std::cout << "Equal.\n";
    else std::cout << "Different.\n";
    std::cout << "<> Matrix '" << matrix_serial.GetName() << "' and Matrix '" << matrix_parallel_threads.GetName() << "' are ";
    if(matrix_utils::MatricesAreEqual(matrix_serial, matrix_parallel_threads)) std::cout << "Equal.\n";
    else std::cout << "Different.\n";

    // Results Table printing
    matrix_utils::PrintResults(serial_times, parallel_omp_times, parallel_threads_times);
    
    
    // Free matrices
    matrix_A.FreeMatrix();
    matrix_B.FreeMatrix();
    matrix_serial.FreeMatrix();
    matrix_parallel_omp.FreeMatrix();
    matrix_parallel_threads.FreeMatrix();

    return 0;
}
