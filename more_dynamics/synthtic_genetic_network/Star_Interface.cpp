#include "./../../Topology/Star.cpp"
namespace parameter
{
    const vector<int> nRange {4,5};/// enumerated

    const vector<double> cRange { 0, 5  , 0.1  };/// range

    constexpr double et = 50;
    constexpr double dt = 0.01;
    constexpr int repetitions = 1000 ;
    constexpr double lp = 100;
}
#include "synthetic_genetic_network.cpp"
#include "./../Sync_Star.cpp"
