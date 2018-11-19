import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys


#Se supone que este programa deberia hacer todas las graficas que se pueden hacer a partir de los archivos de datos que cree en Pde y Ode
#Este archivo sirve cuando se corre en el make porque asi solo no tendra los archivos para graficar. Por eso el make me produce mis archivos.

#Parte de Odes


if (sys.argv[1]=='ODE'):					#Para el archivo de Ode (Lo encuentro mirando los argumentos que se le pasan a este programa)
	print("\n"*4, "Graficas ODE")				#Mensaje para ver donde comienza mi proceso de graficacion de ODE


	#Arranco haciendo la grafica de la trayectoria de la del angulo de 45
	projectile = np.genfromtxt("projectile.csv", delimiter=',') #Leame el archivo de projectile
	plt.figure()						#Creo mi figura
	plt.plot(projectile[:,1], projectile[:,2])		#Grafiqueme la primera columna vs la segunda
	plt.xlabel('x')						#Asigne el eje x
	plt.ylabel('y')						#Asigne el eje y
	plt.savefig('projectile45.png')				#Guardeme la grafica con este nombre y este formato para poder ponerlo en el latex


	projectiles = np.genfromtxt("projectile_7alpha.csv", delimiter=",")  #Leame el archivo de projectile_7alpha
	x = projectiles[:,0:-1:4]					     #Cojame los x
	y = projectiles[:,1:-1:4]					     #Cojame mis Y


	plt.figure()							     #Creeme mi figura
	plt.plot(x,y)							     #Grafique x vs y
	plt.xlabel('x')
	plt.ylabel('y')
	plt.ylim( [0,np.max(np.max(y))] )				     #Defino el limite en y
	plt.legend(["10","20","30","40", "50","60","70"])		     #Pongale la leyenda para cada angulo
	plt.savefig('projectiles7angulos.png')		                     #Guardeme la grafica con este nombre y este formato para poder ponerlo en el latex


##########################################################
##########################################################
##########################################################
##########################################################
##########################################################
#Parte de Pdes

