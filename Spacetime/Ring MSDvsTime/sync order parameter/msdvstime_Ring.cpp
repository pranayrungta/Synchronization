//#include "Interface.cpp"
#include "./../../../Dynamics_base.cpp"
#include<fstream>
#include<sstream>
using namespace std ;

int progress = 0 ;

class timeAnalysis : Dynamics_base<Ring>
{public:

    timeAnalysis(int n, int k):
        Dynamics_base<Ring>(n,k) {}

    /// function to evolve One network and return msd
    double synctime(double c)
	{using parameter::et;
	using parameter::dt;
	using parameter::thresholdmsd;

		initialize();
		int limit= int(et/dt) ;
		for(int i=1; i<=limit; i++)
		{
			evolveNodes(dt,c);
			if(msdx()<thresholdmsd)
				return (i*dt);
		}
		return et ;
	}

    /// function to evolve One network and return msd
    void synctimeVsCoupling(ofstream& f)
	{using parameter::cRange;
	using parameter::repetitions;
		f<<"# Coupling"<<"\t"<<"Transient time"<<endl;
		for(int c=cRange[0]; c<=cRange[1]; c+=cRange[2])
		{
			double avgTransientTime = 0;
			for(int repetitionNo=1; repetitionNo<=repetitions; repetitionNo++)
				avgTransientTime+= synctime(c);
			avgTransientTime/=repetitions;

			f<<c<<"\t"<<avgTransientTime<<endl;
		}
		f.close();
		progress+= repetitions;
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
        timeAnalysis ringNetwork(n,k);
		ostringstream s ;
		s<<"ring_n="<<n<< "_k="<<k;
		ofstream f( s.str()+".txt" );
		f<<"# "<< s.str() <<endl;
		ringNetwork.synctimeVsCoupling(f);

		cout<<"\r progress = "<<progress<<"\t"<<s.str()<<"\t"<<flush;
    }
}
