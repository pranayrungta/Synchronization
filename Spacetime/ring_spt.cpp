#include "./../Topology/Ring.cpp"
namespace parameter
{
    const vector<int> nRange {100};/// enumerated
    const vector<int> kRange {1};/// enumerated

    const vector<double> cRange {1};  /// enumerated

	constexpr double et=20.0;
	constexpr double dt= 0.01;
}
#include "source/spacetime_Ring.cpp"
