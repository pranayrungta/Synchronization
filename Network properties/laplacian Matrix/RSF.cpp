#include "./../../Topology/RSF.cpp"
#include "Adjacency.cpp"

int main()
{
    vector<int> nRange{27,81,243,729};
    vector<int> kRange{1};
    int iniCond = 100;



    for(auto n : nRange)
    for(auto k : kRange)
    for(int ic=1; ic<=iniCond; ic++)
    {
        RSF network(n,k);
        ostringstream ss;
        ss<<"RSF"<<"_n="<<n<<"_k="<<k<<"_ic="<<ic<<".txt";

        ofstream f(ss.str());
        laplacian(f,network);

        cout<<"\r "<<ss.str()<<"   "<<flush;
    }
}

