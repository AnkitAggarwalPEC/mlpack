/**
 * @file sample_initialization.hpp
 * @author Ankit Aggarwal
 * 
 */

#ifndef __MLPACK_METHODS_KCENTRE_SAMPLE_INTIALIZATION_HPP
#define __MLPACK_METHODS_KCENTRE_SAMPLE_INTIALIZATION_HPP

#include <mlpack/prereqs.hpp>
#include <mlpack/core/math/random.hpp>

namespace mlpack{
namespace KCentre{

class SampleInitialization{
    public:
    //! Default constructor will be used by the InitialPartitionPolicy type
    SampleInitialization() = default;
    /**
     * Initialize the centres matrix by randomly selecting single point from the data matrix
     *
     * @param data Dataset
     * @param num_centres Number of centres
     * @param centres Matrix to put initial centres into
     */
    template<typename MatType>
    static size_t Centres(const MatType& data,
                             const size_t num_centres,
                             arma::mat& centres){
        centres.set_size(data.n_rows , num_centres);
        const auto index = math::RandInt(0 , data.n_cols);
        centres.col(0) = data.col(index);
        return index;
    }
};
}
}
#endif
