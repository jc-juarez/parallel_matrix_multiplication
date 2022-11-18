#ifndef ALGORITHMS_
#define ALGORITHMS_

// Multiprocessors Final Project
// 'algorithms.hpp'
// Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.

#include <vector>
#include "matrix.hpp"

namespace algorithms {

    constexpr int number_iterations {5};

    void SerialAlgorithm(matrix_utils::Matrix&, matrix_utils::Matrix&, matrix_utils::Matrix&, std::vector<double>&);
    void ParallelOMPAlgorithm(matrix_utils::Matrix&, matrix_utils::Matrix&, matrix_utils::Matrix&, std::vector<double>&);

}

#endif