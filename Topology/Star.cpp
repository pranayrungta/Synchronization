#include "common_base.cpp"

class Star : public topology_base
{public:
    //Constructor
    Star(const int n, const short dummy=-1)
	{
		nbr = vector<vector<int>>( n, vector<int>(1) );
		nbr[0].reserve(nbr.size()-1);
		nbr[0].resize(0);
		for(int i=1; i<nbr.size(); i++)
		{
			nbr[0].push_back(i);
			nbr[i][0] = 0;
		}
	}
};

int mainStar()
{
    Star a(10,-1);
    cout<<a<<a[0]<<endl;
//    cout<<a.avgx();
//    cout<< endl<< 1.2 ;
    return 0;
}
