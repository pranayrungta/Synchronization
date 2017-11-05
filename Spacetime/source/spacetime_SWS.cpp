#include "spacetime.cpp"

class SWS_spacetime : protected Spacetime<Small_World>
{public:
    SWS_spacetime(int n, int k):
        Spacetime<Small_World>(n,k) {}

    /// function to evolve One network and return msd
	void spacetimeStatic(ofstream& f, double p, double c)
	{
		this->network.evolve_links(p);
		this->spt_file(f,c);
	}
};

int main()
{using namespace parameter;

	int progress = 0 ;
    int iterations = nRange.size()*kRange.size()*
					 pRange.size()*cRange.size() ;
    cout<< "Total approximate iterations  :"<< iterations ;
    cout<< endl<< endl;

    for(int n :nRange)
    for(int k : kRange)
    {
        SWS_spacetime swn(n,k);

        for(double p : pRange )
        for(double c : cRange )
        {
            ostringstream s ;
            s<<"SWS_n="<<n<<"_k="<<k<<"_p="<< p<< "_c="<< c;
            ofstream f(s.str()+".txt");
			swn.spacetimeStatic(f,p,c);

            progress++;
            cout<<"\r progress = "<<progress<<"\t"<<s.str()<<"\t"<<flush;
        }
    }
}
