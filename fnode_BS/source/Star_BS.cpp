//#include "./../Topology/Star.cpp"
//constexpr int positive_well = 1;
//constexpr int negative_well = -1;
//namespace parameter
//{
//    const vector<int> nRange {100, 200, 400} ;
//    const vector<double> cRange { 0.1, 0.5, 1, 2, 3, 4 } ;
//
//    constexpr int repetitions =100 ;
//    constexpr int no_of_initial_conditions=100;
//
//    constexpr int initial_well= negative_well ;
//    constexpr double spread= 0.25 ;
//
//    constexpr double perturbRange_initial = 0;
//    constexpr double perturbRange_final = 5;
//
//    constexpr double transients = 100;
//    constexpr double dt = 0.01;
//}
///-------------------------------------------

#include "fnode_BS.cpp"
#include<sstream>


int total_iterations()
{   using namespace parameter;
    int ti = 0;
    for(auto n : nRange)
        ti+=n/2;
    return (ti*cRange.size()*repetitions*
            no_of_initial_conditions);
}



int main()
{using parameter::nRange;
using  parameter::cRange;

    cout<<"Total iterations :"<<total_iterations()<<endl;
    for(auto n : nRange)
    {
        BS_fnode<Star> analyser(n,-1);
        for(auto c : cRange)
        {
            ostringstream s;
            s<<"Star"<<"_n="<<n <<"_c="<<c ;

            ofstream f(s.str()+".txt");
            f<<"#"<<s.str()<<endl;

            analyser.BSvsfnode(f,c);
        }
    }
}
