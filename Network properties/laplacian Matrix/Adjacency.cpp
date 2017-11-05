#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;

template<class topology>
void laplacian(ostream& os, topology links)
{
    const int n= links.size();
    vector<vector<int>> adjMat(n,vector<int>(n));
    for(int i=0; i<n; i++)
	for(auto j : links[i])
		adjMat[i][j] = 1;

    for(auto row : adjMat)
    {
        for(auto j: row)
            os<<j<<"\t";
        os<<endl;
    }
}
