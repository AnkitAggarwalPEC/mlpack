/**
 * @file kncentre_main.cpp
 * @author Ankit Aggarwal
 *
 * Executable for the running kcentre
 */
#include "kcentre.hpp"
#include <mlpack/prereqs.hpp>
#include <mlpack/core/util/cli.hpp>
#include <mlpack/core/util/mlpack_main.hpp>
#include "sample_initialization.hpp"
#include "kcentre_helper.hpp"

PARAM_MATRIX_IN("input" , "Input dataset" , "i");
PARAM_INT_IN("centres" , "Inpit number of centres" , "c" , 0);
using namespace mlpack;
using namespace mlpack::KCentre;
using namespace std;

PARAM_MATRIX_OUT("output" , "Matrix to store output labels" , "o");
PARAM_INT_IN("max_iterations" , "Maximum number of iterations"  , "m" , 1000);
PARAM_MATRIX_IN("initial_centres" , "Matrix to specify staring selected centre" , "I");
PARAM_STRING_IN("algorithm" , "Algrithm to use" , "a", "naive");

void mlpackMain(){
    
    //CLI::ParseCommandLine(argc, argv);
    if(!CLI::HasParam("output")){
        Log::Warn << "--output_file is not specified, so no output will be saved" << std::endl;
    }
    //get value for the number of centre
    auto numCentres = CLI::GetParam<int>("centres");
    if(numCentres < 0){
        Log::Fatal <<"Invalid number of centres requested " << std::endl;
    }
    auto maxIterations = CLI::GetParam<int>("max_iterations");
    if(maxIterations < 0){
        Log::Fatal <<"Invalid number of max Interation " << maxIterations << " using default value of 1000" << std::endl; 
    }

    arma::mat dataPoints = std::move(CLI::GetParam<arma::mat>("input"));
    arma::mat centres;
    //check if there is initial centres given 
    auto initialCentresGuess = CLI::HasParam("initial_centres");
    if(initialCentresGuess){
        centres = std::move(CLI::GetParam<arma::mat>)("initial_centres");
        Log::Warn << "Initial Centres are specified in the input" << std::endl;
    }
    //check for the type of algorithm to run
    auto algorithm = CLI::GetParam<std::string>("algorithm");
    Timer::Start("Run Time");
    if(algorithm == "dualtree"){
        // run the dual tree algorithm
        kcentre< metric::EuclideanDistance , SampleInitialization, DualTreeKCentre ,  arma::mat> kcentre_obj(maxIterations, metric::EuclideanDistance(), SampleInitialization());
        kcentre_obj.Centres(dataPoints , numCentres, centres , initialCentresGuess);
    }
    else if(algorithm == "naive"){
        // run the gonzalez algorithm
        kcentre<metric::EuclideanDistance, SampleInitialization,GonzalezKcentre, arma::mat> kcentre_obj(maxIterations, metric::EuclideanDistance(), SampleInitialization());
        kcentre_obj.Centres(dataPoints , numCentres, centres , initialCentresGuess);
    }
    Timer::Stop("Run Time");
    
}
