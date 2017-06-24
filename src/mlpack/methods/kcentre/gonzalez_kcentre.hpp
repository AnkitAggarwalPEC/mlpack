/*
 * @file gonzalez_kcentre.hpp
 * @author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_KCENTRE_GONZALEZ_HPP
#define MLPACK_METHODS_KCENTRE_GONZALEZ_HPP
//includes here
#include <mlpack/core/tree/binary_space_tree.hpp>
#include "gonzalez_kcentre_statistic.hpp"

namespace mlpack{
namespace kcentre{
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
             * Run the single iteration of Gonzalez Algorithm updating the given centres to new centres
             */
            void Iterate(MatType& centres);
            /*
             */
        private:
            //! To store the original dataset
            const MatType & datasetOrig;
            //! The metric
            MetricType & metric;
            //!Typedef for the tree
            typedef tree::KDTree<MetricType ,GonzalezKcentreStatistic , MatType > TreeType;
            //The tree built on the points
            TreeType * tree;
    };
}
}
#include "gonzalez_kcentre_impl.hpp"

#endif
