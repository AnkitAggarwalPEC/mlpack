/*
 * @file gonzalez_kcentre_impl.hpp
 * @Author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_KCENTRE_GONZALEZ_IMPL_HPP
#define MLPACK_METHODS_KCENTRE_GONZALEZ_IMPL_HPP
#include "gonzalez_kcentre.hpp"
#include "gonzalez_kcentre_rules.hpp"

namespace mlpack{
namespace KCentre{
    template<typename MetricType , typename MatType>
    GonzalezKcentre<MetricType , MatType>::GonzalezKcentre(
            const MatType & dataset,
            MetricType& metric):
            datasetOrig(dataset),
            metric(metric),
            tree(new TreeType(const_cast<MatType&>(datasetOrig))),
            farthestPointIndex(0)
    {}
    
    template<typename MetricType , typename MatType>
    GonzalezKcentre<MetricType , MatType>::~GonzalezKcentre()
    {
        if(tree)
            delete tree;
    }

    template<
            typename MetricType,
            typename MatType>
    void GonzalezKcentre<
                        MetricType,
                        MatType>::
    Iterate(MatType& centres){
        typedef GonzalezKcentreRules<MetricType, TreeType , MatType> RulesType;
        RulesType rules(datasetOrig , centres , metric , distances , farthestPointIndex);
        typename TreeType::template SingleTreeTranverser<RulesType> traverser(rules);
        traverser.Traverse(0 , *tree);

    }
}
}
#endif
