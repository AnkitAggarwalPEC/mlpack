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

    void print_vector(std::vector <double> & v){
        for(int  i = 0 ; i < v.size() ; i++){
            std::cout << v[i] << " " ;
        }
        std::cout << std::endl;
    }

    void print_set(std::set <size_t> & v){
        for(auto it = v.begin() ; it != v.end() ; it++){
            std::cout << *it << " " ;
        }
        std::cout << std::endl;
    }
}
}
