#include "./../Topology/Ring.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
    const vector<int>  nRange{100} ;
    const vector<int>  kRange{1,2,3,4} ;

    const vector<double> cRange { 0.1, 0.4, 0.7, 1.0, 1.3, 1.6, 1.9,
                            2.2, 2.5, 2.8, 3.1, 3.4, 3.7, 4.0,
                            4.3, 4.6, 4.9, 5.2 } ;

    constexpr int repetitions =100 ;
    constexpr int no_of_initial_conditions=100;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;

    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;

    constexpr double transients = 100;
    constexpr double dt = 0.01;
}
#include "source/Ring_BS.cpp"
