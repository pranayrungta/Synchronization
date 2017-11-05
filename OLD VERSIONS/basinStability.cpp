#include "./../Dynamics.cpp"
#include<fstream>

int progress = 0;

template<class topology>
class BasinStability
{public:

    Dynamics<topology> system;

    BasinStability(int n, int k):
        system(n,k)
    {}

    /// function to initialize a system , perturb one node in perturbRange,
    /// evolve in time and return whether it is synchronized or not
    /// It works for DSF, RSF, Ring, static Small world but not dynamic Small World
    bool syncAfterPerturb(double initialValue, double perturbRange, int perturbNode,
                          double transients, double dt, double coupling) ;


    void BasinStabilityOneNode(ofstream& f, double initialValue, double perturbRange,
                double transients, double dt, double coupling, int noic) ;

    void BSvsCoupling(ofstream& f, vector<double>& cRange, double initialValue, double perturbRange,
                double transients, double dt, int noic) ;
};

int mainbs()
{
    return 0;
}



///------------implementation of class functions-----------
/// function to initialize a system , perturb one node in perturbRange,
/// evolve in time and return whether it is synchronized or not.
/// It works for DSF, RSF, Ring, static Small world but not dynamic Small World
template<class topology>
bool BasinStability<topology>::syncAfterPerturb(double initialValue, double perturbRange, int perturbNode,
                      double transients, double dt, double coupling)
{
    ///initialize
    for(int i=0; i<system.x.size(); i++)
        system.x[i] = initialValue;
    /// Perturb one node
    uniform_real_distribution<double> perturb(0,perturbRange);
    system.x[perturbNode] = perturb(generator);

    for(double t=0; t<=transients; t+=dt)
        system.evolveNodes(dt,0,coupling);
    //system.display_details();

    double firstNode = system.x[0];
    for(int i=1; i<system.x.size(); i++)
        if(system.x[i]*firstNode<0)
            return false;
    return true;
}



template<class topology>
void BasinStability<topology>::BasinStabilityOneNode(ofstream& f, double initialValue, double perturbRange,
            double transients, double dt, double coupling, int noic)
{
    f<< "# node"<< "\t"<< "basinStability"<<endl;
    double bs;
    for(int node=0; node<system.x.size(); node++)
    {
        /// calculating basin stability for one node
        int syncNo = 0;
        for(int i=0 ; i<noic; i++)
        {
            bool isSync = syncAfterPerturb(initialValue,perturbRange,node,transients,dt,coupling);
            if(isSync) syncNo++;
            progress++;
        }
        cout<< "\r progress : "<< progress<< "    "<< flush;
        bs = (1.0*syncNo)/noic ;
        f<< node<< "\t"<< bs<< endl;
    }
    f.close();
}

template<class topology> void BasinStability<topology>:: BSvsCoupling (
    ofstream& f, vector<double>& cRange, double initialValue, double perturbRange,
    double transients, double dt, int noic)
{
    f<< "# coupling"<< "\t"<< "basinStability"<<endl;

    double bs;
    uniform_int_distribution<int> randNode( 0,system.x.size()-1 );
    for(double c=cRange[0]; c<=cRange[1]; c+=cRange[2])
    {
        /// calculating basin stability for one coupling value
        int syncNo = 0;
        for(int i=0 ; i<noic; i++)
        {
            int rNode = randNode(generator);
            bool isSync = syncAfterPerturb(initialValue,perturbRange,rNode,transients,dt,c);
            if(isSync) syncNo++;
            progress++;
        }
        cout<< "\r progress : "<< progress<< "    "<< flush;
        bs = (1.0*syncNo)/noic ;
        f<< c<< "\t"<< bs<< endl;
    }
    f.close();
}
