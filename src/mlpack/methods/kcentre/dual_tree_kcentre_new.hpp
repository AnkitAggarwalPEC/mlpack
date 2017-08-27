/*
 * @file dual_tree_kcentre.hpp
 * @author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_DUAL_TREE_KCENTRE_HPP
#define MLPACK_METHODS_DUAL_TREE_KCENTRE_HPP
#include <mlpack/core/tree/binary_space_tree.hpp>
#include <mlpack/core/metrics/lmetric.hpp>
#include <mlpack/methods/range_search/range_search.hpp>
#include <set>
namespace mlpack{
namespace KCentre{
/*
* An implementation of dual tree kcentre
*/
    template<typename MetricType  = metric::EuclideanDistance , typename MatType = arma::mat>
    class DualTreeKCentre{
        public:
        /*
         * Constructor for the DualTreeKcentre
         */
        DualTreeKCentre(MatType & dataset , MetricType & metric);
        /*
         * Destructor for the DualTreeKcentre
         */
        ~DualTreeKCentre(){}
        /*
         * Intialize the distance matrix with initial centre
         */
        void Initialize(MatType & centres , size_t initial_centre);
        /*
         * To run the whole process
         */
        void ComputeKcentre(MatType & centres , size_t num_centres , size_t max_iterations , size_t index);
        /*
         * Run the single iteration of the Dual Tree Algorithm
         */
        void Iterate();
        /*
         * Select new centre
         */
        size_t SelectNewCentre(std::set <size_t> &);

        private:
        /*
         * Distance matrix for each point
         */
        MatType distances;
        /*
         * To store the metric object
         */
        MetricType & metric;
        /*
         * To store the original dataset
         */
        MatType & dataset;
        /*
         * Typedef for the Range search
         */
        typedef range::RangeSearch<MetricType, MatType,tree::BallTree> RangeSearchType;

        RangeSearchType * rs;

        double maxPossibleDistance;

        double minPossibleDistance;

    };
}
}
#include "dual_tree_kcentre_impl_new.hpp"
#endif
