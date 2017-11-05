//#include "./../Topology/Ring.cpp"
//namespace parameter
//{
//    const vector<int> nRange {100,250,500};/// enumerated
//    const vector<int> kRange {1,2,3,4};/// enumerated
//
//    const vector<double> cRange { 0, 12  , 0.1  };  /// range
//
//    constexpr double et = 50;
//    constexpr double dt = 0.01;
//    constexpr int repetitions = 1000 ;
//    constexpr double lp = 100;
//}
///-------------------------------------------------

#include<fstream>
#include<sstream>
#include "Dynamics_MSD.cpp"

int total_iterations()
{   using namespace parameter;
    return nRange.size()*kRange.size()* repetitions*
         ((cRange[1]-cRange[0])/cRange[2] + 1) ;
}

int main()
{using parameter::nRange;
using  parameter::kRange;

    cout<< "Total approximate iterations  :"<< total_iterations() ;
    cout<< endl<< endl;

    for(int no_of_nodes :nRange)
    for(int k : kRange)
    {
        Dynamics_MSD<Ring> ringNetwork(no_of_nodes,k);

        ostringstream s ;
        s<<"ring_n="<<no_of_nodes<< "_k="<<k;

        ofstream f( s.str()+".txt" );
        f<<( "# "+s.str() )<<endl;

        ringNetwork.CvsMSD(f);
    }
}
