/*
 * @file union_and_find_impl.hpp
 * @author Ankit Aggarwal
 */
#ifndef MLPACK_KCENTRE_UNION_AND_FIND_IMPL_HPP
#define MLPACK_KCENTRE_UNION_AND_FIND_IMPL_HPP
#include "union_and_find.hpp"
namespace mlpack{
namespace KCentre{
UF::UF(const size_t num):
    parent(num),
    size(num),
    count(num)
    {
        for (int i = 0 ; i < num ; i++){
            parent[i] = i;
            size[i] = 1;
        }
    }

UF::~UF(){}

size_t UF::Find(size_t x){
    size_t root = x;
    //! get the root upstream
    while(root != parent[x]){
        root = parent[root];
    }
    //! Update the root downstream
    while(root != x){
        size_t old_parent = parent[x];
        parent[x] = root;
        x = old_parent;
    }
    return root;

}

void UF::Merge(const size_t x , const size_t y){
    size_t i = Find(x);
    size_t j = Find(y);
    if( i == j ) return ;
    if(size[i] < size[j]){
        parent[i] = j;
        size[j] += size[i];
    }else{
        parent[j] = i;
        size[i]  +=  size[j];
    }
    count-- ;
}

bool UF::Connected(const size_t x , const size_t y){
    return Find(x) == Find(y);
}
}
}
#endif

