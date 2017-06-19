/*
 * @file gonzalez_kcentre_rules.hpp
 * @author Ankit Aggarwal
 *
 * Define the pruning rules and base cases necessary to perform single tree kcentre clustering using Gonzalez
 */
#ifndef MLPACK_METHODS_KCENTRE_GONZALEZ_KCENTRE_RULES_HPP
#define MLPACK_METHODS_KCENTRE_GONZALEZ_KCENTRE_RULES_HPP

namespace mlpack{
namespace kcentre{
    /*
     * The rules class for the single tree Gonzalez
     */
    template<typename MetricType , typename TreeType, typename MatType = arma::mat>
    class GonzalezKcentreRules{
        public:
            /*
             * Create the Gonzalez Rules Object
             *
             * @param dataset The dataset on which tree is built
             * @param centres Current Centres
             * @param new_centres New centres after this iteration
             * @param metric Instantiated metric
             */
            GonzalezKcentreRules(const MatType & dataset,
                                 const MatType & centres,
                                 MatType & new_centres,
                                 MetricType& metric
                                );
            
            /*
             * The BaseCase() function for this single-tree algorithm
             * @param queryIndex Index of query point
             * @param referenceIndex Index of reference point
             */
            double BaseCase(const size_t queryIndex ,  const size_t referenceIndex);

            /*
             * Score() function for this single tree algorithm
             * @param queryIndex Index of query point
             * @param referenceNode Node containing points in the dataset
             */
            double Score(const size_t queryIndex , TreeType & referenceNode);
    
            double ReScore(const size_t queryIndex , TreeType& referenceNode , const double oldScore);

        private:
            const MatType & dataset;
            const MatType & centres;
            MatType & new_centres;
            MetricType & metric;
    };
}
}
#include "gonzalez_kcentre_rules_impl.hpp"
#endif
