#pragma once
// Helper class for the debug purpose
//
#include <iostream>
#include <armadillo>
namespace mlpack{
namespace KCentre{
    
    template <class Matrix>
    void print_matrix(Matrix matrix){
        matrix.print(std::cout);
    }
    template <class Matrix>
    void print_matrix(Matrix matrix , int row){
        matrix.col(row).print(std::cout);
    }
}
}
