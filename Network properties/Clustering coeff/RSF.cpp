#include<sstream>
#include<fstream>
#include "ClusteringCoff.cpp"
#include "./../../Topology/RSF.cpp"

int main()
{
    vector<int> nRange {27, 81, 243, 729};
    vector<int> kRange {1,2};
    int no_of_initial_conditions = 10;


    int counter=0;
    cout<<"Total iterations :";
    cout<<nRange.size()*kRange.size()*no_of_initial_conditions<<endl;

    ofstream f("RSF.txt");
    f<<"# n \t";
    for(int k: kRange)
        f<<"k="<<k<<"\t"<<"stdev\t";
    f<<endl;

    for(auto n : nRange)
    {
        f<<n<<"\t";
        for(auto k : kRange)
        {
            clus_coeff<RSF> analyser(n,k);

            double avgCC=0, stdevCC=0;
            for(int ic=0; ic<no_of_initial_conditions; ic++)
            {
                analyser.links.recreateNetwork();
                double CC = analyser.avgCcDirected() ;
                avgCC += CC;
                stdevCC += CC*CC;

                counter++;
                cout<<"\r  count ="<<counter<<flush;
            }
            avgCC /= no_of_initial_conditions;
            stdevCC/= no_of_initial_conditions;
            stdevCC -= avgCC*avgCC;
            f<<avgCC<<"\t"<<stdevCC<<"\t";
        }
        f<<endl;
    }
	return 0;
}
