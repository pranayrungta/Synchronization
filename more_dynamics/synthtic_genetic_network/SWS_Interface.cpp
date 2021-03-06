#include "./../../Topology/Small_World.cpp"
namespace parameter
{
    const vector<int> nRange {100};/// enumerated
    const vector<int> kRange {2};  /// enumerated

    const vector<double> pRange { 0,0.2,0.6,0.8 } ;/// enumerated
    const vector<double> cRange { 0, 2  , 0.1  };  /// range

    constexpr double et = 50;
    constexpr double dt = 0.01;
    constexpr int repetitions = 50 ;
    constexpr double lp = 100;
}
#include "synthetic_genetic_network.cpp"
#include "./../Sync_SWS.cpp"
