import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys


#Se supone que este programa deberia hacer todas las graficas que se pueden hacer a partir de los archivos de datos que cree en Pde y Ode

if (sys.argv[1]=='Ode'):
	print("\n"*4, "Graficas ODE")

	projectile = np.genfromtxt("projectile.csv", delimiter=',')
	plt.figure()
	plt.plot(projectile[:,1], projectile[:,2])
	plt.xlabel('x')
	plt.ylabel('y')
	plt.savefig('projectile45.png')	


	projectiles = np.genfromtxt("projectile_7alpha.csv", delimiter=",")
	x = projectiles[:,0:-1:4]
	y = projectiles[:,1:-1:4]
	print(np.shape(projectiles))
	print(np.shape(x), np.shape(y))

	plt.figure()
	plt.plot(x,y)
	plt.xlabel('x')
	plt.ylabel('y')
	plt.ylim( [0,np.max(np.max(y))] )
	plt.legend(["10","20","30","40", "50","60","70"])
	plt.savefig('projectiles7angulos.png')		


##########################################################
##########################################################
##########################################################
##########################################################
##########################################################
if (sys.argv[1]=='Pde'):
	print("\n"*4, "Graficas PDE")


	rock_data = np.genfromtxt('rock.csv', delimiter=',')
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
	rockm0 = np.mean(rock_data, 1)



	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rock0, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rock0.png')


	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rockf, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rockf.png')

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rock_intermedio1, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rock1.png')

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rock_intermedio2, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rock2.png')
	################################################################


	rock_data = np.genfromtxt('rock1.csv', delimiter=',')
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
	rockm1 = np.mean(rock_data, 1)




	fig = plt.figure()
	ax = fig.gca(projection='3d')	
	surf = ax.plot_surface(X,Y,rock0, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rock0_a.png')

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rockf, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rockf_a.png')

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rock_intermedio1, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rock1_a.png')

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	surf = ax.plot_surface(X,Y,rock_intermedio2, cmap="inferno")
	ax.set_zlim([0,100])
	#fig.colorbar()
	fig.savefig('rock2_a.png')
	################################################################

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


	tf = np.genfromtxt("tiempo.csv", skip_header=1)
	t = np.linspace(0,tf,pasos)


	fig = plt.figure()
	plt.plot(t, rockm0)	
	plt.plot(t, rockm1)	
	plt.plot(t, rockm2)
	plt.legend(['F','A', 'P'])
	plt.ylabel('T media')
	plt.xlabel('t [s]')
	plt.savefig('rockm.png')
