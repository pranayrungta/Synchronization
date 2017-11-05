#include "./../../../Programs/Program v3.0 (virtual function)/Topology/RSF.cpp"
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
    vector<int> nRange{100, 200, 400} ;
    vector<int> kRange{1, 2, 3, 4} ;
    int repetitions = 100;


    ofstream f("RSF.txt");
    f<<"# RSF"<<endl;
    f<<"# n"<<"\t";
    for(auto k : kRange)
        f<<"k="<<k<<"\t";
    f<<endl;

    for(auto n : nRange)
    {
        f<<n<<"\t";
        for(auto k: kRange)
        {
            RSF network(n,k);
            double avg = 0 ;
            for(int i=0; i<repetitions; i++)
            {
                network.recreateNetwork();
                avg += avgDegree(network);
            }
            avg/=repetitions;
            f<<avg<<"\t";
        }
        f<<endl;
    }
}
