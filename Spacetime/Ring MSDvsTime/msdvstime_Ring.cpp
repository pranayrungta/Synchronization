//#include "Ring_msd_vs_time.cpp"
#include "./../../Dynamics_base.cpp"
#include<fstream>
#include<sstream>
using namespace std ;

int progress = 0 ;

class spacetimeAnalysis : Dynamics_base<Ring>
{public:

    spacetimeAnalysis(int n, int k):
        Dynamics_base<Ring>(n,k) {}

    /// function to evolve One network and return msd
    void msdvstime(ofstream& f, double c)
	{using parameter::et;
	using parameter::dt;

		f<<"#time"<<"\t"<<"msd"<<endl;
		initialize();

		int limit= int(et/dt) ;
		for(int i=1; i<=limit; i++)
		{
			evolveNodes(dt,c);

			f<< i*dt<< "\t"<< msdx()<<endl;
		}
		f.close();
	}
};

int main()
{using namespace parameter;

    int iterations = nRange.size()*kRange.size()*
                     cRange.size()*repetitions;
    cout<< "Total approximate iterations  :"<< iterations ;
    cout<< endl<< endl;

    for(int n : nRange)
    for(int k : kRange)
    {
        spacetimeAnalysis ringNetwork(n,k);

        for(int ic =1; ic<=repetitions ; ic++)
        for(double c : cRange)
        {
            ostringstream s;
            s<<"ring_n="<<n<<"_k="<<k<<"_c="<< c<< "_ic="<< ic;
            ofstream f( s.str()+".txt" );
            f<<"# "<< s.str() <<endl;
            ringNetwork.msdvstime(f,c);

            progress++;
            cout<<"\r progress = "<<progress<<"\t"<<s.str()<<"\t"<<flush;
        }

    }
}
