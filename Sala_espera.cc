/** @file Sala_espera.cc
    @brief Codi de la classe Sala_espera
*/

#include "Sala_espera.hh"
#include <iostream>
using namespace std;

Sala_espera::Sala_espera(int n) {
    for (int i = 0; i < n; ++i) {
        string identificador;
        cin >> identificador;
        prioridades.insert(make_pair(identificador, Prioridad (identificador)));
    }
}

void Sala_espera::alta_prioridad(string identificador) {
    if (existe_prioridad(identificador)) cout << "error: ya existe prioridad" << endl;
    else {
        prioridades.insert(make_pair(identificador, Prioridad (identificador)));
    }
}

void Sala_espera::baja_prioridad(string identificador) {
    if (not existe_prioridad(identificador)) cout << "error: no existe prioridad" << endl;
    else {
        if (consultar_prioridad(identificador).te_processos_pendents()) cout << "error: prioridad con procesos" << endl;
        else {
            prioridades.erase(identificador);
        }
    }
}

void Sala_espera::alta_proceso_espera(string identificador, Proceso p) {
    if (not existe_prioridad(identificador)) cout << "error: no existe prioridad" << endl;
    else {
        if (consultar_prioridad(identificador).existe_proceso(p.consultar_iden())) cout << "error: ya existe proceso" << endl;
        else {
            map<string, Prioridad>::iterator it = prioridades.find(identificador);
            it->second.anadir_proceso(p);
        }
    }
}

void Sala_espera::enviar_procesos_cluster(int n, Cluster& cluster) {
    map<string, Prioridad>::iterator it = prioridades.begin();
    while (n > 0 and it != prioridades.end()) {
        it->second.enviar_processos(n, cluster);
        ++it;
    }
}

bool Sala_espera::existe_prioridad(string identificador) {
    map<string, Prioridad>::iterator it = prioridades.find(identificador);
    return it != prioridades.end();
}

Prioridad Sala_espera::consultar_prioridad(string identificador) {
    map<string, Prioridad>::iterator it = prioridades.find(identificador);
    return it->second;
}

void Sala_espera::imprimir_prioridad(string identificador) {
    if (not existe_prioridad(identificador)) cout << "error: no existe prioridad" << endl;
    else {
        map<string, Prioridad>::iterator it1 = prioridades.find(identificador);
        it1->second.imprimir_p();
    }
}

void Sala_espera::imprimir_area_espera() {
    map<string, Prioridad>::iterator it = prioridades.begin();
    while (it != prioridades.end()) {
        cout << it->first << endl;
        it->second.imprimir_p();
        ++it;
    }
}
