OPCIONS = -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++11
#
# La seguent instruccio serveix per obtenir el executable del programa principal.
#
program.exe: program.o Cluster.o Procesador.o Sala_espera.o Prioridad.o Proceso.o
	g++ -o program.exe program.o Cluster.o Procesador.o Sala_espera.o Prioridad.o Proceso.o
#
# Les seguents instruccions serveixen per obtenir els fitxers objecte de cada clase i del main.
#
program.o: program.cc
	g++ -c program.cc $(OPCIONS)
Cluster.o: Cluster.cc
	g++ -c Cluster.cc $(OPCIONS)
Procesador.o: Procesador.cc
	g++ -c Procesador.cc $(OPCIONS)
Sala_espera.o: Sala_espera.cc
	g++ -c Sala_espera.cc $(OPCIONS)
Prioridad.o: Prioridad.cc
	g++ -c Prioridad.cc $(OPCIONS)
Proceso.o: Proceso.cc
	g++ -c Proceso.cc $(OPCIONS)
#
# La ultima instruccio serveix per netejar el directori de fitxers innecessaris ("make clean" per executar-la).
#

tar:
	tar -cvf practica.tar *.cc *.hh Makefile

clean:
	rm *.o
	rm *.exe
	rm *.tar
