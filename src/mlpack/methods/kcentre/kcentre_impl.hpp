/*
 * @file kcentre_impl.hpp
 * @author Ankit Aggarwal
 */
#include "kcentre.hpp"
#include <mlpack/core/metrics/lmetric/hpp>

namespace mlpack{
namespace kcentre{

//constructor definition
template <typename MetricType,
         typename InitialPartitionPolicy,
         typename MatType>
kcentre(const size_t maxIterations,
        const MetricType metric,
        const InitialPartitionPolicy sampler):
        maxIterations(maxIterations),
        metric(metric),
        sampler(sampler)
    {}
template <typename MetricType , 
          typename InitialPartitionPolicy,
          typename MatType>
void kcentre<MetricType ,
             InitialPartitionPolicy, 
             MatType>::
             Centres(const MatType & data ,
                     const size_t num_centres ,
                     arma::mat & centres,
                     const bool initialGuess = false){
                 //sanity check for the number of centre parameter passed
                 if(num_centres > data.n_cols){
                    Log::Warn << "kcentre::Centres more number of centres requested than given points" << std::endl;
                 }
                 else if (num_centres <=0){
                    Log::Warn << "kcentre::Centres zero number of centres requested" << std::endl;
                 }

                 //if initialGuess is set i.e intial centres are passed
                 if(initialGuess){
                    if(centres.n_cols != centres){
                        Log::Fatal << "kcentre::Centres: wrong number of initail centres"<<std::endl; 
                    }
                    if(centres.n_rows != data.n_rows){
                        Log::Fatal << "kcentre::Centres: Wrong dimensionality of passed initial centres" << std::endl;
                    }
                 }
                 //use the sampler to get the initial centroids
                 if(!initialGuess){
                    //fill the centres matrix with InitialPartitionPolicy
                     InitialPartitionPolicy::Centres(data,num_centres ,centres);
                 }
                 size_t interations = 0;
                 double cNorm;
                 do{
                    iterations++;
                 }while(cNorm > 1e-5 && iterations != maxIterations);

                 if(iterations != maxIterations){
                    Log::Info << "kcentre::Centres(): converged after " << iterations << " iterations"<<std::endl;
                 }
                 else{
                    Log::Info << "Max Limit of Num of Interations reached " << std::endl;
                 }

             }
}
}
