#include "./../Topology/DSF.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
    const vector<int> orderRange {3} ;
    const vector<double> cRange {0.5, 1, 2, 3, 4 ,0.1 } ;

    constexpr int repetitions =100 ;
    constexpr int no_of_initial_conditions=100;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;

    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;

    constexpr double transients = 100;
    constexpr double dt = 0.01;
}
#include "source/DSF_BS.cpp"
