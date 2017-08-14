/*
 * @file dual_tree_kcentre_rules.hpp
 * @author Ankit Aggarwal
 */

#ifndef MLPACK_METHODS_DUAL_TREE_KCENTRE_RULES_HPP
#define MLPACK_METHODS_DUAL_TREE_KCENTRE_RULES_HPP

#include <mlpack/prereqs.hpp>
#include <mlpack/core/tree/traversal_info.hpp>

namespace mlpack{
namespace KCentre{
    template <typename MetricType , typename TreeType , typename MatType = arma::mat>
    class DualTreeKcentreRules{
        public:
            /*
             * Constructor for the Rules Object
             */
            DualTreeKcentreRules(const MatType & dataset,
                                 MetricType & metric,
                                 arma::vec& distances
                                 );
            
            double BaseCase(const size_t queryIndex , const size_t referenceIndex);
            double Score(const size_t queryIndex , TreeType & referenceIndex);
            double Score(TreeType & queryNode , TreeType & referenceNode);
            double Rescore(const size_t queryIndex , TreeType& referenceNode , const double oldScore);
            double Rescore(TreeType &  queryNode , TreeType& referenceNode , const double oldScore);
        private:
            //! The data points
            MatType& dataset;
            //! To store the current state of the distances
            arma::vec& distances;
            //! To store the metric object
            MetricType& metric;
            //! Update the bound info for the given query node
            double CalculateBound(TreeType & qeuryNode) const;
            //! Need a mechanism for the storing of the last chosen centre
    };
}
}
#include "dual_tree_kcentre_rules_impl.hpp"
#endif
