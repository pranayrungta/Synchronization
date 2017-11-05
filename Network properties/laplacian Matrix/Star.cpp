#include "./../../Topology/Star.cpp"
#include "Adjacency.cpp"

int main()
{
    vector<int> nRange{100, 200, 400};
    int iniCond = 1;



    for(auto n : nRange)
    for(int ic=1; ic<=iniCond; ic++)
    {
        Star network(n,-1);
        ostringstream ss;
        ss<<"Star"<<"_n="<<n<<"_ic="<<ic<<".txt";

        ofstream f(ss.str());
        laplacian(f,network);

        cout<<"\r "<<ss.str()<<"   "<<flush;
    }
}

