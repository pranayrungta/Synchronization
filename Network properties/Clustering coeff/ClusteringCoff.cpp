#include<iostream>
#include<vector>
using namespace std;

template<typename topology>
class clus_coeff
{
public:
    topology links;

    clus_coeff(const int n, const int k):
    	links(n,k){}

    /// Works only for undirected graph
    ///Checks if i is connected to j and not the other way around
	bool isConnected(int i, int j);

	double SingleNodeCcUndirected(int nn);

	double SingleNodeCcDirected(int nn);

	double avgCcUndirected();

	double avgCcDirected();
};


int main1()
{

	vector<vector<int>> links {{1,4},///0
								{2,0},///1
								{3,1},///2
								{4,2,1},///3
								{0,3},///4
						      };
//	clus_coeff< vector<vector<int>> > cc(links);
//
//	cout<<endl<<"Undirected = "<<cc.avgCcUndirected();
//	cout<<endl<<"Directed = "<<cc.avgCcDirected();
	return 0;
}



///----implementation of class functions--------
/// Works only for undirected graph
///Checks if i is connected to j and not the other way around
template<typename topology>
bool clus_coeff<topology>::isConnected(int i, int j)
{
    for(auto x: links[i])
        if(x==j) return true;
    return false;
}


template<typename topology>
double clus_coeff<topology>::SingleNodeCcUndirected(int nn)
{
	const int k=links[nn].size();
    if(k<2) return 0;

    int counter = 0;
    for(int i=0;   i<k; i++) /// creating combinations of two
	for(int j=i+1; j<k; j++) /// for every nbr of nn
		if( isConnected(links[nn][i],links[nn][j]) )
			counter++;
    double tot_poss_conn = 0.5*k*(k-1);
    return(counter/tot_poss_conn);
}

template<typename topology>
double clus_coeff<topology>::avgCcUndirected()
{
    double avg_cc = 0;
    for(int i=0;i<links.size();i++)
        avg_cc += SingleNodeCcUndirected(i);
    avg_cc /= links.size();
    return avg_cc;
}


template<typename topology>
double clus_coeff<topology>::SingleNodeCcDirected(int nn)
{
	const int k=links[nn].size();
    if(k<2) return 0;

    int counter = 0;
    for(int i=0;i<k;i++)
	for(int j=0;j<k;j++)
		if(isConnected(links[nn][i],links[nn][j]))
			counter++;
    double tot_poss_conn = k*(k-1);
    return(counter/tot_poss_conn);
}

template<typename topology>
double clus_coeff<topology>::avgCcDirected()
{
    double avg_cc = 0;
    for(int i=0;i<links.size();i++)
        avg_cc += SingleNodeCcDirected(i);
    avg_cc /= links.size();
    return avg_cc;
}
