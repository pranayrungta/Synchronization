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

};



int mainProgram(vector<int> nRange, vector<int> kRange,vector<double> pRange,
            int rewireSteps, double initialValue, double perturbRange, double transients,
            double dt, double coupling, int no_of_initial_conditions)
{
    cout<< "Total iterations :";
    int totalNodes = 0;
    for(auto i : nRange)
        totalNodes+=i;
    cout<< (     kRange.size()*pRange.size()*
              totalNodes*no_of_initial_conditions  )<<endl<<endl;

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

            analyser.BasinStabilityOneNode(f,initialValue,perturbRange,p,
            transients,dt,coupling,no_of_initial_conditions,rewireSteps);
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
