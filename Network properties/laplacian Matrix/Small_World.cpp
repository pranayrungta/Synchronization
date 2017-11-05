#include "./../../Topology/Small_World.cpp"
#include "Adjacency.cpp"

int main()
{
    vector<int> nRange{10};
    vector<int> kRange{2};
    vector<double> pRange{0.2, 1};
    int iniCond = 2;



    for(auto n : nRange)
    for(auto k : kRange)
	{
		Small_World network(n,k);
		for(auto p : pRange)
		for(int ic=1; ic<=iniCond; ic++)
		{
			network.evolve_links(p);
			ostringstream ss;
			ss<<"sw"<<"_n="<<n<<"_k="<<k<<"_p="<<p<<"_ic="<<ic<<".txt";

			ofstream f(ss.str());
			laplacian(f,network);

			cout<<"\r "<<ss.str()<<"   "<<flush;
		}
	}
}
