/*
 * @file dual_tree_kcentre_stats.hpp
 * @author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_KCENTRE_STATS_HPP
#define MLPACK_METHODS_KCENTRE_STATS_HPP
#include <mlpack/prereqs.hpp>
namespace mlpack{
namespace KCentre{
/**
 * Statistic Class which stores:
 * 1) Current Centre to which it corresponds to
 * 2) Distance to the nearest centre
 * 3) Upper bound of the distance
 */
    class DualTreeKcentreStats{
    private:
        //! Upper bound on the distance to the centre of any points in this node
        double maxCentreDistance;
        //! Lower bound on the distance to the centre of any points in this node
        double minCentreDistance;
        //! Centre Index of the all the points in this node belong to
        int centreIndex;
        //! To store the bound for this Node
        double bound;

    public:
        DualTreeKcentreStats():
            maxCentreDistance(DBL_MAX),
            minCentreDistance(DBL_MAX),
            centreIndex(-1){}
        template <typename TreeType>
        DualTreeKcentreStats(TreeType & node):
            maxCentreDistance(DBL_MAX),
            minCentreDistance(DBL_MAX),
            centreIndex(
                    ((node.NumPoints() == 1) && (node.NumChildren() == 0)) ?
                    node.Point(0) : -1 ) {}

            
        double & MaxCentreDistance(){ return maxCentreDistance;}
        double & MinCentreDistance(){ return minCentreDistance;}
        int & CentreIndex(){ return centreIndex;}
        double & Bound(){return bound;}



    };
}
}
#endif

