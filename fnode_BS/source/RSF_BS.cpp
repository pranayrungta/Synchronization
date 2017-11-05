//#include "./../Topology/RSF.cpp"
//constexpr int positive_well = 1;
//constexpr int negative_well = -1;
//namespace parameter
//{
//    const vector<int>  nRange{100} ;
//    const vector<int>  kRange{1,2,3,4} ;
//
//    const vector<double> cRange {0.1, 0.5, 1, 2,3  } ;
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

class RSF_BS : public BS_fnode<RSF>
{public:

    RSF_BS(int n, int k):
        BS_fnode<RSF>(n,k)
    {}

    double syncWell_after_evolve(const int& nopn, const double& c) override
    {
        network.recreateNetwork();
        return BS_fnode::syncWell_after_evolve(nopn,c);
    }
};


int total_iterations()
{   using namespace parameter;
    int ti = 0;
    for(auto n : nRange)
        ti+=n/2;
    return (ti*kRange.size()*cRange.size()*
         repetitions* no_of_initial_conditions);
}


int main()
{using parameter::nRange;
using  parameter::kRange;
using  parameter::cRange;

    cout<<"Total iterations :"<<total_iterations()<<endl;

    for(auto n : nRange)
    for(auto k : kRange)
    {
        RSF_BS analyser(n,k);
        for(auto c : cRange)
        {
            ostringstream s;
            s<<"RSF"<<"_n="<<n <<"_k="<<k <<"_c="<<c ;

            ofstream f(s.str()+".txt");
            f<<"#"<<s.str()<<endl;

            analyser.BSvsfnode(f,c);
        }
    }
    return 0;
}
