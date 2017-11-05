#include "./mainPrograms.cpp"

int main()
{
    vector<int> nRange {100, 200, 400};
    vector<int> kRange {1,2,3,4} ;
    vector<double> pRange{0, 0.1, 0.3, 0.5, 0.7, 0.9} ;

    double initialValue = -0.5 ;
    double perturbRange = 5 ;

    double transients = 500 ;
    double dt = 0.01 ;
    double coupling = 1 ;

    int no_of_initial_conditions = 100;



    SWstaticProgram(nRange,kRange,pRange,initialValue,perturbRange,transients,
                dt,coupling,no_of_initial_conditions);



    return 0;
}
