/*
 * @file gonzalez_kcentre.hpp
 * @author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_KCENTRE_GONZALEZ_HPP
#define MLPACK_METHODS_KCENTRE_GONZALEZ_HPP
#include <mlpack/core/tree/binary_space_tree.hpp>
#include "gonzalez_kcentre_statistic.hpp"
#include "gonzalez_kcentre_rules.hpp"
namespace mlpack{
namespace KCentre{
/*
 * An implementation of Gonzalez Algorithm for Kcentre
 */
    template<typename MetricType , typename MatType = arma::mat>
    class GonzalezKcentre{
        public:
            /* Constructor for GonzalezKcentre
             */
            GonzalezKcentre(const MatType & dataset , MetricType& metric);
            /*
             * Destructor for Gonzalez Kcentre
             */
            ~GonzalezKcentre();
            /*
             * To run the whole process
             */
            void ComputeKcentre(MatType & centres  , size_t num_centres , size_t max_iteration) ;
            /*
             * Run the single iteration of Gonzalez Algorithm updating the given centres to new centres
             */
            void Iterate();
            /*
             */
        private:
            //! To store the original dataset
            const MatType & datasetOrig;
            //! The metric
            MetricType & metric;
            //!Typedef for the tree
            typedef tree::KDTree<MetricType ,GonzalezKcentreStatistic , MatType > TreeType;
            //! The tree built on the points
            TreeType * tree;
            //! To store the farthest point index to append in centre matrix 
            int farthestPointIndex;
            //! To store the currently selected node in tree
            TreeType * farthestCentrePointPtr = nullptr;
            //! Typedef for the rules type object
            typedef GonzalezKcentreRules<MetricType, TreeType , MatType> RulesType;

    };
}
}
#include "gonzalez_kcentre_impl.hpp"

#endif
