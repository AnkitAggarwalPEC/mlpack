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
    
    void print_vector(std::vector <size_t> & v){
        for(int  i = 0 ; i < v.size() ; i++){
            std::cout << v[i] << " " ;
        }
        std::cout << std::endl;
    }
}
}
