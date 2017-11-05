#include "./DSF_BS.cpp"

namespace parameter
{
    vector<int> orderRange {4} ;
    vector<double> cRange {0.5, 1, 2, 3, 4 ,0.1 } ;

    int repetitions =100 ;
    int no_of_initial_conditions=100;

    double intial_value= -1 ;
    double spread= 0.25 ;

    double perturbRange_initial = 0;
    double perturbRange_final = 5;

    double transients = 100;
    double dt = 0.01;

    vector<int> perturbNodes {1,2,3} ;
}
