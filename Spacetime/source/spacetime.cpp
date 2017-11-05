#include "./../../Dynamics_base.cpp"
#include<fstream>
#include<sstream>

template<typename topology>
class Spacetime : public Dynamics_base<topology>
{public:
    Spacetime(int n, int k):
        Dynamics_base<topology>(n,k) {}

    /// function to evolve One network and return msd
	void spt_file(ofstream& f, double c)
	{using parameter::et;
	using parameter::dt;

		f<<"#time"<<"\t"<<"x"<<"\t"<<"value"<<endl;
		this->initialize();

		int limit= int(et/dt) ;
		for(int i=1; i<=limit; i++)
		{
			this->evolveNodes(dt,c);

			for(int j=0; j<this->x.size(); j++)
				f<<i*dt<<"\t"<<j<<"\t"<<this->x[j]<<endl;
			f<<endl;
		}
		f.close();
	}
};
