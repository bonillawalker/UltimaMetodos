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



	return 0;
}
