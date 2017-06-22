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
            minMaxDistance(0.0),
            tree(new TreeType(const_cast<MatType&>(datasetOrig))),
    {}
    
    template<typename MetricType , typename MatType>
    GonzalezKcentre<MetricType , MatType>::~GonzalezKcentre()
    {
        if(tree)
            delete tree;
    }

    typename<typename MetricType , typename MatType>
    void GonzalezKcentre<MetricType,MatType>::Iterate(
            const MatType& centres,
            MatType& new_centres){
        new_centres.zeros(centres.n_rows,centres.n_cols);
        typedef GonzalezKcentreRules<MetricType, TreeType , MatType> RulesType;
        RulesType rules(dataset , centres , new_centres , metric);
        typename TreeType::SingleTreeTranverser<RulesType> traverser(rules);
        traverser.Traverse(0 , *tree);
    }
}
}
#endif
