#include "./../../Topology/Deterministic Scale Free.cpp"
#include "./../../Dynamics.cpp"
#include<fstream>
#include<sstream>

int progress = 0;

class BS_DSF : public Dynamics<DeterministicScaleFree>
{public:

    BS_DSF(int n, int k): Dynamics<DeterministicScaleFree>(n,k)
    {}

    double fixedconfigBS(vector<int>& fnodes, double c);
	{   using namespace parameter;

		double negetive_syncCount = 0;
		for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
		{
			initialize(fnodes, initial_value,spread,
						perturbRange_initial,perturbRange_final);
			for(double t=0; t<transients; t+=dt)
				evolveNodes(dt,0,c);
			//display_details();
			if(syncWell()==well::negetiveWell)
				negetive_syncCount++;

			progress++;
		}
		return (negetive_syncCount/repetitions);
	}



	void BSvsfnode(ofstream& f, double c) ;
	{   using namespace parameter;

		f<<"# fnode"<<"\t" <<"mean"<<"\t" <<"stdev"<<endl;
		/// nopn = no of perturb nodes
		for(int nopn=1; nopn<=x.size()/2; nopn++)
		{
			double mean_bs = 0,  stdev_bs = 0;

			/// ic - averaging on nodes selected for perturbation
			///      for fixed number of perturb nodes
			for(int ic=0; ic<no_of_initial_conditions; ic++)
			{
				double bs = fixedconfigBS(perturbNodes,c);
				mean_bs  +=  bs   ;
				stdev_bs += bs*bs ;
			}
			mean_bs /= no_of_initial_conditions;
			stdev_bs/= no_of_initial_conditions;
			stdev_bs = sqrt( abs(stdev_bs-mean_bs*mean_bs)  ) ;

			f<<nopn<<"\t"<<mean_bs<<"\t"<<stdev_bs<<endl;

			cout<<"\r progress = "<<progress<<"    "<<flush;
		}
		f.close();
	}
};




int main()
{using namespace parameter;

    int ti = 0;
    for(auto n : orderRange)
        ti+=pow(3,n)/2;
    cout<<"Total iterations :"<<(ti*cRange.size()*repetitions*
                                no_of_initial_conditions) <<endl;

    for(auto order : orderRange)
    {
        BS_DSF analyser(order,-1);
        for(auto c : cRange)
        {
            ostringstream s;
            s<<"DSF"<<"_order="<<order <<"_c="<<c ;

            ofstream f(s.str()+".txt");
            f<<"#"<<s.str()<<endl;

            analyser.BSvsfnode(f,c);
        }
    }
}
