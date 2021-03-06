#include "./mainPrograms.cpp"

int main()
{
    vector<int> nRange {100}; //{100, 200, 400};
    vector<int> kRange {1,2};//{1,2,3,4} ;
    vector<double> pRange{0, 0.1, 0.3, 0.5, 0.7, 0.9} ;

    vector<double> cRange {0, 5, 0.1} ;///range

    double initialValue = -0.5 ;
    double perturbRange = 5 ;

    double transients = 5;//500 ;
    double dt = 0.01 ;

    int no_of_initial_conditions = 3;//100;



    SWstaticProgram(nRange,kRange,pRange,cRange,
                    initialValue,perturbRange,transients,
                    dt,no_of_initial_conditions);



    return 0;
}
