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

    template<
            typename MetricType,
            typename MatType>
    void GonzalezKcentre<
                        MetricType,
                        MatType>::
    Iterate(MatType& centres  , size_t centreIndex){
        //! TreeType defined in .hpp
        typedef GonzalezKcentreRules<MetricType, TreeType , MatType> RulesType;
        TreeType * farthestCentrePointPtr = nullptr;
        RulesType rules(datasetOrig , centres , metric ,centreIndex - 1 , farthestPointIndex , farthestCentrePointPtr);
        typename TreeType::template SingleTreeTraverser<RulesType> traverser(rules);
        print_matrix<MatType>(centres);
        traverser.Traverse(0 , *tree);

        centres.col(centreIndex) = datasetOrig.col(farthestPointIndex);
        std::cout << "Farthest Point Index=" << farthestPointIndex << std::endl;
        if(farthestCentrePointPtr != nullptr)
            farthestCentrePointPtr->Stat().IsThisCentre() = true;

        print_matrix<MatType>(centres , centreIndex);
    }
}
}
#endif
