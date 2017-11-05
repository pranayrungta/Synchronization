#include "./../../Topology/Ring.cpp"
#include "Adjacency.cpp"
int main()
{
    vector<int> nRange{26,28,30,32};
    vector<int> kRange{2};
    int iniCond = 1;



    for(auto n : nRange)
    for(auto k : kRange)
    for(int ic=1; ic<=iniCond; ic++)
    {
        Ring network(n,k);
        ostringstream ss;
        ss<<"Ring"<<"_n="<<n<<"_k="<<k<<"_ic="<<ic<<".txt";

        ofstream f(ss.str());
        laplacian(f,network);

        cout<<"\r "<<ss.str()<<"   "<<flush;
    }
}


