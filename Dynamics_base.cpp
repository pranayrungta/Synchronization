//#include "./Topology/Small_World.cpp"

template<class topology>
class Dynamics_base
{public:
    topology network;
    vector<double> x, Dx;


    Dynamics_base(const int n, const int k): network(n,k)
	{
		x  = vector<double> (network.size());
		Dx = vector<double> (network.size());
	}

    void initialize();

    void evolveNodes(const double dt, const double c);

    double avgx()const;

    double msdx()const;

    void display_details()const;
};


int maind()
{
/*    Dynamics_base<Small_World> net(50,2);
    net.initialize();

    net.display_details() ;
    net.network.evolve_links(0.5);
    net.display_details();

    for(int i=0 ; i<2000; i++)
        net.evolveNodes(0.1,0);
    net.display_details();

    cout<<net.msdx()<< endl;
    cout<< net.avgx();
*/
}


///------------implementation of class functions----------------


//function to return avg value
template<class topology>
double Dynamics_base<topology>:: msdx()const
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
double Dynamics_base<topology>:: avgx()const
{
    int n= x.size() ;
    double average =0;
    for(int i=0; i<n; i++)
        average+=x[i];
    average /= n;
    return average;
}


//function to evolve sites
template<class topology>
void Dynamics_base<topology>:: evolveNodes(const double dt, const double c)
{
    int n= x.size();
    double nf=0;

    int i,j;
    //Calculating derivatives
    for(i=0; i<n; i++)
    {
        nf=0;
        for( j=0; j<network[i].size(); j++ )
            nf+=x[ network[i][j] ];
        nf /= network[i].size();

        Dx[i] = ( x[i]- x[i]*x[i]*x[i] ) + c*(nf- x[i]) ;
    }
    //Evolving nodes
    for( i=0; i<n; i++)
        x[i] += Dx[i] * dt  ;
}

//reinitialize
template<class topology>
void Dynamics_base<topology>:: initialize()
{
    int     n = x.size();
    uniform_real_distribution<double>  distribution(-1, 1);
    //initializing
    for(int i=0; i<n ; i++)
    {
        x[i]= distribution(generator) ;
        Dx[i]=0;
    }

}

// display details
template<class topology>
void Dynamics_base<topology>::display_details()const
{
    for(int i=0; i<network.size(); i++)
    {
        cout<< "x = "<<x[i]<< "\tDx = "<<Dx[i];
        cout<< "\tNode "<< i<< " :\t";
        for(int j=0; j<network[i].size(); j++)
            cout<< network[i][j]<< "  " ;
        cout<< endl;
    }
    cout<< endl;
}
