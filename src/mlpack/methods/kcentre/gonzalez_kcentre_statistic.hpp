/*
 * @file gonzalez_kcentre_statistic.hpp
 * @author Ankit Aggarwal
 * A statiscticType for used for trees when performing kcentre
 */

#ifndef MLPACK_GONZALEZ_KCENTRE_STATISTIC_HPP
#define MLPACK_GONZALEZ_KCENTRE_STATISTIC_HPP

#include <mlpack/prereqs.hpp> 

namespace mlpack{
namespace kcentre{

class GonzalezKcentreStatistic{
    private:
        //! Upper bound on the distance to the nearest neighbour of any points in this node
        double maxNeighbourDistance;
        //! Lower bound on the distanc to the nearest neighbour of any points in this node
        double minNeighbourDistance;
        
        int currentCentre;
    public:
        //! Empty Constructor
        GonzalezKcentreStatistic():
            maxNeighbourDistance(DBL_MAX),
            minNeighbourDistance(DBL_MIN),
            currentCentre(DBL_MAX),
            currentCentre(-1)
        {}

        //! Initialize the statistic for the node
        template <typename TreeType>
        GonzalezKcentreStatistic(TreeType & node):
            maxNeighbourDistance(DBL_MAX),
            minNeighbourDistance(DBL_MIN),
            currentCentre(DBL_MAX),
            currentCentre(-1)
        {}
};
}
}
#endif

