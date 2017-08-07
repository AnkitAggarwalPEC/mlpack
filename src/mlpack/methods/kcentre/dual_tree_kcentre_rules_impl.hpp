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
    
    template<typename MetricType , typename TreeType , typename MatType>
    DualTreeKcentreRules<MetricType , TreeType , MatType>::
    CalculateBound(TreeType & queryNode){
        //! It will be maximum distance of the centre from all the query points in queryNode
        double worstPointCentreDistance = -DBL_MAX;
        //! It will be mimimum distance of the centre from all the query points in queryNode
        double bestPointCentreDistance = DBL_MAX;

        //! It will be maximum distance of the centre from all the query childs in queryNode
        double worstChildCentreDistance = -DBL_MAX;
        //! It will be mimimum distance of the centre from all the query childs in queryNode
        double bestChildCentreDistance = DBL_MAX;

        for (size_t i = 0 ; i < queryNode.NumPoints() ; ++i){
            //! Bound will be the distance
            const double bound = 12;
            if(bound > worstPointCentreDistance) worstPointCentreDistance = bound;
            if(bound < bestPointCentreDistance) bestPointCentreDistance = bound;
        }
        for (size_t i = 0 ; i < queryNode.NumChildren() ; ++i){
            const double bound = 12;
            if(bound > worstChildCentreDistance) worstChildCentreDistance = bound;
            if(bound < bestChildCentreDistance) bestChildCentreDistance = bound;
        }
        //! Get absolute maximum and minimum bounds for this queryNode
        const double worstBound = std::max(worstPointCentreDistance , worstChildCentreDistance);
        const double bestBound = std::min(bestPointCentreDistance , bestChildCentreDistance );
        //! This is implementation of the B2 from the 2015Improving.pdf from mlpack website
        const double bestAdjustedBound = bestBound +  2* queryNode.FurthestDescendantDistance();

        queryNode.Stat().MaxCentreDistance() = worstBound;
        queryNode.Stat().MinCentreDistance() = bestBound;
        queryNode.Stat().Bound() = std::min(worstBound , bestAdjustedBound);
        return queryNode.Stat().Bound();
    }
}
}
#endif

