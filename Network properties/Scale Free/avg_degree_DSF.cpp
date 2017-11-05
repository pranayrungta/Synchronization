#include "./../../../Programs/Program v3.0 (virtual function)/Topology/DSF.cpp"
#include<fstream>
using namespace std;

template<typename topology>
double avgDegree(topology& links)
{
	double avg=0;
	for(int i=0; i<links.size(); i++)
		avg+=links[i].size();
	avg/=links.size();
	return avg;
}


int main()
{
    vector<int> dsf_order{3,4,5,6};
    ofstream f("DSF.txt");

    f<<"# DSF"<<endl<<"# order"<<"\t"<<"avg_degree"<<endl;
    for(auto order : dsf_order)
    {
        DSF network(order);
        f<<order<<"\t"<<avgDegree(network)<<endl;
    }
	return 0;
}
