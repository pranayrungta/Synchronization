#include "./../../Topology/topology v1.3 (map added)/Random Scale Free.cpp"
#include "./../../Topology/Small_World.cpp"
#include "./../../Topology/Deterministic Scale Free.cpp"
#include "./../../Topology/Ring.cpp"

#include "./../basinStability.cpp"
#include<sstream>


int mainbPrograms()
{
    return 0;
}


///function to produce results for ring
void RingProgram(vector<int>& nRange, vector<int>& kRange, double initialValue,
            double perturbRange, double transients, double dt, double coupling, int no_of_initial_conditions )
{
    cout<< "total iterations :";
    int totalNodes = 0;
    for(auto i : nRange)
        totalNodes+=i;
    cout<< (totalNodes*kRange.size()*no_of_initial_conditions )<<endl<<endl;


    for(auto n : nRange)
    for(auto k : kRange)
    {
        ostringstream s;
        s<< "Ring_"<<"n="<<n <<"_k="<<k;
        string filename = s.str() + ".txt";
        ofstream f(filename);
        f<<"# "<< s.str()<<endl;

        BasinStability<Ring> analyser(n,k);
        analyser.BasinStabilityOneNode(f,initialValue,perturbRange,
        transients,dt,coupling,no_of_initial_conditions);
    }
}




void DSFProgram(vector<int>& orderRange, double initialValue,double perturbRange,
                 double transients, double dt, double coupling,
                int no_of_initial_conditions )
{
    cout<< "Total iterations :";
    int totalNodes = 0;
    for(auto i : orderRange)
        totalNodes+=pow(3,i);
    cout<< (totalNodes*no_of_initial_conditions )<<endl<<endl;

    for(auto order : orderRange)
    {
        ostringstream s;
        s<< "DSF_"<<"order="<<order;
        string filename = s.str() + ".txt";
        ofstream f(filename);
        f<<"# "<< s.str()<<endl;

        BasinStability<DeterministicScaleFree> analyser(order,-1);
        analyser.BasinStabilityOneNode(f,initialValue,perturbRange,
        transients,dt,coupling,no_of_initial_conditions);
    }
}


///function to produce results for ring
void SWstaticProgram(vector<int>& nRange, vector<int>& kRange, vector<double>& pRange,
            double initialValue,double perturbRange, double transients, double dt,
            double coupling, int no_of_initial_conditions )

{
    cout<< "Total iterations :";
    int totalNodes = 0;
    for(auto i : nRange)
        totalNodes+=i;
    cout<< (totalNodes*kRange.size()*pRange.size()*
            no_of_initial_conditions )<<endl<<endl;



    for(auto n : nRange)
    for(auto k : kRange)
    {
        BasinStability<Small_World> analyser(n,k);
        for(auto p : pRange)
        {
            analyser.system.network.evolve_links(p);///static network

            ostringstream s1;
            s1<< "SW_static_"<<"n="<<n <<"_k="<<k <<"_p="<<p<<"config.txt";
            ofstream config ( s1.str() );
            analyser.system.network.display_connections(config);
            config.close();

            ostringstream s;
            s<< "SW_static_"<<"n="<<n <<"_k="<<k<<"_p="<<p;
            string filename = s.str() + ".txt";
            ofstream f(filename);
            f<<"# "<< s.str()<<endl;

            analyser.BasinStabilityOneNode(f,initialValue,perturbRange,
            transients,dt,coupling,no_of_initial_conditions);
        }
    }
}


///function to produce results for ring
void RSFProgram(vector<int>& nRange, vector<int>& kRange, double initialValue,
            double perturbRange, double transients, double dt, double coupling,
            int no_of_initial_conditions )
{
    cout<< "total iterations :";
    int totalNodes = 0;
    for(auto i : nRange)
        totalNodes+=i;
    cout<< (totalNodes*kRange.size()*no_of_initial_conditions )<<endl<<endl;


    for(auto n : nRange)
    for(auto k : kRange)
    {
        BasinStability<RandomScaleFree> analyser(n,k);

        ostringstream s1;
        s1<< "RSF_"<<"n="<<n <<"_k="<<k<<"config.txt";
        ofstream config ( s1.str() );
        analyser.system.network.display(config);
        config.close();


        ostringstream s;
        s<< "RSF_"<<"n="<<n <<"_k="<<k;
        string filename = s.str() + ".txt";
        ofstream f(filename);
        f<<"# "<< s.str()<<endl;

        analyser.BasinStabilityOneNode(f,initialValue,perturbRange,
        transients,dt,coupling,no_of_initial_conditions);
    }
}
