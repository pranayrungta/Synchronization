#include "basinStability.cpp"

int main()
{
    vector<int> nRange {100, 200, 400};
    vector<int> kRange {1,2,3,4} ;
    vector<double> pRange{0, 0.1, 0.3, 0.5, 0.7, 0.9} ;

    int rewireSteps = 10 ; /// only for dynamic network rewiring

    double initialValue = -0.5 ;
    double perturbRange = 5 ;

    double transients = 500 ;
    double dt = 0.01 ;
    double coupling = 1 ;

    int no_of_initial_conditions = 100;



    mainProgram(nRange,kRange,pRange,rewireSteps,initialValue,perturbRange,
        transients,dt,coupling,no_of_initial_conditions);
    return 0;
}
