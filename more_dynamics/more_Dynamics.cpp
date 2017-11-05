//#include "./../Topology/Small_World.cpp"
//#include "piecewise_linear/piecewise_linear.cpp"

template<class topology>
class Dynamics_base
{public:

    topology network;
	local_Dynamics g;
    vector<double> x, Dx;

    Dynamics_base(const int& n, const int& k):network(n,k)
	{
		x  = vector<double>(network.size());
		Dx = vector<double>(network.size());
	}

    void initialize();

    void evolveNodes(const double& dt, const double& c);

    double avgx();

    double msdx();

    void display_details();

};

//#include "./Topology/Small_World.cpp"
int maind()
{
/*    Dynamics_base<Small_World> net(50,2);
    net.initialize();

    net.display_details() ;

    net.network.evolve_links(0.5);

    net.display_details();


    for(int i=0 ; i<2000; i++)
        net.evolveNodes(0.1,0,0);
    net.display_details();

    cout<<net.msdx()<< endl;
    cout<< net.avgx();
*/
}



//------------implementation of class functions----------------


//function to return avg value
template<class topology>
double Dynamics_base<topology>:: msdx()
{
    int n= x.size() ;
    double x1=0, x2=0, msd=0;
    for(int i=0; i<n; i++)
    {
        x1+=x[i];
        x2+=x[i]*x[i];
    }

    msd = abs( x2/n - x1*x1/(n*n) );
    return sqrt(msd);

}


//function to return avg value
template<class topology>
double Dynamics_base<topology>:: avgx()
{
    double average =0;
    for(int i=0; i<network.size(); i++)
        average+=x[i];
    average /= network.size();
    return average;
}


//function to evolve sites
template<class topology>
void Dynamics_base<topology>:: evolveNodes(const double&dt, const double& c)
{
    double nf=0;
    int i,j;
    //Calculating derivatives
    for(i=0; i<network.size(); i++)
    {
        nf=0;
        for( j=0; j<network[i].size(); j++ )
            nf+=x[ network[i][j] ];
        nf /= network[i].size();

        Dx[i] = g(x[i])  +  c*(nf- x[i]);
    }
    //Evolving nodes
    for( i=0; i<network.size(); i++)
        x[i] += Dx[i] * dt  ;
}

//reinitialize
template<class topology>
void Dynamics_base<topology>:: initialize()
{
    uniform_real_distribution<double>  distribution(-1, 1);
    for(int i=0; i<network.size() ; i++)
    {
        x[i]= distribution(generator) ;
        Dx[i]=0;
    }
}

// display details
template<class topology>
void Dynamics_base<topology>::display_details()
{
    for(int i=0; i<network.size(); i++)
    {
        cout<< "x = "<<x[i]<< "\tDx = "<<Dx[i];
        cout<< "\tNode "<< i<< " :\t";
        for(int j=0; j<network[i].size(); j++)
            cout<< network[i][j]<< "  " ;
        cout<< endl;
    }
}
