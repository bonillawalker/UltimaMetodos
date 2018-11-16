#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdio"

using namespace std;


// Constantes del problema --------------------------------------
	float g=-10.0; 
	float c=0.2; 
	float m=0.2; 

	float v0mag = 300.0; 
	float alpha0= 45.0;

	// tiempo!!
	float dt = 0.001; 
	int nt = 2000;

int main(){


	float x[nt];
	float y[nt];
	float vx[nt];
	float vy[nt];


	x[0] = 0.0;
	y[0] = 0.0;
	vx[0] = v0mag*cos(alpha0/180*M_PI);
	vy[0] = v0mag*sin(alpha0/180*M_PI);
	




	x[0] = 0.0;
	y[0] = 0.0;
	vx[0] = v0mag*cos(alpha0/180*M_PI);
	vy[0] = v0mag*sin(alpha0/180*M_PI);


	float k1x, k1y, k1vx, k1vy;
	float k2x, k2y, k2vx, k2vy;
	float k3x, k3y, k3vx, k3vy;
	float k4x, k4y, k4vx, k4vy;


	ofstream projectile("projectile.csv");




	return 0;
}