if (sys.argv[1]=='PDE'):						     #Para el archivo de Ode (Lo encuentro mirando los argumentos que se le pasan a este programa)
	print("\n"*4, "Graficas PDE")					     #Mensaje para ver donde comienza mi proceso de graficacion

	#Condiciones de fronteras fijas!!
	rock_data = np.genfromtxt('rock.csv', delimiter=',')		    #Leame el archivo de rock
	rock_data = rock_data[:,:-1]                                        #Hay que quitar la ultima columna
	n2 = np.size(rock_data[0,:])                                        #Este sera el tamano del archivo en eje 1
	n = int(n2**0.5)						    #Tamano los otros ejes

	
	X,Y = np.meshgrid(np.linspace(0,50,n), np.linspace(0,50,n))         #Hay que crear la grilla 3D para poder graficar los datos(Lo vi en internet)


	#print(np.shape(rock_data))
	pasos = np.size(rock_data,0)					    #Este sera el numero de puntos a graficar

	intermedio1 = int(0.3*pasos);
	intermedio2 = int(0.6*pasos);


	rock0 = np.reshape(rock_data[0,:], (n,n))
	rock_intermedio1 = np.reshape(rock_data[intermedio1,:], (n,n))
	rock_intermedio2 = np.reshape(rock_data[intermedio2,:], (n,n))
	rockf = np.reshape(rock_data[-1,:], (n,n))
	rockm0 = np.mean(rock_data, 1)

	#Saco de internet que este es el metodo para poder graficar todo

	fig = plt.figure()					#Me crea la figura
	ax = fig.gca(projection='3d')				#Le digo que tiene que ser en 3d
	surf = ax.plot_surface(X,Y,rock0, cmap="inferno")       #Pongame la figura con mis X,Y y mis datos obtenidos en PDE con color inferno		
	ax.set_zlim([0,100])					#Ajusta los ejes
	#fig.colorbar()						#Pongame el colorbar
	fig.savefig('rock0.png')				#Guardeme la figura con este nombre y en ese formato para poder ponerlo en el Latex			


	fig = plt.figure()					#Me crea la figura
	ax = fig.gca(projection='3d')				#Le digo que tiene que ser en 3d
	surf = ax.plot_surface(X,Y,rockf, cmap="inferno")	#Pongame la figura con mis X,Y y mis datos obtenidos en PDE con color inferno
	ax.set_zlim([0,100])					#Ajusta los ejes
	#fig.colorbar()						#Pongame el colorbar
	fig.savefig('rockf.png')				#Guardeme la figura con este nombre y en ese formato para poder ponerlo en el Latex		

	fig = plt.figure()					#Me crea la figura
	ax = fig.gca(projection='3d')				#Le digo que tiene que ser en 3d
	surf = ax.plot_surface(X,Y,rock_intermedio1, cmap="inferno")#Pongame la figura con mis X,Y y mis datos obtenidos en PDE con color inferno
	ax.set_zlim([0,100])					#Ajusta los ejes
	#fig.colorbar()						#Pongame el colorbar
	fig.savefig('rock1.png')				#Guardeme la figura con este nombre y en ese formato para poder ponerlo en el Latex		

	fig = plt.figure()					#Me crea la figura
	ax = fig.gca(projection='3d')				#Le digo que tiene que ser en 3d
	surf = ax.plot_surface(X,Y,rock_intermedio2, cmap="inferno")#Pongame la figura con mis X,Y y mis datos obtenidos en PDE con color inferno
	ax.set_zlim([0,100])					#Ajusta los ejes
	#fig.colorbar()						#Pongame el colorbar
	fig.savefig('rock2.png')				#Guardeme la figura con este nombre y en ese formato para poder ponerlo en el Latex		
	################################################################


	#Grafica que me plotea condicion de frontera abierta

	rock_data = np.genfromtxt('rock1.csv', delimiter=',')		#Leame el archivo de rock1
	rock_data = rock_data[:,:-1] 					#Hay que quitar la ultima columna
	n2 = np.size(rock_data[0,:]) 					#Este sera el tamano del archivo en eje 1
	n = int(n2**0.5)						#Tamano los otros ejes

	
	X,Y = np.meshgrid(np.linspace(0,50,n), np.linspace(0,50,n))     #Hay que crear la grilla 3D para poder graficar los datos(Lo vi en internet)


	#print(np.shape(rock_data))
	pasos = np.size(rock_data,0)					#Este sera el numero de puntos a graficar

	intermedio1 = int(0.3*pasos);
	intermedio2 = int(0.6*pasos);


	rock0 = np.reshape(rock_data[0,:], (n,n))
	rock_intermedio1 = np.reshape(rock_data[intermedio1,:], (n,n))
	rock_intermedio2 = np.reshape(rock_data[intermedio2,:], (n,n))
	rockf = np.reshape(rock_data[-1,:], (n,n))
	rockm1 = np.mean(rock_data, 1)




	fig = plt.figure()						#Me crea la figura
	ax = fig.gca(projection='3d')					#Le digo que tiene que ser en 3d
	surf = ax.plot_surface(X,Y,rock0, cmap="inferno")		#Pongame la figura con mis X,Y y mis datos obtenidos en PDE con color inferno
	ax.set_zlim([0,100])						#Ajusta los ejes
	#fig.colorbar()							#Pongame el colorbar
	fig.savefig('rock0_a.png')					#Guardeme la figura con este nombre y en ese formato para poder ponerlo en el Latex

	fig = plt.figure()						#Me crea la figura
	ax = fig.gca(projection='3d')					#Le digo que tiene que ser en 3d
	surf = ax.plot_surface(X,Y,rockf, cmap="inferno")		#Pongame la figura con mis X,Y y mis datos obtenidos en PDE con color inferno
	ax.set_zlim([0,100])						#Ajusta los ejes
	#fig.colorbar()							#Pongame el colorbar
	fig.savefig('rockf_a.png')					#Guardeme la figura con este nombre y en ese formato para poder ponerlo en el Latex

	fig = plt.figure()						#Me crea la figura
	ax = fig.gca(projection='3d')					#Le digo que tiene que ser en 3d
	surf = ax.plot_surface(X,Y,rock_intermedio1, cmap="inferno")	#Pongame la figura con mis X,Y y mis datos obtenidos en PDE con color inferno
	ax.set_zlim([0,100])						#Ajusta los ejes
	#fig.colorbar()							#Pongame el colorbar
	fig.savefig('rock1_a.png')					#Guardeme la figura con este nombre y en ese formato para poder ponerlo en el Latex

	fig = plt.figure()						#Me crea la figura
	ax = fig.gca(projection='3d')					#Le digo que tiene que ser en 3d
	surf = ax.plot_surface(X,Y,rock_intermedio2, cmap="inferno")	#Pongame la figura con mis X,Y y mis datos obtenidos en PDE con color inferno
	ax.set_zlim([0,100])						#Ajusta los ejes
	#fig.colorbar()							#Pongame el colorbar
	fig.savefig('rock2_a.png')					#Guardeme la figura con este nombre y en ese formato para poder ponerlo en el Latex
	################################################################


	#Grafica que me plotea condicion de frontera periodica
	
	rock_data = np.genfromtxt('rock2.csv', delimiter=',')
	rock_data = rock_data[:,:-1] # quitar la ultima columna
	n2 = np.size(rock_data[0,:]) # tamano del archivo en eje 1
	n = int(n2**0.5)

	# crear XY para graficar
	X,Y = np.meshgrid(np.linspace(0,50,n), np.linspace(0,50,n))


	print(np.shape(rock_data))
	pasos = np.size(rock_data,0)

	intermedio1 = int(0.3*pasos);
	intermedio2 = int(0.6*pasos);


	rock0 = np.reshape(rock_data[0,:], (n,n))
	rock_intermedio1 = np.reshape(rock_data[intermedio1,:], (n,n))
	rock_intermedio2 = np.reshape(rock_data[intermedio2,:], (n,n))
	rockf = np.reshape(rock_data[-1,:], (n,n))
	rockm2 = np.mean(rock_data, 1)

										#Esta seccion no la comento porque es lo mismo que las dos de aca arriba!! Cambia el archivo


	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rock0, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rock0_p.png')

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rockf, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rockf_p.png')

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rock_intermedio1, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rock1_p.png')

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rock_intermedio2, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rock2_p.png')
	################################################################


	#Grafica que me plotea el cambio de las tres condiciones para la roca

	tf = np.genfromtxt("tiempo.csv", skip_header=1)					#Leame el archivo de tiempo
	t = np.linspace(0,tf,pasos)							#Arreglo para el tiempo


	fig = plt.figure()								#Me crea mi figura
	plt.plot(t, rockm0)								#Me plotea mis tres rocas	
	plt.plot(t, rockm1)	
	plt.plot(t, rockm2)
	plt.legend(['F','A', 'P'])							#Pongame la leyenda para fija, periodica y abierta
	plt.ylabel('T media')								#Pongame los nombres de los ejes
	plt.xlabel('t [s]')
	plt.savefig('rockm.png')							#Guardeme la figura con este nombre y en ese formato para poder ponerlo en el Latex
