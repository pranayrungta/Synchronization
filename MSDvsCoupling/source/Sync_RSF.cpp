//#include "./../Topology/RSF.cpp"
//namespace parameter
//{
//    const vector<int> nRange{100, 250, 500}; /// enumerated
//    const vector<int> kRange{1, 2, 3, 4}; /// enumerated
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

class Scale_Free_Sync : public Dynamics_MSD<RSF>
{public:
    Scale_Free_Sync(int n, int k):
        Dynamics_MSD<RSF>(n,k) {}

    /// function to evolve One network and return msd
    double EvolveOne(const double& c)override
    {
        network.recreateNetwork();
        return Dynamics_MSD::EvolveOne(c);
    }
};

int total_iterations()
{   using namespace parameter;
    return nRange.size()*kRange.size()* repetitions*
         ( (cRange[1]-cRange[0])/cRange[2] + 1);
}

int main()
{using parameter::nRange;
using parameter::kRange;

    cout<< "Total approximate iterations  :"<< total_iterations() ;
    cout<< endl<< endl;

    for(int n :nRange)
    for(int k :kRange)
    {
        Scale_Free_Sync scaleFreeNetwork(n,k);

        ostringstream s ;
        s<<"RSF_n="<<n<<"_k="<< k;

        ofstream f( s.str()+".txt" );
        f<<( "# "+s.str() )<<endl;

        scaleFreeNetwork.CvsMSD(f);
    }
    return 0;
}
