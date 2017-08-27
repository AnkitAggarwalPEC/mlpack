/*
 * @file dual_tree_kcentre_impl.hpp
 * @author Ankit Aggarwal
 */
#ifndef MLPACK_METHODS_DUAL_TREE_KCENTRE_IMPL_HPP
#define MLPACK_METHODS_DUAL_TREE_KCENTRE_IMPL_HPP
#include <mlpack/prereqs.hpp>
#include <mlpack/core/tree/binary_space_tree.hpp>
#include "dual_tree_kcentre_new.hpp"
#include "kcentre_helper.hpp"

namespace mlpack{
namespace KCentre{

/*An implementation of Dual Tree Kcentre
 */
    template <typename MetricType , typename MatType>
    DualTreeKCentre<MetricType , MatType>::
    DualTreeKCentre(MatType & data , MetricType & metric):
        metric(metric),
        dataset(data),
        maxPossibleDistance(-DBL_MAX),
        minPossibleDistance(DBL_MAX)
    {
        rs = new RangeSearchType(); 
        //! Set the default distance
        distances.set_size(1 , dataset.n_cols),
        distances.fill(-DBL_MAX);
    }
    

    template <typename MetricType , typename MatType>
    void DualTreeKCentre<MetricType , MatType>::
    Initialize(MatType & centres , size_t initial_centre){
        
        for (size_t index =  0 ; index < dataset.n_cols ; index++){
            auto val = metric.Evaluate(centres.col(0), dataset.col(index));
            distances.col(index) = metric.Evaluate(centres.col(0), dataset.col(index));
            
            if (initial_centre == index) continue;
            
            if (val > maxPossibleDistance) maxPossibleDistance = val;
            if (val < minPossibleDistance) minPossibleDistance = val;
        }
        print_matrix <arma::mat>(dataset);
        print_matrix<arma::mat>(distances);
        std::cout << maxPossibleDistance << " " << minPossibleDistance << std::endl;
    }

    template <typename MetricType , typename MatType>
    void DualTreeKCentre<MetricType , MatType>::
    ComputeKcentre(MatType & centres ,  size_t num_centres , size_t max_iterations , size_t initial_centre){
        Initialize(centres , initial_centre);
        std::vector<std::vector<size_t>> neighbour;
        std::vector<std::vector<double>> neighbourDistances;
        rs->Train(dataset);
        std::cout << maxPossibleDistance/2.00 << std::endl;
        rs->Search(dataset,math::Range(0.05 , maxPossibleDistance/2.00),neighbour ,neighbourDistances);
        std::set <size_t> points_set;
        for (size_t i = 0 ; i < dataset.n_cols; i++) points_set.insert(i);
        points_set.erase(initial_centre);
        std::cout <<"Initial Set" << std::endl;
        print_set(points_set);
        for(size_t i = 1 ; i < num_centres ; i++){

            std::cout <<"Iteration " << std::endl;
            print_set(points_set);
            print_vector(neighbour[initial_centre]);
            for(size_t j = 0 ; j < neighbour[initial_centre].size(); j++){
                points_set.erase(neighbour[initial_centre][j]);
            }
            print_set(points_set);
            initial_centre = SelectNewCentre(points_set);
            centres.col(i) = dataset.col(initial_centre);
            points_set.erase(initial_centre);
        }
        print_matrix<arma::mat>(centres);
    }

    template <typename MetricType , typename MatType>
    size_t DualTreeKCentre<MetricType , MatType>::
    SelectNewCentre(std::set <size_t>& remaining_points){
        auto set_size = remaining_points.size();
        auto index =  math::RandInt(set_size); 
        auto it = remaining_points.begin();
        std::advance(it , index);
        return *it;
    }
}
}
#endif
