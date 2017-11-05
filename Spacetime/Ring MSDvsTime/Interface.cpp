#include "./../../Topology/Ring.cpp"
namespace parameter
{
	vector<int> nRange {50, 10};/// enumerated
    vector<int> kRange {1};/// enumerated
    vector<double> cRange { 0.15, 0.26, 0.4, 1.00  };  /// enumerated

    double et = 500;
    double dt = 0.01;
    int repetitions = 10;
}
#include "msdvstime_Ring.cpp"
