/*
 * @file gonzalez_kcentre_rules_impl.hpp
 * @Author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_KCENTRE_GONZALEZ_KCENTRE_RULES_IMPL_HPP
#define MLPACK_METHODS_KCENTRE_GONZALEZ_KCENTRE_RULES_IMPL_HPP
#include "gonzalez_kcentre_rules.hpp"

namespace mlpack{
namespace kcentre{
    template <typename MetricType, typename TreeType , typename MatType>
    GonzalezKcentreRules<MetricType , TreeType , MatType> ::
    GonzalezKcentreRules(const MatType & dataset,
                         const MatType & centres,
                         MatType & new_centres,
                         MetricType & metric):
        dataset(dataset),
        centres(centres),
        new_centres(new_centres),
        metric(metric)
    {}

    template <typename MetricType, typename TreeType , typename MatType>
    GonzalezKcentreRules<MetricType , TreeType , MatType> ::
    double BaseCase(const size_t queryIndex , const size_t referenceIndex ){
        return 0.0;
    }

    template <typename MetricType, typename TreeType , typename MatType>
    GonzalezKcentreRules<MetricType , TreeType , MatType> ::
    double Score(const size_t queryIndex , TreeType & referenceNode){
        
    }

    template <typename MetricType, typename TreeType , typename MatType>
    GonzalezKcentreRules<MetricType , TreeType , MatType> ::
    double ReScore(const size_t queryIndex , TreeType & referenceNode , const double oldScore){
        return oldScore;
    }

}
}
