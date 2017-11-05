#include "spacetime.cpp"

int main()
{using namespace parameter;

	int progress = 0 ;
    int iterations = orderRange.size()*cRange.size();
    cout<< "Total approximate iterations  :"<< iterations ;
    cout<< endl<< endl;

    for(int order :orderRange)
    {
        Spacetime<DSF> dsf_spt(order,-1);
        for(double c : cRange)
        {
            ostringstream s ;
            s<<"DSF_order="<<order<< "_c="<< c;
            ofstream f(s.str()+".txt");
            dsf_spt.spt_file(f,c);

            progress++;
            cout<<"\r progress = "<<progress<<"\t"<<s.str()<<"\t"<<flush;
        }
    }
}
