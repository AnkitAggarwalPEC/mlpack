/*
 * @file dual_tree_kcentre_impl.hpp
 * @author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_DUAL_TREE_KCENTRE_IMPL_HPP
#define MLPACK_METHODS_DUAL_TREE_KCENTRE_IMPL_HPP
#include "dual_tree_kcentre.hpp"
namespace mlpack{
namespace KCentre{
/*An implementation of Dual Tree Kcentre
 */
    template <typename MetricType , typename MatType>
    DualTreeKCentre<MetricType , MatType>::
    DualTreeKCentre(const MatType & dataset , MetricType & metric):
        distance.set_size(dataset.n_cols)
    {
        //! Set the default distance
        distance.fill(-DBL_MAX);
    }

    template <typename MetricType , typename MatType>
    DualTreeKCentre<MetricType , MatType>::
    Iterate(MatType & centres , size_t centreIndex){
    }
    
}
}
#endif
