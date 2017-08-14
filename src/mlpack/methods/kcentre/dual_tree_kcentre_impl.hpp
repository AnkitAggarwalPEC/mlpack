/*
 * @file dual_tree_kcentre_impl.hpp
 * @author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_DUAL_TREE_KCENTRE_IMPL_HPP
#define MLPACK_METHODS_DUAL_TREE_KCENTRE_IMPL_HPP
#include <mlpack/prereqs.hpp>
#include <mlpack/core/tree/binary_space_tree.hpp>
#include "dual_tree_kcentre.hpp"

namespace mlpack{
namespace KCentre{

template <typename TreeType , typename MatType = arma::mat>
TreeType * BuildTree(MatType & dataset ,
        const typename std::enable_if<!tree::TreeTraits<TreeType>::RearrangesDataset>::type* = 0){
        return new TreeType(std::forward<MatType>(dataset));
}
/*An implementation of Dual Tree Kcentre
 */
    template <typename MetricType , typename MatType>
    DualTreeKCentre<MetricType , MatType>::
    DualTreeKCentre(MatType & dataset , MetricType & metric):
        metric(metric),
        dataset(dataset),
        tree(BuildTree<TreeType>(dataset))
    {
        //! Set the default distance
        distances.set_size(dataset.n_cols),
        distances.fill(-DBL_MAX);
    }
    

    template <typename MetricType , typename MatType>
    void DualTreeKCentre<MetricType , MatType>::
    Initialize(MatType & centres , size_t initial_centre){

        for (size_t index =  0 ; index < dataset.n_cols ; index++){
            distances.col(index) = metric.Evaluate(centres.col(initial_centre), dataset.col(index));
        }
    }

    template <typename MetricType , typename MatType>
    void DualTreeKCentre<MetricType , MatType>::
    ComputeKcentre(MatType & centres ,  size_t num_centres , size_t max_iterations){
        Initialize(centres , 0 );
        RulesType rules(dataset , metric , distances);
        for(auto iteration = 1 ; iteration < max_iterations && iteration < num_centres ; iteration++){
            //! Create a traverser;
            typename TreeType:: template DualTreeTraverser<RulesType> traverser(rules);
            traverser.Traverse(*tree , *tree);
            //! Select the new centre
            auto new_centre = SelectNewCentre();
            centres.col(iteration) = dataset.col(new_centre);
        }
    }

    template <typename MetricType , typename MatType>
    size_t DualTreeKCentre<MetricType , MatType>::
    SelectNewCentre(){
        auto max_distance = -DBL_MAX;
        size_t new_centre = -1;
        for (size_t index =  0 ; index < dataset.n_cols ; index++){
            if (distances[index] > max_distance){
                max_distance = distances[index];
                new_centre = index;
            }
        }
        return new_centre;
    }


}
}
#endif
