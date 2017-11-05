#include "./../Topology/Small_World.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
    const vector<int>  nRange{100} ;
    const vector<int>  kRange{1,2,3,4} ;
    const vector<double> pRange{0, 0.1, 0.2, 0.5, 0.7, 0.9} ;
    const vector<double> cRange {0.1, 0.5,   0.8, 1, 1.3,    2  } ;

    constexpr int repetitions =100 ;
    constexpr int no_of_initial_conditions=100;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;

    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;

    constexpr double transients = 100;
    constexpr double dt = 0.01;
}
#include "source/SWStatic_BS.cpp"
