#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdio"

using namespace std;



int main(int argc, char const *argv[])
{
	
	float g=-10.0; 
	float c=0.2; 
	float m=0.2; 

	float v0mag = 300.0; 
	float alpha0= 45.0; 

	
	float dt = 0.001; 
	int nt = 2000; 



	float x[nt];
	float y[nt];
	float vx[nt];
	float vy[nt];


	
	x[0] = 0.0;
	y[0] = 0.0;
	vx[0] = v0mag*cos(alpha0/180*M_PI);
	vy[0] = v0mag*sin(alpha0/180*M_PI);


	

	float k1x, k1y, k1vx, k1vy;
	float k2x, k2y, k2vx, k2vy;
	float k3x, k3y, k3vx, k3vy;
	float k4x, k4y, k4vx, k4vy;


	ofstream projectile("projectile.csv");


	int i;
	int lastIt=0;

	for (i = 0; i < nt-1; ++i)
	{

		projectile << i*dt << "," << x[i] << "," << y[i] << "," << vx[i] << "," << vy[i] << "\n";

		
		k1x = vx[i];
		k1y = vy[i];
		k1vx = -c/m*pow( pow(vx[i],2) + pow(vy[i],2) , 0.5)*vx[i];
		k1vy = g -c/m*pow( pow(vx[i],2) + pow(vy[i],2) , 0.5)*vy[i];

		k2x = vx[i] + 0.5*dt*k1vx;
		k2y = vy[i] + 0.5*dt*k1vy;
		k2vx = -c/m*pow( pow(vx[i]+0.5*dt*k1vx,2) + pow(vy[i]+0.5*dt*k1vy,2) , 0.5) * (vx[i]+0.5*dt*k1vx);
		k2vy = g -c/m*pow( pow(vx[i]+0.5*dt*k1vx,2) + pow(vy[i]+0.5*dt*k1vy,2) , 0.5) * (vy[i]+0.5*dt*k1vy);		

		k3x = vx[i] + 0.5*dt*k2vx;
		k3y = vy[i] + 0.5*dt*k2vy;
		k3vx = -c/m*pow( pow(vx[i]+0.5*dt*k2vx,2) + pow(vy[i]+0.5*dt*k2vy,2) , 0.5) * (vx[i]+0.5*dt*k2vx);
		k3vy = g -c/m*pow( pow(vx[i]+0.5*dt*k2vx,2) + pow(vy[i]+0.5*dt*k2vy,2) , 0.5) * (vy[i]+0.5*dt*k2vy);		

		k4x = vx[i] + 1.0*dt*k3vx;
		k4y = vy[i] + 1.0*dt*k3vy;
		k4vx = -c/m*pow( pow(vx[i]+1.0*dt*k3vx,2) + pow(vy[i]+1.0*dt*k3vy,2) , 0.5) * (vx[i]+1.0*dt*k3vx);
		k4vy = g -c/m*pow( pow(vx[i]+1.0*dt*k3vx,2) + pow(vy[i]+1.0*dt*k3vy,2) , 0.5) * (vy[i]+1.0*dt*k3vy);		
		
	
		x[i+1] = x[i] + 1.0/6.0*(k1x + 2.0*k2x + 2.0*k3x + k4x)*dt;
		y[i+1] = y[i] + 1.0/6.0*(k1y + 2.0*k2y + 2.0*k3y + k4y)*dt;
		vx[i+1] = vx[i] + 1.0/6.0*(k1vx + 2.0*k2vx + 2.0*k3vx + k4vx)*dt;
		vy[i+1] = vy[i] + 1.0/6.0*(k1vy + 2.0*k2vy + 2.0*k3vy + k4vy)*dt;

		if (y[i+1]<0  && i>1 )
		{
			
			cout << "\nTraveled Distance along x axes = " << x[i+1] << "\n";
			lastIt = i;
			cout << "Total iterations = " << lastIt << "\n";
			break;
		}

		
		cout << i << "," << k1vx*dt << "," << k2vx*dt << "," << k3vx*dt << "," << k4vx*dt << "\n";
	}


	if (lastIt==0)
	{
		cout << "\nTraveled Distance along x axes = " << x[nt-1] << "\n";
		lastIt = nt;
		cout << "Total iterations = " << lastIt << "\n";
	}

	cout << "Programa Finalizado\n";
	cout << vx[0] << "\n" << vy[0] << "\n";

	return 0;
}
