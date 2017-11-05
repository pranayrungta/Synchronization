#include "./../../Dynamics_base.cpp"
#include<fstream>
#include<sstream>

int progress = 0 ;

class spacetimeAnalysis : Dynamics_base<Small_World>
{public:
    spacetimeAnalysis(int n, int k):
        Dynamics_base<Small_World>(n,k) {}

    void spacetimeDynamic(ofstream& f, const double p, const double c)
	{using parameter::et;
	using parameter::dt;
	using parameter::link_period;

		f<<"#time"<<"\t"<<"x"<<"\t"<<"value"<<endl;
		network.evolve_links(p);
		initialize();

		int limit= int(et/dt);
		for(int i=1; i<=limit; i++)
		{
			evolveNodes(dt,c);
			if(i%link_period==0)
				network.evolve_links(p);

			for(int j=0; j<x.size(); j++)
				f<<i*dt<<"\t"<<j<<"\t"<<x[j]<<endl;
			f<<endl;
		}
		f.close();
	}
};



int main()
{using namespace parameter;

    int iterations = nRange.size()*kRange.size()*
					 pRange.size()*cRange.size() ;
    cout<< "Total approximate iterations  :"<< iterations ;
    cout<< endl<< endl;

    for(int n :nRange)
    for(int k : kRange)
    {
        spacetimeAnalysis swn(n,k);

        for(double p : pRange )
        for(double c : cRange )
        {
            ostringstream s ;
            s<<"SWD_n="<<n<< "_k="<<k<<"_p="<< p<< "_c="<< c;
            ofstream f(s.str()+".txt");
			swn.spacetimeDynamic(f,p,c);

            progress++;
            cout<<"\r progress = "<<progress<<"\t"<<s.str()<<"\t"<<flush;
        }
    }
}


