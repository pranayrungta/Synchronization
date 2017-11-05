#include<sstream>
#include<fstream>
#include "ClusteringCoff.cpp"
#include "./../../Topology/Small_World.cpp"

int main()
{
    vector<int> nRange {100};
    vector<int> kRange {2};
    vector<double> pRange { 0, 1.05, 0.1} ;/// range
    int no_of_initial_conditions = 1000;



    int counter=0;
    cout<<"Total iterations :";
    cout<<nRange.size()*kRange.size()*
    ( int( (pRange[1]-pRange[0])/pRange[2] ) + 1)
    *no_of_initial_conditions<<endl;

    for(auto n : nRange)
    for(auto k : kRange)
    {
        clus_coeff<Small_World> analyser(n,k);
        ostringstream s;
        s<<"SW_n="<<n<<"_k="<<k;
        ofstream f( s.str()+".txt" );
        f<<"# "<<s.str()<<endl;
        f<<"# p"<<"\t"<<"clusteringCoeff"<<"\t"<<"stdev"<<endl;
        for(double p= pRange[0]; p<=pRange[1]; p+=pRange[2])
        {
            double avgCC=0, stdevCC=0;
            for(int ic=0; ic<no_of_initial_conditions; ic++)
            {
                analyser.links.evolve_links(p);
                double CC = analyser.avgCcDirected() ;
                avgCC += CC;
                stdevCC += CC*CC;

                counter++;
            }
			cout<<"\r  count ="<<counter<<flush;
            avgCC /= no_of_initial_conditions;
            stdevCC/= no_of_initial_conditions;
            stdevCC -= avgCC*avgCC;
            f<<p<<"\t"<<avgCC<<"\t"<<stdevCC<<endl;
        }
    }
	return 0;
}
