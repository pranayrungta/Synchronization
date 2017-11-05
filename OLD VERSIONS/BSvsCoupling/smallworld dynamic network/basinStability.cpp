#include "./../../../Topology/Small_World.cpp"
#include "./../../../Dynamics.cpp"
#include<fstream>
#include<sstream>

int progress = 0;

class BasinStability
{public:

    Dynamics<Small_World> system;

    BasinStability(int n, int k):
        system(n,k)
    {}

    bool syncAfterPerturb(double initialValue, double perturbRange, int perturbNode, double p,
                          double transients, double dt, double coupling, int rewireSteps) ;

    void BasinStabilityOneNode(ofstream& f, double initialValue, double perturbRange, double p,
                double transients, double dt, double coupling, int noic, int rewireSteps) ;

    void BSvsCoupling(ofstream& f, vector<double>& cRange, double initialValue, double perturbRange,
                    double p, double transients, double dt, int noic, int rewireSteps) ;
};



int mainProgram(vector<int>& nRange, vector<int>& kRange,vector<double>& pRange, vector<double>& cRange,
            int rewireSteps, double initialValue, double perturbRange,
            double transients, double dt, int no_of_initial_conditions)
{
    cout<< "Total iterations :";
    cout<< (      nRange.size()*kRange.size()*pRange.size()*no_of_initial_conditions*
                 (     (cRange[1]-cRange[0])/cRange[2]+1     )      )<<endl<<endl;

    for(auto n : nRange)
    for(auto k : kRange)
    {
        BasinStability analyser(n,k);
        for(auto p : pRange)
        {
            ostringstream s;
            s<< "SW_dynamic_"<<"n="<<n <<"_k="<<k <<"_p="<<p;
            string filename = s.str() + ".txt";
            ofstream f(filename);
            f<<"# "<< s.str()<<endl;

            analyser.BSvsCoupling(f,cRange,initialValue,perturbRange,p,
            transients,dt,no_of_initial_conditions,rewireSteps);
        }
    }

    return 0;
}





/// implementation of class functions

bool BasinStability::syncAfterPerturb(double initialValue, double perturbRange, int perturbNode, double p,
                      double transients, double dt, double coupling, int rewireSteps)
{
    ///initialize
    for(int i=0; i<system.x.size(); i++)
        system.x[i] = initialValue;
    /// Perturb one node
    uniform_real_distribution<double> perturb(0,perturbRange);
    system.x[perturbNode] = perturb(generator);

    int tdLimit = int( round(transients/dt) );
    for(int td=0; td<=tdLimit; td++)
    {
        if(td%rewireSteps==0)
            system.network.evolve_links(p);
        system.evolveNodes(dt,0,coupling);
    }
        //system.display_details();
    /// check for sync- all in same well
    double firstNode = system.x[0];
    for(int i=1; i<system.x.size(); i++)
        if(system.x[i]*firstNode<0)
            return false;
    return true;
}



void BasinStability:: BasinStabilityOneNode(ofstream& f, double initialValue, double perturbRange, double p,
            double transients, double dt, double coupling, int noic, int rewireSteps)
{
    f<< "# node"<< "\t"<< "basinStability"<<endl;
    double bs;
    for(int node=0; node<system.x.size(); node++)
    {
        /// calculating basin stability for one node
        int syncNo = 0;
        for(int i=0 ; i<noic; i++)
        {
            bool isSync = syncAfterPerturb(initialValue,perturbRange,node,p,
                                transients,dt,coupling, rewireSteps);
            if(isSync) syncNo++;
            progress++;
        }
        cout<< "\r progress : "<< progress<< "    "<< flush;
        bs = (1.0*syncNo)/noic ;
        f<< node<< "\t"<< bs<< endl;
    }
    f.close();
}


void BasinStability:: BSvsCoupling(ofstream& f, vector<double>& cRange, double initialValue, double perturbRange, double p,
            double transients, double dt, int noic, int rewireSteps)
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
            bool isSync = syncAfterPerturb(initialValue,perturbRange,rNode,p,transients,dt,c,rewireSteps);
            if(isSync) syncNo++;
            progress++;
        }
        cout<< "\r progress : "<< progress<< "    "<< flush;
        bs = (1.0*syncNo)/noic ;
        f<< c<< "\t"<< bs<< endl;
    }
    f.close();
}
