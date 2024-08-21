/** @file Prioridad.cc
    @brief Codi de la classe Prioridad
*/

#include "Prioridad.hh"
#include <iostream>
using namespace std;

Prioridad::Prioridad(string identificador) {
    iden = identificador;
    processos_enviats = 0;
    processos_rebutjats = 0;
    processos.clear();
}

void Prioridad::enviar_processos(int& n, Cluster& c) {
    list<Proceso>::iterator it = processos.begin();
    int i = 0;
    int j = processos.size();
    while (n > 0 and i < j) {
        if (c.colocar_proceso(*it)) {
            --n;
            ++processos_enviats;
        }
        else {
            ++processos_rebutjats;
            processos.insert(processos.end(), *it);
        }
        it = processos.erase(it);
        ++i;
    }
}

void Prioridad::anadir_proceso(const Proceso& p) {
    list<Proceso>::iterator it2 = processos.end();
    processos.insert(it2, p);
}

void Prioridad::borrar_primer_proceso() {
    processos.erase(processos.begin());
}

Proceso Prioridad::consultar_primer_proceso() {
    return *processos.begin();
}

bool Prioridad::te_processos_pendents() {
    return not processos.empty();
}

bool Prioridad::existe_proceso(int identificador) {
    list<Proceso>::iterator it = processos.begin();
    while (it != processos.end()) {
        if ((*it).consultar_iden() == identificador) return true;
        ++it;
    }
    return false;
}


void Prioridad::imprimir_p() {
    list<Proceso>::iterator it = processos.begin();
    while (it != processos.end()) {
        (*it).imprimir_proceso();
        ++it;
    }
    cout << processos_enviats << ' ' << processos_rebutjats << endl;
}
