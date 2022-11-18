// ***************************************************************************
// Multiprocessors Final Project
// 'algorithms.hpp'
// Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.
// ***************************************************************************

#ifndef ALGORITHMS_
#define ALGORITHMS_

#include <vector>
#include "matrix.hpp"

namespace algorithms {

    constexpr int number_iterations {5};
    constexpr int number_threads {64};

    void SerialAlgorithm(matrix_utils::Matrix&, matrix_utils::Matrix&, matrix_utils::Matrix&, std::vector<double>&);
    void ParallelOMPAlgorithm(matrix_utils::Matrix&, matrix_utils::Matrix&, matrix_utils::Matrix&, std::vector<double>&);
    void ParallelPOSIXThreadsAlgorithm(matrix_utils::Matrix&, matrix_utils::Matrix&, matrix_utils::Matrix&, std::vector<double>&);
    void POSIXThreadWorker(int, int, int, matrix_utils::Matrix, matrix_utils::Matrix, matrix_utils::Matrix);

}

#endif