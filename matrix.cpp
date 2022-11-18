// ***************************************************************************
// Multiprocessors Final Project
// 'matrix.cpp'
// Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.
// ***************************************************************************

#include <string>
#include "matrix.hpp"

namespace matrix_utils {

    Matrix::Matrix(std::string _name, std::string _path) {
        name = _name;
        path = _path;
    }
    
    void Matrix::SetNumberColumns(int _number_columns) { number_columns = _number_columns; }

    void Matrix::SetNumberRows(int _number_rows) { number_rows = _number_rows; }

    void Matrix::SetMatrix(double* _matrix) { matrix = _matrix; }

    std::string Matrix::GetName() const { return name; };

    std::string Matrix::GetPath() const { return path; }

    int Matrix::GetNumberColumns() const { return number_columns; }

    int Matrix::GetNumberRows() const { return number_rows; }

    double* Matrix::GetMatrix() const { return matrix; }

    void Matrix::FreeMatrix() { 
        free(matrix);
        matrix = NULL;
    }

}