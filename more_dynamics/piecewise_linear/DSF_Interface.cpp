#include "./../../Topology/DSF.cpp"
namespace parameter
{
    const vector<int> order {3,4,5};// enumerated
    const vector<double> cRange { 0, 4  , 0.1  };// range

    constexpr double et = 50;
    constexpr double dt = 0.01;
    constexpr int repetitions = 100 ;
    constexpr double lp = 100;
}
#include "piecewise_linear.cpp"
#include "./../Sync_DSF.cpp"
