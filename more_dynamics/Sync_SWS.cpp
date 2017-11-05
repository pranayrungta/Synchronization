//#include "./../Topology/Small_World.cpp"
//namespace parameter
//{
//    const vector<int> nRange {100};/// enumerated
//    const vector<int> kRange {2};  /// enumerated
//
//    const vector<double> pRange { 0.8 } ;/// enumerated
//    const vector<double> cRange { 0, 2  , 0.1  };  /// range
//
//    constexpr double et = 50;
//    constexpr double dt = 0.01;
//    constexpr int repetitions = 50 ;
//    constexpr double lp = 100;
//}
///-------------------------------------------------

#include<fstream>
#include<sstream>
#include "Dynamics_MSD.cpp"
using namespace std ;

class Small_World_Static_Sync : protected Dynamics_MSD<Small_World>
{public:
    Small_World_Static_Sync(int n, int k):
        Dynamics_MSD<Small_World>(n,k) {}

    void CvsMSD(const double& p_, ofstream& f)
    {
        p=p_;
        Dynamics_MSD::CvsMSD(f);
    }

protected:
    double p{0};

    /// function to evolve One network and return msd
    double EvolveOne(const double& c)override
    {
        network.evolve_links(p);
        return Dynamics_MSD::EvolveOne(c);
    }
};


int total_iterations()
{   using namespace parameter;
    return      nRange.size()*kRange.size()*
                pRange.size()* repetitions*
         ( (cRange[1]-cRange[0])/cRange[2]  + 1 ) ;
}

int main()
{using parameter::nRange;
using  parameter::kRange;
using  parameter::pRange;

    cout<< "Total approximate iterations  :"<< total_iterations() ;
    cout<< endl<< endl;

    for(int no_of_nodes :nRange)
    for(int k : kRange)
    {
        Small_World_Static_Sync swn(no_of_nodes,k);

        for(double p : pRange )
        {
            ostringstream s ;
            s<<"sws"<<"_n="<<no_of_nodes
             << "_k="<<k <<"_p="<< p;

            ofstream f( s.str()+".txt" );
            f<<( "# "+s.str() )<<endl;

            swn.CvsMSD(p,f);
        }
    }
}
