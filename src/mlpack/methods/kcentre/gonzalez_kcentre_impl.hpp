/*
 * @file gonzalez_kcentre_impl.hpp
 * @Author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_KCENTRE_GONZALEZ_IMPL_HPP
#define MLPACK_METHODS_KCENTRE_GONZALEZ_IMPL_HPP
#include "gonzalez_kcentre.hpp"
#include "gonzalez_kcentre_rules.hpp"

namespace mlpack{
namespace kcentre{
    template<typename MetricType , typename MatType>
    GonzalezKcentre<MetricType , MatType>::GonzalezKcentre(
            const MatType & dataset,
            MetricType& metric):
            datasetOrig(dataset),
            metric(metric),
            tree(new TreeType(const_cast<MatType&>(datasetOrig))),
            farthestPointIndex(0),
            farthestPointDistance(DBL_MIN)
    {}
    
    template<typename MetricType , typename MatType>
    GonzalezKcentre<MetricType , MatType>::~GonzalezKcentre()
    {
        if(tree)
            delete tree;
    }

    typename<typename MetricType , typename MatType>
    void GonzalezKcentre<MetricType,MatType>::Iterate(MatType& centres , int centreIndex){
        typedef GonzalezKcentreRules<MetricType, TreeType , MatType> RulesType;
        RulesType rules(dataset , centres , metric , distances , farthestPoint , farthestPointDistance);
        typename TreeType::SingleTreeTranverser<RulesType> traverser(rules);
        traverser.Traverse(0 , *tree);

    }
}
}
#endif
