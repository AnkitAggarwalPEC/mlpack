/*
 *@file dual_tree_kcentre_rules_impl.hpp
 *@author Ankit Aggarwal
 *
 */
#ifndef MLPACK_METHODS_DUAL_TREE_KCENTRE_RULES_IMPL_HPP
#define MLPACK_METHODS_DUAL_TREE_KCENTRE_RULES_IMPL_HPP
#include "dual_tree_kcentre_rules.hpp"

namespace mlpack{
namespace KCentre{
    template<typename MetricType ,typename TreeType , typename MatType>
    DualTreeKcentreRules<MetricType , TreeType , MatType>::
    DualTreeKcentreRules(const MatType & dataset ,
                        MetricType & metric ,
                        UF & connections,
                        arma::vec& distances):
                        dataset(dataset),
                        connections(connections),
                        distances(distances),
                        metric(metric)
    {
        //! constructor
    }
    
    template<typename MetricType ,typename TreeType , typename MatType>
    DualTreeKcentreRules<MetricType , TreeType , MatType>::
    BaseCase(const size_t queryIndex, const size_t referenceIndex){
        
    }
}
}
#endif

