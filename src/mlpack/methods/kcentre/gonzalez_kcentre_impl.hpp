/*
 * @file gonzalez_kcentre_impl.hpp
 * @Author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_KCENTRE_GONZALEZ_IMPL_HPP
#define MLPACK_METHODS_KCENTRE_GONZALEZ_IMPL_HPP
#include "gonzalez_kcentre.hpp"
#include "gonzalez_kcentre_rules.hpp"
#include "kcentre_helper.hpp"

namespace mlpack{
namespace KCentre{
    template<typename MetricType , typename MatType>
    GonzalezKcentre<MetricType , MatType>::GonzalezKcentre(
            const MatType & dataset,
            MetricType& metric):
            datasetOrig(dataset),
            metric(metric),
            tree(new TreeType(const_cast<MatType&>(datasetOrig), 1)),
            farthestPointIndex(0)
    {}
    
    template<typename MetricType , typename MatType>
    GonzalezKcentre<MetricType , MatType>::~GonzalezKcentre()
    {
        if(tree)
            delete tree;
    }

    template<typename MetricType, typename MatType>
    void GonzalezKcentre<MetricType,MatType>::
    ComputeKcentre(MatType & centres , size_t num_centres , size_t max_iteration){
        size_t iterations = 0;
        RulesType rules(datasetOrig , centres , metric);
        for (iterations  = 1 ; iterations < max_iteration && iterations < num_centres ; iterations++ ){
            farthestCentrePointPtr = nullptr;
            rules.CentreIndex() = iterations - 1;
            rules.FarthestPointIndex() = -1;
            rules.SetFarthestCentrePointer(&farthestCentrePointPtr);
            typename TreeType::template SingleTreeTraverser<RulesType> traverser(rules);
            traverser.Traverse(0 , *tree);
            //Iterate();
            std::cout << "Farthest point index" << rules.FarthestPointIndex() << std::endl;
            centres.col(iterations) = datasetOrig.col(rules.FarthestPointIndex());
            if (farthestCentrePointPtr != nullptr) farthestCentrePointPtr->Stat().IsThisCentre() = true;
            rules.SetMaxDistancedPoint() = DBL_MIN;

        }

    }
    template<typename MetricType, typename MatType>
    void GonzalezKcentre<MetricType,MatType>::
    Iterate(){
        //typename TreeType::template SingleTreeTraverser<RulesType> traverser(rules);
        //traverser.Traverse(0 , *tree);
    }
}
}
#endif
