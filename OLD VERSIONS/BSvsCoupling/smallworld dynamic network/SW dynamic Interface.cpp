#include "basinStability.cpp"

int main()
{
    vector<int> nRange {5}; //{100, 200, 400}; /// enumerated
    vector<int> kRange {1,2}; //{1,2,3,4} ; /// enumerated
    vector<double> pRange {0,0.5}; //{0, 0.1, 0.3, 0.5, 0.7, 0.9} ; /// enumerated

    vector<double> cRange{0, 5, 0.1}; ///range

    int rewireSteps = 10 ; /// only for dynamic network rewiring
    double initialValue = -0.5 ;
    double perturbRange = 5 ;

    double transients = 5;//500 ;
    double dt = 0.01 ;
    int no_of_initial_conditions = 3;//100;



    mainProgram(nRange,kRange,pRange,cRange,
                rewireSteps,initialValue,perturbRange,
                transients,dt,no_of_initial_conditions);
    return 0;
}
