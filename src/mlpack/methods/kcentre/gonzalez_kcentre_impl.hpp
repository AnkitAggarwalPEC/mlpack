/*
 * @file gonzalez_kcentre_impl.hpp
 * @Author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_KCENTRE_GONZALEZ_IMPL_HPP
#define MLPACK_METHODS_KCENTRE_GONZALEZ_IMPL_HPP
#include "gonzalez_kcentre.hpp"

namespace mlpack{
namespace kcentre{
    template<typename MetricType , typename MatType>
    GonzalezKcentre<MetricType , MatType>::GonzalezKcentre(
            const MatType & dataset,
            MetricType& metric):
            datasetOrig(dataset),
            metric(metric),
            minMaxDistance(0.0)
    {}
    
    template<typename MetricType , typename MatType>
    GonzalezKcentre<MetricType , MatType>::~GonzalezKcentre()
    {}

    typename<typename MetricType , typename MatType>
    void GonzalezKcentre<MetricType,MatType>::Iterate(
            const MatType& centres,
            MatType& new_centres){
        new_centres.zeros(centres.n_rows,centres.n_cols);

    }
}
}
#endif
