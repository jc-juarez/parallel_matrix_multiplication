// ***************************************************************************
// Multiprocessors Final Project
// 'matrix.hpp'
// Authors: Juan Carlos Juarez. A00824524 / Marisa Jacqueline Diaz. A01172917.
// ***************************************************************************

#ifndef MATRIX_
#define MATRIX_

#include <string>

namespace matrix_utils {

    class Matrix {

        // Constructor
        public:
            Matrix(std::string, std::string);
    
        // Private properties
        private:
            std::string name;
            std::string path;
            int number_columns;
            int number_rows;
            double* matrix;

        // Setter Methods
        public:
            void SetNumberColumns(int);
            void SetNumberRows(int);
            void SetMatrix(double*);

        // Getter Methods
        public:
            std::string GetName() const;
            std::string GetPath() const;
            int GetNumberColumns() const;
            int GetNumberRows() const;
            double* GetMatrix() const;

        // Update Methods
        public:
            void FreeMatrix();

    };

}

#endif
