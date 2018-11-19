#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdio"

using namespace std;



//Decidi hacer Runge-Kutta porque asi sea muy largo esta muy bien explicado en el repositorio y es mucho mas facil guiarme asi


void varios_angulos();                           //Declaro el tipo de funcion que voy a hacer mas adelante para la segunda parte

int main(int argc, char const *argv[])
{
	cout << "\n\n\nIniciando programa ODE:\n";    //Mandeme un mensajito para ver bien donde arranca mi programa
	//Declaro todas las constantes para mi problema --------------------------------------
	float g=-10.0;                       //Gravedad	
	float c=0.2;                         //Coeficiente de friccion
	float m=0.2;                         //Masa de la particula

	float v0mag = 300.0; 	             //Velocidad inicial	
	float alpha0= 45.0; 		     //Angulo inicial con el que arranco


	//Para manejar el tiempo se necesita fijar:
	float dt = 0.001;                     //Cada cuanto va a mirar
	int nt = 2000; 			      //Cuantas veces va a mirar


	//Creo los arreglos donde voy a guardar todas mis variables de interes(x,y,vx,vy) -----------------
	float x[nt];
	float y[nt];					//Todos tienen que tener el tamaño necesario para guardar en todos los tiempos
	float vx[nt];
	float vy[nt];


	//Ahora le pongo todos los datos con los que inicia la particula ---------------------------------------------
	x[0] = 0.0;
	y[0] = 0.0;					//Todos los datos vienen dados en la guia
	vx[0] = v0mag*cos(alpha0/180*M_PI);		//Para las dos velocidades me di cuenta que c++ hace el coseno en radianes, entonces toca pasar los angulos a Radianes
	vy[0] = v0mag*sin(alpha0/180*M_PI);		//Encontre que M_PI es Pi en c++

	//Ahora si aplico el metodo de RungeKutta4 -----------------------------------------------
	
	//Inicializar todas las variables k para guardar mis datos
	float k1x, k1y, k1vx, k1vy;
	float k2x, k2y, k2vx, k2vy;
	float k3x, k3y, k3vx, k3vy;
	float k4x, k4y, k4vx, k4vy;

	//Creo un archivo projectile para poder mandar todos mis datos de posicion y velocidad en funcion del tiempo
	ofstream projectile("projectile.csv");

	int NumeroIt=0;				//Inicio la variable del numero de iteraciones totales en 0

	for (int i = 0; i < nt-1; ++i)
	{

		projectile << i*dt << "," << x[i] << "," << y[i] << "," << vx[i] << "," << vy[i] << "\n";  //Mandeme a mi archivo el tiempo en el que va, la posicion x,y y la velocidad x,y

		//Apliqueme RK4. Para cada k toca sacar todas las cuatro variables
		k1x = vx[i];
		k1y = vy[i];
		k1vx = -c/m*pow( pow(vx[i],2) + pow(vy[i],2) , 0.5)*vx[i];
		k1vy = g -c/m*pow( pow(vx[i],2) + pow(vy[i],2) , 0.5)*vy[i];

		k2x = vx[i] + 0.5*dt*k1vx;
		k2y = vy[i] + 0.5*dt*k1vy;
		k2vx = -c/m*pow( pow(vx[i]+0.5*dt*k1vx,2) + pow(vy[i]+0.5*dt*k1vy,2) , 0.5) * (vx[i]+0.5*dt*k1vx);
		k2vy = g -c/m*pow( pow(vx[i]+0.5*dt*k1vx,2) + pow(vy[i]+0.5*dt*k1vy,2) , 0.5) * (vy[i]+0.5*dt*k1vy);		

		k3x = vx[i] + 0.5*dt*k2vx;								//En toda esta seccion, me guie por el archivo del repositorio para darle el valor a cada K
		k3y = vy[i] + 0.5*dt*k2vy;
		k3vx = -c/m*pow( pow(vx[i]+0.5*dt*k2vx,2) + pow(vy[i]+0.5*dt*k2vy,2) , 0.5) * (vx[i]+0.5*dt*k2vx);
		k3vy = g -c/m*pow( pow(vx[i]+0.5*dt*k2vx,2) + pow(vy[i]+0.5*dt*k2vy,2) , 0.5) * (vy[i]+0.5*dt*k2vy);		

		k4x = vx[i] + 1.0*dt*k3vx;
		k4y = vy[i] + 1.0*dt*k3vy;
		k4vx = -c/m*pow( pow(vx[i]+1.0*dt*k3vx,2) + pow(vy[i]+1.0*dt*k3vy,2) , 0.5) * (vx[i]+1.0*dt*k3vx);
		k4vy = g -c/m*pow( pow(vx[i]+1.0*dt*k3vx,2) + pow(vy[i]+1.0*dt*k3vy,2) , 0.5) * (vy[i]+1.0*dt*k3vy);		
		
		
		//Por el repositorio se que la pendiente es (1/6)*(k1+2k2+2k3+k4)

		//Ahora multipliqueme en el valor en el que esta por la pendiente, y de esta manera conseguira el valor en la siguiente posicion.
		x[i+1] = x[i] + 1.0/6.0*(k1x + 2.0*k2x + 2.0*k3x + k4x)*dt;
		y[i+1] = y[i] + 1.0/6.0*(k1y + 2.0*k2y + 2.0*k3y + k4y)*dt;
		vx[i+1] = vx[i] + 1.0/6.0*(k1vx + 2.0*k2vx + 2.0*k3vx + k4vx)*dt;
		vy[i+1] = vy[i] + 1.0/6.0*(k1vy + 2.0*k2vy + 2.0*k3vy + k4vy)*dt;

		if (y[i+1]<0  && i>1 )			//Necesito que me busque donde toca la particula el suelo otra vez!! Obviamente que no sea el punto inicial
		{
			
			cout << "\nDezplazamiento en eje x = " << x[i+1] << "\n"; //Cuando consiga el punto, digame en que x esta parado
			NumeroIt = i;						  //Guardeme en que indice es
			cout << "Total iteraciones= " << NumeroIt << "\n";	  //Usando ese indice, digame cuantas veces tuvo que hacer el recorrido
			break;
		}

		
		//cout << i << "," << k1vx*dt << "," << k2vx*dt << "," << k3vx*dt << "," << k4vx*dt << "\n";
	}


	if (NumeroIt==0)	//Si el numero de iteraciones es cero, necesito saber cual es el dezplazamiento en x asi no toque el piso
	{
		cout << "\nDezplazamiento en eje x = " << x[nt-1] << "\n";
		NumeroIt = nt;							//Recorre todos los datos y nunca llego al cero
		cout << "Total iteraciones = " << NumeroIt << "\n";
	}

	//cout << vx[0] << "\n" << vy[0] << "\n";
	cout<<"         "<<endl;
	cout<<"Ahora para varios angulos:"<<endl;


	varios_angulos();  //Para que el main me corra mi funcion para la segunda parte, la llamo desde aca!!

	return 0;
}


