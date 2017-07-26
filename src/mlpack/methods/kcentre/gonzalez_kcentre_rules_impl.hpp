/*
 * @file gonzalez_kcentre_rules_impl.hpp
 * @Author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_KCENTRE_GONZALEZ_KCENTRE_RULES_IMPL_HPP
#define MLPACK_METHODS_KCENTRE_GONZALEZ_KCENTRE_RULES_IMPL_HPP
#include "gonzalez_kcentre_rules.hpp"
#include "kcentre_helper.hpp"

namespace mlpack{
namespace KCentre{
    template <
            typename MetricType,
            typename TreeType,
            typename MatType>
    GonzalezKcentreRules<
                        MetricType,
                        TreeType,
                        MatType> ::
    GonzalezKcentreRules(const MatType & dataset,
                        MatType & centres,
                        MetricType & metric,
                        int centreIndex,
                        int &farthestPointIndex,
                        TreeType ** nodePtr
                        ):
        dataset(dataset),
        centres(centres),
        metric(metric),
        centreIndex(centreIndex),
        farthestPointIndex(farthestPointIndex),
        nodePtr(nodePtr)
    {}

    template <
            typename MetricType,
            typename TreeType,
            typename MatType>
    double GonzalezKcentreRules<MetricType,
                        TreeType,
                        MatType> :: BaseCase(const size_t /*queryIndex*/ , const size_t /*referenceIndex*/ ){
        return 0.0;
    }

    //The queryIndex is Fake one. We will be always working upon the reference node and current centres and update the current centre

    template <
            typename MetricType,
            typename TreeType,
            typename MatType>
    double GonzalezKcentreRules<
                                MetricType,
                                TreeType,
                                MatType> ::
    Score(const size_t /*queryIndex*/ , TreeType & referenceNode){
        //we have reached the node containing points
        for(size_t i = 0 ; i < referenceNode.NumPoints() ; ++i){
            // Evaluating the distance of each point from the current index and update the stats
            auto distance = metric.Evaluate(centres.col(centreIndex) , dataset.col(referenceNode.Point(i)));
            if(referenceNode.Stat().IsThisCentre()){
                continue;
            }
            if(std::fabs(distance - 0) <= elipson * std::fmax(std::fabs(distance), std::fabs(0))){
                //! Distance between the reference point and choosen centre is very less
                referenceNode.Stat().IsThisCentre() = true;
                continue;
            }
            if(referenceNode.Stat().Distance() > distance){
                referenceNode.Stat().Distance() = distance;
            }
            if(referenceNode.Stat().Distance() > maxDistancedPointDistance ){
                maxDistancedPointDistance = referenceNode.Stat().Distance();
                farthestPointIndex = referenceNode.Point(i);
                *nodePtr = &referenceNode;    
            }
        }
        return 0.0;
    }

    template <
            typename MetricType,
            typename TreeType,
            typename MatType>
    double GonzalezKcentreRules<
                        MetricType,
                        TreeType,
                        MatType> ::
    Rescore(const size_t /*queryIndex*/ , TreeType & /*referenceNode*/ , const double oldScore){
        return oldScore;
    }
}
}
#endif
