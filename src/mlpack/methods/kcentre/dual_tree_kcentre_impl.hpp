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
        distance.set_size(dataset.n_cols),
        this->metric(metric),
        this->dataset(dataset)
        this->tree(BuildTree<MetricType , MetricType>(dataset))
    {
        //! Set the default distance
        distance.fill(-DBL_MAX);
    }
    
    template <typename MetricType , typename MatType>
    TreeType * DualTreeKCentre<MetricType , MatType>::
    BuildTree(MatType && dataset){
        return new TreeType(std::forward<MatType>(dataset));
    }

    template <typename MetricType , typename MatType>
    DualTreeKCentre<MetricType , MatType>::
    Intialize(MatType & centres , size_t initial_centre){

        for (size_t index =  0 ; index < dataset.n_cols ; index++){
            distance.col(index) = metric.Evaluate(centres.col(initial_centre), dataset.col(index));
        }
    }

    template <typename MetricType , typename MatType>
    DualTreeKCentre<MetricType , MatType>::
    void ComputeKCentre(MatType & centres ,  size_t num_centres , size_t max_iterations){
        Intialize();
        for(auto iteration = 1 ; iteration < max_iterations && iteration < num_centres ; iteration++){
            //! Create a traverser;
            typename TreeType:: template DualTreeTraverser<RuleType> traverser(rules);
            traverser.Traverse(*tree , *tree);
            //! Select the new centre
        }
    }
    
}
}
#endif
