#include "./mainPrograms.cpp"

int main()
{
    vector<int> nRange {10};
    vector<int> kRange {1,2,3,4} ;

    double initialValue = -0.5 ;
    double perturbRange = 5 ;
    double transients = 5 ;
    double dt = 0.01 ;
    double coupling = 1 ;

    int no_of_initial_conditions = 10;


    RSFProgram(nRange,kRange,initialValue,perturbRange,transients,
                dt,coupling,no_of_initial_conditions);
    return 0;
}
