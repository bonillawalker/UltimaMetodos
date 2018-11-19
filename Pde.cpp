#include "iostream"
#include "fstream"
#include "cmath"
#include "cstdio"

using namespace std;



int main(int argc, char const *argv[])
{
	cout << "\n\n\nIniciando programa PDE:\n";    //Mandeme un mensajito para ver bien donde arranca mi programa

	//Creo las variables de mi roca
	float conductivity=1.62;                     // m^2/s
	float Cp=820;                                // J/(kg*K)
	float rho=2.71;                              // g/cm^3 
	float rho_si=rho/1000*1000000;               // Toca pasarlo a kg/m^3 porque si no todo me sale mal


	//Creo las variables para mi varilla
	float Trod = 100;                            // Temperatura de la varilla [°c]
	float Drod = 0.1;                            // Diametro de la varilla [m]


	// Inicio los otros datos -------------------------------------------------------
	float L=0.5;                                 // Extension de mis datos
	int nx=64;                                   // Numero de puntos
	float dx=L/(nx-1);                           // Cada cuanto aparece un punto, como voy avanzando

	//Creo mis arreglos para ir guardando todas las temperaturas (Pasado, Presente, Futuro)
	float Tpresent[nx][nx];			//Arreglo Tpresente de ese tamaño
	float Tfuture[nx][nx];			//Arreglo Tfuturo de ese tamaño

	float Tpresent1[nx][nx];                //Condicion de frontera para mi primer punto de arranque
	float Tfuture1[nx][nx];			////Arreglo Tfuturo1 de ese tamaño

	float Tpresent2[nx][nx];                // Condicion periodica para mi frontera
	float Tfuture2[nx][nx];			//Areglo Tfuturo2 de ese tamaño
	int rock_int[nx][nx];			//Arreglo para guardar T para roca
	//Despues de crear todos estas variables se supone que ya tengo donde guardar todos los datos que necesito!!
	
	

	//Creo un ciclo para poder darle los valores iniciales a mis arreglos previamente creados!!

	for (int i = 0; i < nx; ++i)		//Para moverme en X
	{
		for (int j = 0; j < nx; ++j)    //Para moverme en Y
		{
			if (pow((i-nx/2)*dx,2) + pow((j-nx/2)*dx,2) < pow(Drod/2,2)) //Pow es una funcion que recibe una base y un exponente y devuelve la base elevada a la exponente(en este caso2)!	
			{ // Arranco con los datos para la varilla
				Tpresent[i][j] = Trod;
				Tfuture[i][j] = Trod;
				
				Tpresent1[i][j] = Trod;			//Todo va a estar a la misma temperatura excepto mi roca, y va a ser la temperatura inicial de mi varilla!!!
				Tfuture1[i][j] = Trod;
				
				Tpresent2[i][j] = Trod;
				Tfuture2[i][j] = Trod;

				rock_int[i][j] = 0;			//En este caso mi roca deberia ser 0!
			}else
			{ // Ahora lo hago para mi roca
				Tpresent[i][j] = 10.0;			
				Tfuture[i][j] = 10.0;

				Tpresent1[i][j] = 10.0;
				Tfuture1[i][j] = 10.0;			//Todo va a estar a 10 grados ya que es la temperatura de mi calcita!!!!

				Tpresent2[i][j] = 10.0;
				Tfuture2[i][j] = 10.0;

				rock_int[i][j] = 1;			//En este caso mi roca deberia ser 1!
			}
		}
	}


	// Ahora si o si toca arreglar los puntos de las fronteras -----------------------------------------------------
	
	for (int i = 0; i < nx; ++i)				 //Recorrame todo mi arreglo en X
	{
		for (int j = 0; j < nx; ++j){ 			 //Recorrame todo mi arreglo en Y
			if (i==0 || j==0 || i==nx-1 || j==nx-1)  //Para mis primeros y ultimos puntos:
			{					 // T frontera = 10 
				Tpresent[i][j] = 10;		 // T =10
				Tfuture[i][j] = 10;		 // T =10
				rock_int[i][j] = 0;              // Roca si tiene que ser = 0
			}
		}
	}


	// Y ahora tiene que encontrarme la solucion--------------------------------------------------------------------
	//Acuerdese que siempre se mueve en tiempo y posicion!!!

	float nu=conductivity/(Cp*rho_si);
	float C=0.1;
	float dt=C*dx*dx/nu;

	
	int nt=5000;
	float tf=dt*nt;

	//Quiero crear un archivo diferente para cada caso! Escogi tipo de archivo csv
	ofstream rock("rock.csv");				//Caso1:Mandeme los datos a un archivo .csv para despues plotearlos
	ofstream rock1("rock1.csv");				//Caso2:Mandeme los datos a un archivo .csv para despues plotearlos
	ofstream rock2("rock2.csv");				//Caso3:Mandeme los datos a un archivo .csv para despues plotearlos



	//Aqui arranco a plantear su solucion!
	//Aranco mi ciclo
	for ( int k = 0; k < nt; ++k)
	{// Arranco mi ciclo para el tiempo!
		for (int i = 0; i < nx; ++i)
		{
			for (int j = 0; j < nx; ++j)
			{
				if (rock_int[i][j]==1)                                    //Si mi dato de roca efectivamente es uno, por la inializacion de arriba:
				{                                                         //Apliquele  la roca este cambio:

					//Esto se obtiene al derivar la funcion dada en la guia, como lo hicimos en la clase y sale en el libro
					
					Tfuture[i][j] = C*(Tpresent[i-1][j] + Tpresent[i+1][j] + Tpresent[i][j-1] + Tpresent[i][j+1] - 4*Tpresent[i][j]) + Tpresent[i][j];

					Tfuture1[i][j] = C*(Tpresent1[i-1][j] + Tpresent1[i+1][j] + Tpresent1[i][j-1] + Tpresent1[i][j+1] - 4*Tpresent1[i][j]) + Tpresent1[i][j];

					Tfuture2[i][j] = C*(Tpresent2[i-1][j] + Tpresent2[i+1][j] + Tpresent2[i][j-1] + Tpresent2[i][j+1] - 4*Tpresent2[i][j]) + Tpresent2[i][j];
				}
			}

		}



		// Para las fronteras abiertas:
		for (int i = 0; i < nx; ++i)
		{
			Tfuture1[0][i] = Tfuture1[1][i];
			Tfuture1[nx-1][i] = Tfuture1[nx-2][i];

			Tfuture1[i][0] = Tfuture1[i][1];
			Tfuture1[i][nx-1] = Tfuture1[i][nx-2];
		}


		// Para las fronteras periodicas:
		for (int i = 1; i < nx-1; ++i)
		{
			Tfuture2[0][i] = C*(Tpresent2[nx-1][i] + Tpresent2[1][i] + Tpresent2[0][i-1] + Tpresent2[0][i+1] - 4*Tpresent2[0][i]) + Tpresent2[0][i];
			Tfuture2[nx-1][i] = C*(Tpresent2[nx-2][i] + Tpresent2[0][i] + Tpresent2[nx-1][i-1] + Tpresent2[nx-1][i+1] - 4*Tpresent2[nx-1][i]) + Tpresent2[nx-1][i];


			Tfuture2[i][0] = C*(Tpresent2[i][nx-1] + Tpresent2[i][1] + Tpresent2[i-1][0] + Tpresent2[i+1][0] - 4*Tpresent2[i][0]) + Tpresent2[i][0];
			Tfuture2[i][nx-1] = C*(Tpresent2[i][nx-2] + Tpresent2[i][0] + Tpresent2[i-1][nx-1] + Tpresent2[i+1][nx-1] - 4*Tpresent2[i][nx-1]) + Tpresent2[i][nx-1];
		}		
		

		//Aqui me di cuenta que las esquinas siempre van a ser un problema, entonces toca hacerlo especifico para estas!!
		//Para mis esquinas:

		Tfuture2[0][0] = C*(Tpresent2[nx-1][0] + Tpresent2[1][0] + Tpresent2[0][nx-1] + Tpresent2[0][1] - 4*Tpresent2[0][0]) + Tpresent2[0][0];
		Tfuture2[0][nx-1] = C*(Tpresent2[nx-1][nx-1] + Tpresent2[1][nx-1] + Tpresent2[0][nx-2] + Tpresent2[0][0] - 4*Tpresent2[0][nx-1]) + Tpresent2[0][nx-1];

		Tfuture2[nx-1][0] = C*(Tpresent2[nx-1][nx-1] + Tpresent2[nx-1][1] + Tpresent2[nx-2][0] + Tpresent2[0][0] - 4*Tpresent2[nx-1][0]) + Tpresent2[nx-1][0];
		Tfuture2[nx-1][nx-1] = C*(Tpresent2[nx-1][nx-2] + Tpresent2[nx-1][0] + Tpresent2[nx-2][nx-1] + Tpresent2[0][nx-1] - 4*Tpresent2[nx-1][nx-1]) + Tpresent2[nx-1][nx-1];



		//Actualizeme los nuevos valores para poder volver a arrancar en el siguiente tiempo
		for (int i = 0; i < nx; ++i)
		{
			for ( int j = 0; j < nx; ++j)
			{
			
				Tpresent[i][j] = Tfuture[i][j];
				Tpresent1[i][j] = Tfuture1[i][j];
				Tpresent2[i][j] = Tfuture2[i][j];
			

			}
		}

		// Mandeme ya mis datos a mis archivos!!!
		for (int i = 0; i < nx; ++i)
		{
			for (int j = 0; j < nx; ++j)
			{
				rock << Tpresent[i][j] << ",";
				rock1 << Tpresent1[i][j] << ",";
				rock2 << Tpresent2[i][j] << ",";
			}
		}
		rock << "\n";  
		rock1 << "\n";
		rock2 << "\n";


	}


	
	ofstream tiempo("tiempo.csv");
	tiempo << "Tiempo final [s] \n";			//Mandeme este mensaje para que se vea bonito
	tiempo << tf << endl;					//Imprima el tiempo final del proceso de difusion en el archivo de tiempo en la carpeta
	cout<<"   "<<endl;					//Imprima vacio para que no se vea pegado
	cout <<"Al correr el programa y observar los archivos produciods, se puede ver claramente donde hay cambio de T"<<endl;	
	cout << "Programa de Pde Finalizado\n\n\n";		//Muestreme que Pde se cabo porque si no, con el mkae uno no sabe que es que
	return 0;
}
