#include "spacetime.cpp"


int main()
{using namespace parameter;

	int progress = 0 ;
	int iterations = nRange.size()*kRange.size()*cRange.size();
    cout<< "Total approximate iterations  :"<< iterations ;
    cout<< endl<< endl;

    for(int n : nRange)
    for(int k : kRange)
    {
        Spacetime<Ring> ringspt(n,k);

        for(double c : cRange)
        {
            ostringstream s ;
            s<<"ring_n="<<n<<"_k="<<k<<"_c="<< c;
            ofstream f(s.str()+".txt");
            f<<"# "<< s.str() <<endl;
            ringspt.spt_file(f,c);

            progress++;
            cout<<"\r progress = "<<progress<<"\t"<<s.str()<<"\t"<<flush;
        }

    }
}
