#include "./../Topology/DSF.cpp"
namespace parameter
{
    const vector<int> orderRange {4,5};/// enumerated
    const vector<double> cRange { 0, 1, 5  };/// enumerated

    constexpr double et = 10;
    constexpr double dt = 0.1;
}
#include "source/spacetime_DSF.cpp"
