#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdio"

using namespace std;


void varios_angulos();

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

	int lastIt=0;

	for (int i = 0; i < nt-1; ++i)
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
			
			cout << "\nDezplazamiento en eje x = " << x[i+1] << "\n";
			lastIt = i;
			cout << "Total iteraciones= " << lastIt << "\n";
			break;
		}

		
		//cout << i << "," << k1vx*dt << "," << k2vx*dt << "," << k3vx*dt << "," << k4vx*dt << "\n";
	}


	if (lastIt==0)
	{
		cout << "\nDezplazamiento en eje x = " << x[nt-1] << "\n";
		lastIt = nt;
		cout << "Total iteraciones = " << lastIt << "\n";
	}

	cout << "Programa Finalizado\n";
	//cout << vx[0] << "\n" << vy[0] << "\n";
	cout<<"         "<<endl;
	cout<<"Ahora para varios angulos"<<endl;


	varios_angulos();

	return 0;
}



void varios_angulos()
{

	float g=-10.0; 
	float c=0.2; 
	float m=0.2; 
	float v0mag = 300.0; 
	float alpha[7];


	for (int a = 0; a < 7; ++a)
	{
		alpha[a] = ((a+1)*10.0)/180.0*M_PI; 
	}


	float dt = 0.001; 
	int nt = 2000; 



	float x[nt][7];
	float y[nt][7];
	float vx[nt][7];
	float vy[nt][7];



	for (int a = 0; a < 7; ++a)
	{
		x[0][a] = 0.0;
		y[0][a] = 0.0;
		vx[0][a] = v0mag*cos(alpha[a]);
		vy[0][a] = v0mag*sin(alpha[a]);
	}



	
	float k1x, k1y, k1vx, k1vy;
	float k2x, k2y, k2vx, k2vy;
	float k3x, k3y, k3vx, k3vy;
	float k4x, k4y, k4vx, k4vy;


	ofstream projectile("projectile_7alpha.csv");


	float distancia_recorrida[7];
	for (int a = 0; a < 7; ++a)
		{
			distancia_recorrida[a]=0.0;
		}

	int angulo_maxDist=2;

	
	int lastIt=0;

	for (int i = 0; i < nt-1; ++i)
	{
		for (int a = 0; a < 7; ++a)
		{

			projectile << x[i][a] << "," << y[i][a] << "," << vx[i][a] << "," << vy[i][a] << "," ;

			
			k1x = vx[i][a];
			k1y = vy[i][a];
			k1vx = -c/m*pow( pow(vx[i][a],2) + pow(vy[i][a],2) , 0.5)*vx[i][a];
			k1vy = g -c/m*pow( pow(vx[i][a],2) + pow(vy[i][a],2) , 0.5)*vy[i][a];

			k2x = vx[i][a] + 0.5*dt*k1vx;
			k2y = vy[i][a] + 0.5*dt*k1vy;
			k2vx = -c/m*pow( pow(vx[i][a]+0.5*dt*k1vx,2) + pow(vy[i][a]+0.5*dt*k1vy,2) , 0.5) * (vx[i][a]+0.5*dt*k1vx);
			k2vy = g -c/m*pow( pow(vx[i][a]+0.5*dt*k1vx,2) + pow(vy[i][a]+0.5*dt*k1vy,2) , 0.5) * (vy[i][a]+0.5*dt*k1vy);		

			k3x = vx[i][a] + 0.5*dt*k2vx;
			k3y = vy[i][a] + 0.5*dt*k2vy;
			k3vx = -c/m*pow( pow(vx[i][a]+0.5*dt*k2vx,2) + pow(vy[i][a]+0.5*dt*k2vy,2) , 0.5) * (vx[i][a]+0.5*dt*k2vx);
			k3vy = g -c/m*pow( pow(vx[i][a]+0.5*dt*k2vx,2) + pow(vy[i][a]+0.5*dt*k2vy,2) , 0.5) * (vy[i][a]+0.5*dt*k2vy);		

			k4x = vx[i][a] + 1.0*dt*k3vx;
			k4y = vy[i][a] + 1.0*dt*k3vy;
			k4vx = -c/m*pow( pow(vx[i][a]+1.0*dt*k3vx,2) + pow(vy[i][a]+1.0*dt*k3vy,2) , 0.5) * (vx[i][a]+1.0*dt*k3vx);
			k4vy = g -c/m*pow( pow(vx[i][a]+1.0*dt*k3vx,2) + pow(vy[i][a]+1.0*dt*k3vy,2) , 0.5) * (vy[i][a]+1.0*dt*k3vy);		
			
			
			x[i+1][a] = x[i][a] + 1.0/6.0*(k1x + 2.0*k2x + 2.0*k3x + k4x)*dt;
			y[i+1][a] = y[i][a] + 1.0/6.0*(k1y + 2.0*k2y + 2.0*k3y + k4y)*dt;
			vx[i+1][a] = vx[i][a] + 1.0/6.0*(k1vx + 2.0*k2vx + 2.0*k3vx + k4vx)*dt;
			vy[i+1][a] = vy[i][a] + 1.0/6.0*(k1vy + 2.0*k2vy + 2.0*k3vy + k4vy)*dt;

			if (y[i+1][a]<0  && i>1 && distancia_recorrida[a]==0.0)
			{
				// LLego al piso la bola
				// cout << "\nDezplazamiento en x = " << x[i+1] << "\n";
				// lastIt = i;
				// cout << "Total iterations = " << lastIt << "\n";
				// break;
				distancia_recorrida[a] = x[i+1][a];

				cout << a << "  " << distancia_recorrida[a] << "\n";

				if ( x[i+1][a] > distancia_recorrida[angulo_maxDist] )
				{
					angulo_maxDist = a; // encontrar angulo de maxima distancia
				}
			}
		}
		projectile << "\n";
		
		//cout << i << "," << k1vx*dt << "," << k2vx*dt << "," << k3vx*dt << "," << k4vx*dt << "\n";
	}


	cout << "\n\nAngulo de mayor distancia es " << alpha[angulo_maxDist]/M_PI*180 << "\n\n";

	cout << "Programa Finalizado\n";
	//cout << vx[0] << "\n" << vy[0] << "\n";

}
