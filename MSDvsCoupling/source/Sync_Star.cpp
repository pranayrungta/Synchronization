//#include "./../Topology/Star.cpp"
//namespace parameter
//{
//    const vector<int> nRange {4,5};/// enumerated
//
//    const vector<double> cRange { 0, 5  , 0.1  };/// range
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
using namespace std ;

int total_iterations()
{using namespace parameter;
    return nRange.size()* repetitions*
     ( (cRange[1]-cRange[0])/cRange[2] + 1) ;
}

int main()
{using parameter::nRange;

    cout<< "Total approximate iterations  :"<< total_iterations() ;
    cout<< endl<< endl;

    for(int n :nRange)
    {
        Dynamics_MSD<Star> starNetwork(n,-1);

        ostringstream s ;
        s<<"star_n="<<n;

        ofstream f( s.str()+".txt" );
        f<<( "# "+s.str() )<<endl;

        starNetwork.CvsMSD(f);
    }
    return 0;
}
