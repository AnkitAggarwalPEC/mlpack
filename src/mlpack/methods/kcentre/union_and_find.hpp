/*
 * @file union_and_find.hpp
 * @author Ankit Aggarwal
 * An implementation of weighted union and find
 */
#ifndef MLPACK_METHODS_KCENTRE_UNION_AND_FIND_HPP
#define MLPACK_METHODS_KCENTRE_UNION_AND_FIND_HPP
#include <mlpack/prereqs.hpp>
namespace mlpack{
namespace KCentre{
    class UF{
        public:
            /*
             *Constructor for the Union and find DS
             */
            UF(const size_t num);
            /*
             * Destructor for the Union and find
             */
            ~UF();
            /*
             *@param x of which representative to be find
             *@return the index of the representative
             */
            size_t Find(size_t x);
            /*
             * @param x one of the component
             * @param y you guessed it other component
             */
            void Merge(const size_t x , const size_t y);
            /*
             * @param x
             * @param y
             */
            bool Connected(const size_t x , const size_t y);
            /*
             */
            size_t Size(){ return count;}

        private:
            arma::Col<size_t> parent;
            arma::ivec size;
            int count;
    };
}
}
#endif
