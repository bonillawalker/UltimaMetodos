#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdio"

using namespace std;

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


int main(){

	return 0;
}

