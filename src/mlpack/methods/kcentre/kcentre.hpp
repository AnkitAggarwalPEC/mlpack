/**
 * @file kcentre.hpp
 * @author Ankit Aggarwal
 *
 * K-Centre Problem
 */
#ifndef MLPACK_METHODS_KCENTRE_HPP
#define MLPACK_METHODS_KCENTRE_HPP

#include <mlpack/prereqs.hpp>
#include "sample_initialization.hpp"
#include <mlpack/core/metrics/lmetric.hpp> //include for distance function definition
#include <mlpack/core/tree/binary_space_tree.hpp>
#include "gonzalez_kcentre.hpp"
#include "dual_tree_kcentre.hpp"

namespace mlpack{
namespace KCentre{

/**
 * Begining Point of Kcentre
 */
/*@tparam MetricType The distance metric to use for this KMeans
 *@tparam InitialPartitionPolicy Intial Centre Selection Policy
 *@tparam MatType Type of data on which we would be processing
 */
template<typename MetricType = metric::EuclideanDistance,
         typename InitialPartitionPolicy = SampleInitialization,
         template <class , class> class Solver = GonzalezKcentre, 
         typename MatType = arma::mat
        >
class kcentre{
    private:
        size_t maxIterations;
        MetricType metric;
        InitialPartitionPolicy sampler;
    public:
        /*
         * @param maxIterations Max Number of iterations allowed before giving up
         * @parram metric When special selection policy is required
         * @param InitialPartitionPolicy When special selection policy is required
         */
        kcentre(const size_t maxIterations = 1000,
                const MetricType metric =  MetricType(),
                const InitialPartitionPolicy sampler = InitialPartitionPolicy()
                );
        /* Run the k Centre algorithm on the data provided
         * @param data Dataset for the algorithm
         * @param num_centres Number of Centres
         * @param centres Matrix for storing the centres
         */
        void Centres(MatType& data ,
                     const size_t num_centres,
                     arma::mat& centres,
                     const bool initialGuess = false);
};

}
}
#include "kcentre_impl.hpp"
#endif

