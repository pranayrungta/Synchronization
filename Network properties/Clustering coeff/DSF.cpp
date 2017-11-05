#include<fstream>
#include "ClusteringCoff.cpp"
#include "./../../Topology/DSF.cpp"


int main()
{
    vector<int> orderRange{3,4,5,6};

    ofstream f("DSF.txt");
    f<<"# order"<<"\t"<<"ClusteringCoeff"<<endl;
    for(auto order: orderRange)
    {
        clus_coeff<DSF> analyser(order,-1);
        f<<order<<"\t"<<analyser.avgCcUndirected()<<endl;
    }
	return 0;
}
