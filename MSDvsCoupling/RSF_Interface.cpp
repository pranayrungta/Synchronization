#include "./../Topology/RSF.cpp"
namespace parameter
{
    const vector<int> nRange{100, 250, 500}; /// enumerated
    const vector<int> kRange{1, 2, 3, 4}; /// enumerated

    const vector<double> cRange { 0, 5  , 0.1  };/// range

    constexpr double et = 50;
    constexpr double dt = 0.01;
    constexpr int repetitions = 1000 ;
    constexpr double lp = 100;
}
#include "source/Sync_RSF.cpp"
