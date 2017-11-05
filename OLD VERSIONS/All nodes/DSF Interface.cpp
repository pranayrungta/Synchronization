#include "./mainPrograms.cpp"

int main()
{
    vector<int> orderRange {3,4,5,6};

    double initialValue = -0.5 ;
    double perturbRange = 5 ;

    double transients = 500 ;
    double dt = 0.01 ;
    double coupling = 1 ;

    int no_of_initial_conditions = 100;



    DSFProgram(orderRange,initialValue,perturbRange,transients,
                dt,coupling,no_of_initial_conditions);
   return 0;
}
