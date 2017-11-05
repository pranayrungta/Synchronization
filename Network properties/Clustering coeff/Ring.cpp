#include<fstream>
#include "./ClusteringCoff.cpp"
#include "./../../Topology/Ring.cpp"

int main()
{
    vector<int> nRange{100,200,400,800};
    vector<int> kRange{1,2,3,4};


    ofstream f("Ring.txt");
    f<<"# n \t";
    for(int k: kRange)
        f<<"k="<<k<<"\t";
    f<<endl;
    for(int n: nRange)
    {
        f<<n<<"\t";
        for(int k: kRange)
        {
            clus_coeff<Ring> analyser(n,k);
            f<<analyser.avgCcUndirected()<<"\t";
        }
        f<<endl;
    }
	return 0;
}
