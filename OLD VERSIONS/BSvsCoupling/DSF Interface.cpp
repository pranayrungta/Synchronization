#include "./mainPrograms.cpp"

int main()
{
    vector<int> orderRange {4};//{3,4,5,6};

    vector<double> cRange {0, 5, 0.1} ;///range

    double initialValue = -0.5 ;
    double perturbRange = 5 ;

    double transients = 5;//500 ;
    double dt = 0.01 ;
    int no_of_initial_conditions = 3;//100;



    DSFProgram(orderRange,cRange,
               initialValue,perturbRange,transients,
                dt,no_of_initial_conditions);
   return 0;
}
