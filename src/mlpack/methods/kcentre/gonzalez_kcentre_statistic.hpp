/*
 * @file gonzalez_kcentre_statistic.hpp
 * @author Ankit Aggarwal
 * A statiscticType for used for trees when performing kcentre
 */

#ifndef MLPACK_GONZALEZ_KCENTRE_STATISTIC_HPP
#define MLPACK_GONZALEZ_KCENTRE_STATISTIC_HPP

#include <mlpack/prereqs.hpp> 

namespace mlpack{
namespace KCentre{

class GonzalezKcentreStatistic{
    private:
        //! To cache whether it is already chosen centre
        bool isThisCentre;
        //! To store the distance from centre
        double distance;
        //! To store the centre index in dataset for this node
        int index;
    public:
        
        //! Empty Constructor
        GonzalezKcentreStatistic():
            isThisCentre(false),
            distance(DBL_MAX),
            index(-1)
        {}
        //! Initialize the statistic for the node
        template <typename TreeType>
        GonzalezKcentreStatistic(TreeType & /*node*/):
            isThisCentre(false),
            distance(DBL_MAX),
            index(-1)
        {}
        
        //setter and getter for the member variable
        bool & IsThisCentre(){
            return isThisCentre;
        }
        double & Distance(){
            return distance;
        }
        int & Centre(){
           return index; 
        }
};
}
}
#endif

