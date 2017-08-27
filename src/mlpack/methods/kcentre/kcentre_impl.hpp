/*
 * @file kcentre_impl.hpp
 * @author Ankit Aggarwal
 */
#include "kcentre.hpp"
#include <mlpack/core/metrics/lmetric.hpp>

namespace mlpack{
namespace KCentre{

//constructor definition
template <typename MetricType,
         typename InitialPartitionPolicy,
         template <class ,class> class Solver,
         typename MatType>
kcentre<
        MetricType,
        InitialPartitionPolicy,
        Solver,
        MatType>::
kcentre(const size_t maxIterations,
        const MetricType metric,
        const InitialPartitionPolicy sampler):
        maxIterations(maxIterations),
        metric(metric),
        sampler(sampler)
    {}
template <typename MetricType , 
          typename InitialPartitionPolicy,
          template <class ,class> class Solver,
          typename MatType>
void kcentre<MetricType ,
             InitialPartitionPolicy,
             Solver,
             MatType>::
             Centres(MatType & data ,
                     const size_t num_centres ,
                     arma::mat & centres,
                     const bool initialGuess ){
                 //sanity check for the number of centre parameter passed
                 if(num_centres > data.n_cols){
                    Log::Warn << "kcentre::Centres more number of centres requested than given points" << std::endl;
                 }
                 else if (num_centres <=0){
                    Log::Warn << "kcentre::Centres zero number of centres requested" << std::endl;
                 }

                 //if initialGuess is set i.e intial centres are passed
                 if(initialGuess){
                    if(centres.n_cols != num_centres){
                        Log::Fatal << "kcentre::Centres: wrong number of initail centres"<<std::endl; 
                    }
                    if(centres.n_rows != data.n_rows){
                        Log::Fatal << "kcentre::Centres: Wrong dimensionality of passed initial centres" << std::endl;
                    }
                 }
                 size_t index = 0;
                 //use the sampler to get the initial centroids
                 if(!initialGuess){
                    //fill the centres matrix with InitialPartitionPolicy
                    index = InitialPartitionPolicy::Centres(data,num_centres ,centres);
                 }
                 Solver<MetricType ,  MatType> solver_obj(data , metric);
                 solver_obj.ComputeKcentre(centres , num_centres , maxIterations , index);
             }
}
}
