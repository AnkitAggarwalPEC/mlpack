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
        double closetCentreDistance;
        //! Lower bound on the distanc to the nearest neighbour of any points in this node
        double farthestCentreDistance;
        //! Current Closest Centre         
        int currentClosestCentre;
        //! Current Farthest Centre
        int currentFarthestCentre;
    public:
        //! Empty Constructor
        GonzalezKcentreStatistic():
            closetCentreDistance(DBL_MAX),
            farthestCentreDistance(DBL_MIN),
            currentClosestCentre(-1),
            currentFarthestCentre(-1)
        {}

        //! Initialize the statistic for the node
        template <typename TreeType>
        GonzalezKcentreStatistic(TreeType & node):
            closetCentreDistance(DBL_MAX),
            farthestCentreDistance(DBL_MIN),
            currentClosestCentre(-1),
            currentFarthestCentre(-1)
        {}
        //setter and getter for the member variable

        double & ClosetCentreDistance(){
            return closetCentreDistance;
        }
        
        double & FarthestCentreDistance(){
            return farthestCentreDistance;
        }
        int & CurrentClosestCentre(){
            return currentClosestCentre;
        }
        int & CurrentFarthestCentre(){
            return currentFarthestCentre;
        }
};
}
}
#endif

