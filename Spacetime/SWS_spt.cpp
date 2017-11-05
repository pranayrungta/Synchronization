#include "./../Topology/Small_World.cpp"
namespace parameter
{
    const vector<int> nRange {100};/// enumerated
    const vector<int> kRange {2,4};  /// enumerated

    const vector<double> pRange { 0,  0.1 } ;/// enumerated
    const vector<double> cRange { 0, 5  };  /// enumerated

    const double et = 10;
    const double dt = 0.1;
}
#include "source/spacetime_SWS.cpp"
