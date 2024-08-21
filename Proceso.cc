/** @file Proceso.cc
    @brief Codi de la classe Proceso
*/

#include "Proceso.hh"
#include <iostream>
using namespace std;

Proceso::Proceso() {
    iden = 0;
    memoria = 0;
    tiempo = 0;
}

bool Proceso::restar_tiempo(int t) {
    tiempo = tiempo - t;
    return tiempo <= 0;
}

int Proceso::consultar_tiempo() {
    return tiempo;
}

int Proceso::consultar_memoria() {
    return memoria;
}

int Proceso::consultar_iden() {
    return iden;
}

void Proceso::leer_proceso() {
    int identificador;
    int mem;
    int t;
    cin >> identificador >> mem >> t;
    iden = identificador;
    memoria = mem;
    tiempo = t;
}

void Proceso::imprimir_proceso() const {
    cout << iden << ' ' << memoria << ' ' << tiempo << endl;
}
