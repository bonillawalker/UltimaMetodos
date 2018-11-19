all:Resultados_hw4.pdf

Resultados_hw4.pdf:projectile45.png projectiles7angulos.png rock0.png rock1.png rock2.png rockf.png rockm.png Resultados_hw4.tex
	pdflatex Resultados_hw4.tex

rock0.png rock1.png rock2.png rockf.png rockm.png: rock.csv rock1.csv rock2.csv Plots_hw4.py
	python Plots_hw4.py PDE


projectile45.png projectiles7angulos.png: projectile.csv projectile_7alpha.csv
	python Plots_hw4.py ODE


rock.csv rock1.csv rock2.csv: PDE.cpp
	g++ PDE.cpp -o PDE.x
	./PDE.x

projectile.csv projectile_7alpha.csv: ODE.cpp
	g++ ODE.cpp -o ODE.x
	./ODE.x


clean:
	rm *.png
	rm *.csv
	rm *.x


