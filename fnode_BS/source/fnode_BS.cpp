#include "./../../Dynamics_base.cpp"
#include<fstream>

int progress=0;

template<class topology>
class BS_fnode : public Dynamics_base<topology>
{public:

    BS_fnode(const int& n, const int& k):
    	Dynamics_base<topology>(n,k)
	{}

    void BSvsfnode(ofstream& f, double c);

protected:
	//function to evolve One network and return msd
    virtual double syncWell_after_evolve(const int& nopn, const double& c);

    void fnode_BS_initialize(const vector<int>& fnodes);

    int syncWell();
private:
    constexpr static int unsync = 0;
};






///function to initialize nodes in a range (value-spread, value+spread)
template<class topology>
void BS_fnode<topology>::fnode_BS_initialize(const vector<int>& fnodes)
{using parameter::initial_well;
using parameter::spread;
using parameter::perturbRange_initial;
using parameter::perturbRange_final;

    uniform_real_distribution<double>  distribution(initial_well-spread, initial_well+spread);
    for(int i=0; i<this->x.size() ; i++)
    {
        this->x[i]= distribution(generator) ;
        this->Dx[i]=0;
    }

    uniform_real_distribution<double>  perturbRange(perturbRange_initial, perturbRange_final);
    for(auto nodeNo : fnodes)
        this->x[nodeNo] = perturbRange(generator);
}



///function to check if all nodes are in same well
template<class topology>
int BS_fnode<topology>::syncWell()
{
    double& first = this->x[0];
    for(int i=1; i<this->x.size(); i++)
        if(this->x[i]*first<0)
            return unsync;

    if(first>0)return positive_well;
    if(first<0)return negative_well;
}

//function to evolve One network and return msd
template<class topology>
double BS_fnode<topology>::syncWell_after_evolve(const int& nopn, const double& c)
{using parameter::repetitions;
using parameter::transients;
using  parameter::dt;

    vector<int> perturbNodes = sample(0, this->network.size()-1, nopn,-1);
    double stableCount = 0;
    for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
    {
        fnode_BS_initialize(perturbNodes);
        for(double t=0; t<transients; t+=dt)
            this->evolveNodes(dt, c);
        if(syncWell()==parameter::initial_well)
            stableCount++;

        progress++;
    }
    return (stableCount/repetitions);
}

template<class topology>
void BS_fnode<topology>::BSvsfnode(ofstream& f, double c)
{using parameter::no_of_initial_conditions;

    f<<"# fnode"<<"\t" <<"mean"<<endl;
    /// nopn = no of perturb nodes
    for(int nopn=1; nopn<=this->network.size()/2; nopn+=2)
    {
        double mean_bs = 0;
        for(int ic=0; ic<no_of_initial_conditions; ic++)
            mean_bs  +=  syncWell_after_evolve(nopn,c);
        mean_bs /= no_of_initial_conditions;
        f<<nopn<<"\t"<<mean_bs<<endl;

        cout<<"\r progress = "<<progress<<"    "<<flush;
    }
}
