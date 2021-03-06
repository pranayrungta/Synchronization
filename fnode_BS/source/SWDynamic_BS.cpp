//#include "./../../Topology/Small_World.cpp"
//constexpr int positive_well = 1;
//constexpr int negative_well = -1;
//namespace parameter
//{
//    const vector<int>  nRange{100} ;
//    const vector<int>  kRange{1,2,3,4} ;
//    const vector<double> pRange{0, 0.1, 0.2, 0.5, 0.7, 0.9} ;
//    const vector<double> cRange {0.1, 0.5,   0.8, 1, 1.3,    2  } ;
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
//
//    constexpr int link_period = 10;
//}
///-------------------------------------------

#include "fnode_BS.cpp"
#include<sstream>

class SWD_BS : protected BS_fnode<Small_World>
{public:

    SWD_BS(const int& n,const int& k):
        BS_fnode<Small_World>(n,k)
    {}

    void BSvsfnode(ofstream& f, const double& c, const double& p_)
    {
        p=p_;
        BS_fnode::BSvsfnode(f,c);
    }

private:
    double p{0};

	//function to evolve One network and return msd
    double syncWell_after_evolve(const int& nopn, const double& c)override;
};

int total_iterations()
{
    using namespace parameter;
    int ti = 0;
    for(auto n : nRange)
        ti+=n/2;
    return (ti*kRange.size()*cRange.size()*pRange.size()*
                repetitions* no_of_initial_conditions);
}

int main()
{using parameter::nRange;
using  parameter::kRange;
using  parameter::pRange;
using  parameter::cRange;

    cout<<"Total iterations :"<<total_iterations()<<endl;

    for(auto n : nRange)
    for(auto k : kRange)
    {
        SWD_BS analyser(n,k);
        for(auto p : pRange)
        for(auto c : cRange)
        {
            ostringstream s;
            s<<"SW_dynamic"<<"_n="<<n <<"_k="<<k <<"_p="<<p  <<"_c="<<c ;

            ofstream f(s.str()+".txt");
            f<<"#"<<s.str()<<endl;

            analyser.BSvsfnode(f,c,p);
        }
    }
}

///------------implementation of class functions-------

double SWD_BS::syncWell_after_evolve(const int& nopn, const double& c)
{using parameter::repetitions;
using parameter::transients;
using  parameter::dt;
using parameter::link_period;

    vector<int> perturbNodes = sample(0, this->network.size()-1, nopn,-1);
    double stableCount = 0;
    for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
    {
        fnode_BS_initialize(perturbNodes);

        int limit = int(  round(transients/dt)  ) ;
        for(int t=0; t<limit; t++)
        {
            /// to take average initial configuration in account
            if(t%link_period==0)
                network.evolve_links(p);
            evolveNodes(dt,c);
        }
        if(syncWell()==parameter::initial_well)
            stableCount++;

        progress++;
    }
    return (stableCount/repetitions);
}
