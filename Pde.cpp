#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdio"

using namespace std;



int main(int argc, char const *argv[])
{
	cout << "\n\n\nIniciando programa PDE\n";

	
	float conductivity=1.62; 
	float Cp=820;
	float rho=2.71; 
	float rho_si=rho/1000*1000000; 


	
	float Trod = 100; 
	float Drod = 0.1; 



	float L=0.5; 
	int nx=64; 
	float dx=L/(nx-1); 

	
	float Tpresent[nx][nx];
	float Tfuture[nx][nx];
	int rock_int[nx][nx];

	int i, j;

	for (i = 0; i < nx; ++i)
	{
		for (j = 0; j < nx; ++j)
		{
			if (pow((i-nx/2)*dx,2) + pow((j-nx/2)*dx,2) < pow(Drod/2,2))
			{ 
				Tpresent[i][j] = Trod;
				Tfuture[i][j] = Trod;
				rock_int[i][j] = 0;
			}else
			{ /
				Tpresent[i][j] = 0.0;
				Tfuture[i][j] = 0.0;
				rock_int[i][j] = 1;
			}
		}
	}


	//Condicion frontera
	for (i = 0; i < nx; ++i)
	{
		for (j = 0; j < nx; ++j){
			if (i==0 || j==0 || i==nx-1 || j==nx-1)
			{ 
				Tpresent[i][j] = 10;
				Tfuture[i][j] = 10;
				rock_int[i][j] = 0;
			}
		}
	}



	
	float nu=conductivity/(Cp*rho);
	float C=0.1;
	float dt=C*dx/nu;

	int k;
	int nt=500;
	float tf=dt*nt;

	
	ofstream rock("rock.csv");

	for (k = 0; k < nt; ++k)
	{
		for (i = 0; i < nx; ++i)
		{
			for (j = 0; j < nx; ++j)
			{
				if (rock_int[i][j]==1)
				{
					Tfuture[i][j] = C*(Tpresent[i-1][j] + Tpresent[i+1][j] + Tpresent[i][j-1] + Tpresent[i][j+1] - 4*Tpresent[i][j]) + Tpresent[i][j];
				}
			}

		}


		
		for (i = 0; i < nx; ++i)
		{
			for (j = 0; j < nx; ++j)
			{
				if (rock_int[i][j]==1)
				{
					Tpresent[i][j] = Tfuture[i][j];
				}

			}
		}

		
		for (i = 0; i < nx; ++i)
		{
			for (j = 0; j < nx; ++j)
			{
				rock << Tpresent[i][j] << ",";
			}
		}
		rock << "\n";


	}


	



	cout << "Programa Finalizado\n\n\n";
	return 0;
}