//Quiero crear mi funcion que me va a encontrar cual es el angulo en el que la particula reccore mayor distancia en el ejex!!

void varios_angulos()
{
	//Vuelvo a inicar todas mis variables para que sean usadas dentro de mi funcion, ya que las cree en el main
	float g=-10.0; 		//Gravedad	
	float c=0.2; 		//Coeficiente de friccion	
	float m=0.2; 		//Masa de la particula
	float v0mag = 300.0;    //Velocidad inicial
	float alpha[7];		//Angulo iniciales que se van a probar



	//Para que me calcule facil el angulo:
	for (int a = 0; a < 7; ++a)                  //Son 7 angulos
	{
		alpha[a] = ((a+1)*10.0)/180.0*M_PI;  //El angulo sera el indice multiplicado por diez y para pasarlo a radianes lo vuelvo a dividir entre 180*pi
	}					     //Aqui ya tengo mi arreglo con mis angulos a probar

	//Para manejar el tiempo se necesita fijar otra vez:
	float dt = 0.001;                     //Cada cuanto va a mirar
	int nt = 2000; 			      //Cuantas veces va a mirar


	//Creo los arreglos donde voy a guardar todas mis variables de interes(x,y,vx,vy) . Cada arreglo va a tener 7 celdas para guardar cada valor para cada angulo-----------------
	float x[nt][7];
	float y[nt][7];
	float vx[nt][7];
	float vy[nt][7];


	//Ahora le pongo todos los datos con los que inicia la particula ---------------------------------------------
	for (int a = 0; a < 7; ++a)
	{
		x[0][a] = 0.0;
		y[0][a] = 0.0;
		vx[0][a] = v0mag*cos(alpha[a]);					//Aqui ya el angulo esta en radianes entonces no hay que hacer lo de arriba
		vy[0][a] = v0mag*sin(alpha[a]);
	}



        //Inicializar todas las variables k para guardar mis datos	
	float k1x, k1y, k1vx, k1vy;
	float k2x, k2y, k2vx, k2vy;
	float k3x, k3y, k3vx, k3vy;
	float k4x, k4y, k4vx, k4vy;

	//Creo un archivo projectile_7alpha para poder mandar todos mis datos de posicion y velocidad en funcion del tiempo, para cada angulo!!!
	ofstream projectile("projectile_7alpha.csv");


	float distancia_recorrida[7];   //Creeme un arreglo de siete celdas para poder guardar las distancias que se recorren para cada angulo


	//Inicieme todo ese arreglo con ceros
	for (int a = 0; a < 7; ++a)
		{
			distancia_recorrida[a]=0.0;
		}

	int angulo_maxDist=2; //Creo esta variable para guardar al final el mayor angulo. Le doy el valor2, pero puede ser cualquiera.

	
	int NumeroIt=0;	      //Inicio la variable del numero de iteraciones totales en 0





	//Solucion para todos los angulos------------------------------

	//Primero hagame el mismo runge kutta de arriba

	for (int i = 0; i < nt-1; ++i)
	{
		for (int a = 0; a < 7; ++a)
		{

			projectile << x[i][a] << "," << y[i][a] << "," << vx[i][a] << "," << vy[i][a] << "," ;  //Mandeme a mi archivo el tiempo en el que va, la posicion x,y y la velocidad x,y

			//Apliqueme RK4. Para cada k toca sacar todas las cuatro variables
			k1x = vx[i][a];
			k1y = vy[i][a];
			k1vx = -c/m*pow( pow(vx[i][a],2) + pow(vy[i][a],2) , 0.5)*vx[i][a];
			k1vy = g -c/m*pow( pow(vx[i][a],2) + pow(vy[i][a],2) , 0.5)*vy[i][a];

			k2x = vx[i][a] + 0.5*dt*k1vx;
			k2y = vy[i][a] + 0.5*dt*k1vy;
			k2vx = -c/m*pow( pow(vx[i][a]+0.5*dt*k1vx,2) + pow(vy[i][a]+0.5*dt*k1vy,2) , 0.5) * (vx[i][a]+0.5*dt*k1vx);
			k2vy = g -c/m*pow( pow(vx[i][a]+0.5*dt*k1vx,2) + pow(vy[i][a]+0.5*dt*k1vy,2) , 0.5) * (vy[i][a]+0.5*dt*k1vy);		

			k3x = vx[i][a] + 0.5*dt*k2vx; 								//En toda esta seccion, me guie por el archivo del repositorio para darle el valor a cada K
			k3y = vy[i][a] + 0.5*dt*k2vy;                                                         
			k3vx = -c/m*pow( pow(vx[i][a]+0.5*dt*k2vx,2) + pow(vy[i][a]+0.5*dt*k2vy,2) , 0.5) * (vx[i][a]+0.5*dt*k2vx);
			k3vy = g -c/m*pow( pow(vx[i][a]+0.5*dt*k2vx,2) + pow(vy[i][a]+0.5*dt*k2vy,2) , 0.5) * (vy[i][a]+0.5*dt*k2vy);		

			k4x = vx[i][a] + 1.0*dt*k3vx;
			k4y = vy[i][a] + 1.0*dt*k3vy;
			k4vx = -c/m*pow( pow(vx[i][a]+1.0*dt*k3vx,2) + pow(vy[i][a]+1.0*dt*k3vy,2) , 0.5) * (vx[i][a]+1.0*dt*k3vx);
			k4vy = g -c/m*pow( pow(vx[i][a]+1.0*dt*k3vx,2) + pow(vy[i][a]+1.0*dt*k3vy,2) , 0.5) * (vy[i][a]+1.0*dt*k3vy);		
		
		        //Por el repositorio se que la pendiente es (1/6)*(k1+2k2+2k3+k4)

		        //Ahora multipliqueme en el valor en el que esta por la pendiente, y de esta manera conseguira el valor en la siguiente posicion.			
			
			x[i+1][a] = x[i][a] + 1.0/6.0*(k1x + 2.0*k2x + 2.0*k3x + k4x)*dt;
			y[i+1][a] = y[i][a] + 1.0/6.0*(k1y + 2.0*k2y + 2.0*k3y + k4y)*dt;
			vx[i+1][a] = vx[i][a] + 1.0/6.0*(k1vx + 2.0*k2vx + 2.0*k3vx + k4vx)*dt;
			vy[i+1][a] = vy[i][a] + 1.0/6.0*(k1vy + 2.0*k2vy + 2.0*k3vy + k4vy)*dt;



			//Ahora toca realizar la comparacion para encontrar el angulo para el que mayor distancia recorrio la particula

			if (y[i+1][a]<0  && i>1 && distancia_recorrida[a]==0.0) //Necesito que me busque donde toca la particula el suelo otra vez!! Obviamente que no sea el punto inicial
			{
				
				//La idea es que cuando encuentre el punto, me saque la distancia en la que esta en x
				distancia_recorrida[a] = x[i+1][a];

				if ( x[i+1][a] > distancia_recorrida[angulo_maxDist] )  //Si para el angulo donde esta, la distancia es mayor que la anterior
				{
					angulo_maxDist = a;                            //Vuelvame mi variable creada, el valor de la poscion en la que esta el mayor angulo
				}
			}
		}
		projectile << "\n";
		
		//cout << i << "," << k1vx*dt << "," << k2vx*dt << "," << k3vx*dt << "," << k4vx*dt << "\n";
	}


	cout << "\n\nAngulo de mayor distancia en x es: " << alpha[angulo_maxDist]/M_PI*180 << "\n\n";    //Por ultimo, deme ese angulo que esta en el arreglo de angulos en la posicion encontrada
	cout << "Programa Ode Finalizado y resultados hechos\n";
	cout<<"         "<<endl;
	//cout << vx[0] << "\n" << vy[0] << "\n";

}

//Final completo, Funciona!!
