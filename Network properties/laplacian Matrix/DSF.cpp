#include "./../../Topology/DSF.cpp"
#include "Adjacency.cpp"
int main()
{
    vector<int> orderRange{2};
    int iniCond = 1;



    for(auto order : orderRange)
    for(int ic=1; ic<=iniCond; ic++)
    {
        DSF network(order,-1);
        ostringstream ss;
        ss<<"DSF"<<"_order="<<order<<"_ic="<<ic<<".txt";

        ofstream f(ss.str());
        laplacian(f,network);

        cout<<"\r "<<ss.str()<<"   "<<flush;
    }
}


