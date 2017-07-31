/*
 * @file dual_tree_kcentre.hpp
 * @author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_DUAL_TREE_KCENTRE_HPP
#define MLPACK_METHODS_DUAL_TREE_KCENTRE_HPP
#include <mlpack/core/tree/binary_space_tree.hpp>

namespace mlpack{
namespace KCentre{
/*
* An implementation of dual tree kcentre
*/
    template<typename MetricType , typename MatType = arma::mat>
    class DualTreeKcentre{
        pubic:
        /*
         * Constructor for the DualTreeKcentre
         */
        DualTreeKcentre(const MatType & dataset , MetricType & metric);
        /*
         * Destructor for the DualTreeKcentre
         */
        ~DualTreeKcentre();
        /*
         * Run the single iteration of the Dual Tree Algorithm
         */
        void Iterate(MatType & centres , size_t centreIndex);
    };
}
}
