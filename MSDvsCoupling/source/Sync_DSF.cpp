//#include "./../Topology/DSF.cpp"
//namespace parameter
//{
//    const vector<int> order {3,4};/// enumerated
//
//    const vector<double> cRange { 0, 5  , 0.1  };/// range
//
//    constexpr double et = 50;
//    constexpr double dt = 0.01;
//    constexpr int repetitions = 1 ;
//    constexpr double lp = 100;
//}
///-------------------------------------------------

#include<fstream>
#include<sstream>
#include "Dynamics_MSD.cpp"
using namespace std ;

int total_iterations()
{using namespace parameter;
    return order.size()* repetitions*
     ( (cRange[1]-cRange[0])/cRange[2] + 1) ;
}

int main()
{using parameter::order;
    cout<< "Total approximate iterations  :"<< total_iterations() ;
    cout<< endl<< endl;

    for(int netSize :order)
    {
        Dynamics_MSD<DSF> DSF_Network(netSize,-1);

        ostringstream s ;
        s<<"DSF_order="<<netSize;

        ofstream f( s.str()+".txt" );
        f<<( "# "+s.str() )<<endl;

        DSF_Network.CvsMSD(f);
    }
    return 0;
}
