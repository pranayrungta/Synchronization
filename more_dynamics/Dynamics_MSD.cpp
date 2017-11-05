#include "more_Dynamics.cpp"

int progress = 0 ;

template<class topology>
class Dynamics_MSD : public Dynamics_base<topology>
{public:

    Dynamics_MSD(const int& n, const int& k):
    	Dynamics_base<topology>(n,k)
	{}

	//function to evolve One network and return msd
    virtual double EvolveOne(const double& c);

    //-- function to generate and write coupling vs MSD to file
    void CvsMSD(ofstream& f);
};


int maindy()
{
/*    Dynamics_MSD<Small_World> net(50,2);
    net.initialize();

    net.display_details() ;
    net.network.evolve_links(0.5);
    net.display_details();

    for(int i=0 ; i<2000; i++)
        net.evolveNodes(0.1,0);
    net.display_details();

    cout<<net.msdx()<< endl;
    cout<< net.avgx();
*/
}


///------- msd vs coupling -------------

/// function to evolve One network and return msd
template<class topology>
double Dynamics_MSD<topology>::EvolveOne(const double& c)
{using parameter::et;
using  parameter::dt;
using  parameter::lp;
    this->initialize();

    int limit= int( (et/dt) - lp );
    for(int i=1; i<=limit; i++)
        this->evolveNodes(dt,c);

    double msd=0;
    for(int i=1; i<=lp; i++)
    {
        this->evolveNodes(dt, c);
        msd += this->msdx();
    }
    msd/=lp;

    return msd;
}

///-- function to generate and write coupling vs MSD to file
template<class topology>
void Dynamics_MSD<topology>::CvsMSD(ofstream& f)
{using parameter::cRange;
using  parameter::repetitions;

    f<<"#coupling"<<"\t"<<"msd"<< endl;
    for(double c=cRange[0]; c<=cRange[1]; c+=cRange[2])
    {
        double avgMsd = 0;
        for(int repetitionNo=1; repetitionNo<=repetitions; repetitionNo++)
        {
            avgMsd += this->EvolveOne(c);
            progress++ ;
        }
        cout<< "\r count = "<< progress<< flush;
        avgMsd /= repetitions;

        f<<c<<"\t"<<avgMsd<<endl;
    }
}

