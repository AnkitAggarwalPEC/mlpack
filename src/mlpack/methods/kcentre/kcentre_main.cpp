/**
 * @file kncentre_main.cpp
 * @author Ankit Aggarwal
 *
 * Executable for the running kcentre
 */
#include <mlpack/prereqs.hpp>
#include <mlpack/core/util/cli.hpp>
#include "kcentre.hpp"
#include "sample_initialization.hpp"

using namespace mlpack;
using namespace mlpack::kcentre;
using namespace std;

int main(int argc , char * argv[]){
    CLI::Parse(argc, argv);
    if(!CLI::HasParams("output")){
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

    //check for the type of algorithm to run
    auto algorithm = CLI::GetParam<std::string>("algorithm");
    if(algorithm == "dualtree"){
        // run the dual tree algorithm
    }
    else if(algorithm == "naive"){
        // run the daul tree algorithm
    }
    arma::mat dataPoints = std::move(CLI::GetParam<arma::mat>("input"));
    arma::mat centres;
    //check if there is initial centres given 
    auto initialCentresGuess = CLI::HasParam("initial_centres");
    if(initialCentresGuess){
        centres = std::move(CLI::GetParam<arma::mat>)("initial_centres");
        Log::Warn << "Initial Centres are specified in the input" << std::endl;
    }
    Timer::Start("Run Time");
    kcentre<metric::EuclideanDistance,
            SampleInitialization,
            arma::mat> kcentre(maxIterations, metric::EuclideanDistance(), SampleInitialization());
    kcentre.Centres(dataPoints , numCentres, centres , initialCentresGuess);
    Timer::Stop("Run Time");
    
    return 0;
}
