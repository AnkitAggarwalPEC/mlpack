/*
 *@file dual_tree_kcentre_rules_impl.hpp
 *@author Ankit Aggarwal
 *
 */
#ifndef MLPACK_METHODS_DUAL_TREE_KCENTRE_RULES_IMPL_HPP
#define MLPACK_METHODS_DUAL_TREE_KCENTRE_RULES_IMPL_HPP
#include "dual_tree_kcentre_rules.hpp"
#include "kcentre_helper.hpp"

namespace mlpack{
namespace KCentre{
    template<typename MetricType ,typename TreeType , typename MatType>
    DualTreeKcentreRules<MetricType , TreeType , MatType>::
    DualTreeKcentreRules(MatType & dataset ,
                        MetricType & metric ,
                        MatType& distances):
                        dataset(dataset),
                        distances(distances),
                        metric(metric)
    {
        //! constructor
    }
    
    template<typename MetricType ,typename TreeType , typename MatType>
    double DualTreeKcentreRules<MetricType , TreeType , MatType>::
    BaseCase(const size_t queryIndex, const size_t referenceIndex){
        //! Calculate the distance between the query point and the reference point and update the distance matrix if this can be possible centre
        double newUpperBound = -1.0;
        auto distance = metric.Evaluate(dataset.col(queryIndex), dataset.col(referenceIndex));
        //! Assumption metric(a , b) == metric(b , a)
        //! Update the distance matrix for the query index
        if(this->distances[queryIndex] > distance){
            distances[queryIndex] = distance;
        }
        //! Update the distance matrix for the reference index
        if(this->distances[referenceIndex] > distance){
            distances[referenceIndex] = distance;
        }
        if(distance >  newUpperBound) newUpperBound = distance;
        return newUpperBound;
    }
     
    template<typename MetricType ,typename TreeType , typename MatType>
    double DualTreeKcentreRules<MetricType , TreeType , MatType>::
    Rescore(const size_t queryIndex , TreeType & /*referenceNode*/ , const double oldScore){
        return distances[queryIndex] > oldScore ? oldScore:DBL_MAX;
    }

    template<typename MetricType ,typename TreeType , typename MatType>
    double DualTreeKcentreRules<MetricType , TreeType , MatType>::
    Rescore(TreeType& queryNode , TreeType & /*referenceNode*/ , const double oldScore){
        auto bound  = CalculateBound(queryNode);
        return bound > oldScore ?oldScore : DBL_MAX;
        
    }
    template<typename MetricType ,typename TreeType , typename MatType>
    double DualTreeKcentreRules<MetricType , TreeType , MatType>::
    Score(const size_t queryIndex , TreeType & referenceNode){
        const arma::vec queryPoint = dataset.unsafe_col(queryIndex);
        auto distance = referenceNode.MinDistance(queryPoint);
        return distances[queryIndex] > distance ? distance:DBL_MAX;
    }
    
    template<typename MetricType ,typename TreeType , typename MatType>
    double DualTreeKcentreRules<MetricType , TreeType , MatType>::
    Score(TreeType & queryNode , TreeType & referenceNode){
        auto distance = queryNode.MinDistance(referenceNode);
        //! Bound constains the distance
        auto bound = CalculateBound(queryNode);
        return bound > distance ? distance : DBL_MAX;
    }

    template<typename MetricType , typename TreeType , typename MatType>
    double DualTreeKcentreRules<MetricType , TreeType , MatType>::
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
            const double bound = distances[queryNode.Point(i)];
            if(bound > worstPointCentreDistance) worstPointCentreDistance = bound;
            if(bound < bestPointCentreDistance) bestPointCentreDistance = bound;
        }
        for (size_t i = 0 ; i < queryNode.NumChildren() ; ++i){
            const double maxBound = queryNode.Child(i).Stat().MaxCentreDistance(); 
            if(maxBound > worstChildCentreDistance) worstChildCentreDistance = maxBound;
            const double minBound = queryNode.Child(i).Stat().MinCentreDistance(); 
            if(minBound < bestChildCentreDistance) bestChildCentreDistance = minBound;
        }
        //! Get absolute maximum and minimum bounds for this queryNode
        const double worstBound = std::max(worstPointCentreDistance , worstChildCentreDistance);
        const double bestBound = std::min(bestPointCentreDistance , bestChildCentreDistance );
        //! This is implementation of the B2 from the 2015Improving.pdf from mlpack website
        const double bestAdjustedBound = (bestBound == DBL_MAX)? DBL_MAX: bestBound +  2* queryNode.FurthestDescendantDistance();

        queryNode.Stat().MaxCentreDistance() = worstBound;
        queryNode.Stat().MinCentreDistance() = bestBound;
        queryNode.Stat().Bound() = std::min(worstBound , bestAdjustedBound);
        return queryNode.Stat().Bound();
    }
}
}
#endif

