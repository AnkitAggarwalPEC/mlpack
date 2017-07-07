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
using namespace mlpack::KCentre;
using namespace std;

int main(int argc , char * argv[]){
    CLI::ParseCommandLine(argc, argv);
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
        kcentre< metric::EuclideanDistance , SampleInitialization, GonzalezKcentre ,  arma::mat> kcentre_obj(maxIterations, metric::EuclideanDistance(), SampleInitialization());
        kcentre_obj.Centres(dataPoints , numCentres, centres , initialCentresGuess);
    }
    else if(algorithm == "naive"){
        // run the gonzalez algorithm
        kcentre<metric::EuclideanDistance, SampleInitialization,GonzalezKcentre, arma::mat> kcentre_obj(maxIterations, metric::EuclideanDistance(), SampleInitialization());
        kcentre_obj.Centres(dataPoints , numCentres, centres , initialCentresGuess);
    }
    Timer::Stop("Run Time");
    
    return 0;
}
