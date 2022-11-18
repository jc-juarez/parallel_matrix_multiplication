// ***************************************************************************
// Multiprocessors Final Project
// 'utils.hpp'
// Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.
// ***************************************************************************

#ifndef UTILS_
#define UTILS_

#include <vector>
#include "matrix.hpp"

namespace matrix_utils {

    void CheckMatrixAvailability(Matrix&);
    void AllocateMatrixMemory(Matrix&);
    void FillMatrix(Matrix&);
    void TransposeMatrix(Matrix&);
    void WriteToFile(Matrix&);
    void PrintResults(std::vector<double>&, std::vector<double>&, std::vector<double>&);
    bool MatricesAreEqual(Matrix&, Matrix&);

}

#endif