/** @file Cluster.cc
    @brief Codi de la classe Cluster
*/

#include "Cluster.hh"
#include <iostream>
using namespace std;

BinTree<string> Cluster::modificar_cluster_aux(const BinTree<string>& estruct, const BinTree<string>& arbre_nou, string identificador, bool& trobat) {
    if (estruct.empty()) return estruct;
    else if (estruct.value() == identificador) {
        trobat = true;
        return arbre_nou;   
    }
    BinTree<string> arbre_esquerra = modificar_cluster_aux(estruct.left(), arbre_nou, identificador, trobat);
    BinTree<string> arbre_dret = estruct.right();
    if (not trobat) arbre_dret = modificar_cluster_aux(estruct.right(), arbre_nou, identificador, trobat);
    BinTree<string> arbre_modificat(estruct.value(), arbre_esquerra, arbre_dret);
    return arbre_modificat;
}

Cluster::Cluster() {}

void Cluster::configurar_cluster() {
    procesadors.clear();
    configurar_cluster_aux(estructura);
}

void Cluster::configurar_cluster_aux(BinTree<string>& aux2) {
    string aux_first;
    cin >> aux_first;
    if (aux_first != "*") {
        int aux_second;
        cin >> aux_second;
        procesadors.insert(make_pair(aux_first, Procesador (aux_first, aux_second)));
        BinTree<string> left;
        BinTree<string> right;
        configurar_cluster_aux(left);
        configurar_cluster_aux(right);
        aux2 = BinTree<string> (aux_first, left, right);
    }
}

void Cluster::modificar_cluster(string identificador) {
    Cluster aux;
    aux.configurar_cluster();
    if (not existe_procesador(identificador)) cout << "error: no existe procesador" << endl;
    else {
        map<string, Procesador>::iterator it = procesadors.find(identificador);
        if (it->second.hi_ha_procesos_en_exe()) cout << "error: procesador con procesos" << endl;
        else if(not no_tiene_procesadores_aux(identificador, estructura)) cout << "error: procesador con auxiliares" << endl;
        else {
            bool trobat = false;
            estructura = modificar_cluster_aux(estructura, aux.consultar_estructura(), identificador, trobat);
            map<string, Procesador>::iterator it2 = procesadors.find(identificador);
            it2 = procesadors.erase(it2);
            anadir_procesadores(aux.consultar_procesadors());
        }
    }
}

void Cluster::alta_proceso_procesador(string identificador, Proceso p) {
    if (not existe_procesador(identificador)) cout << "error: no existe procesador" << endl;
    else {
        map<string, Procesador>::iterator it = procesadors.find(identificador);
        if (it->second.existe_proceso(p.consultar_iden())) cout << "error: ya existe proceso" << endl;
        else {
            int hueco = it->second.buscar_hueco(p.consultar_memoria());
            if (hueco == -1) cout << "error: no cabe proceso" << endl;
            else {
                it->second.ejecutar_proceso(p, hueco);
            }
        }
    }
}

void Cluster::baja_proceso_procesador(string identificador, int identificador_job) {
    if (not existe_procesador(identificador)) cout << "error: no existe procesador" << endl;
    else {
        map<string, Procesador>::iterator it = procesadors.find(identificador);
        if (not it->second.existe_proceso(identificador_job)) cout << "error: no existe proceso" << endl;
        else {
            it->second.eliminar_proceso(identificador_job);
        }
    }
}

void Cluster::anadir_procesadores(const map<string, Procesador>& prc) {
    map<string, Procesador>::const_iterator it = prc.begin();
    while (it != prc.end()) {
        procesadors.insert(make_pair(it->first, it->second));
        ++it;
    }
}

void Cluster::avanzar_tiempo(int t) {
    map<string, Procesador>::iterator it = procesadors.begin();
    while (it != procesadors.end()) {
        it->second.avanzar_tiempo_procesador(t);
        ++it;
    }
}

bool Cluster::colocar_proceso(Proceso& p) {
    int mida = -1;
    int mem_lliure = -1;
    int pos = -1;
    map<string, Procesador>::iterator it_final;
    queue<BinTree<string>> aux;
    aux.push(estructura);
    while (not aux.empty()) {
        BinTree<string> aux2(aux.front());
        map<string, Procesador>::iterator it = procesadors.find(aux2.value());
        int mida_prc;
        int pos_prc;
        it->second.buscar_hueco_aux(p.consultar_memoria(), mida_prc, p.consultar_iden(), pos_prc);
        int mem_lliure_prc = it->second.consultar_mem_lliure();
        if (mida_prc != -1) {
            if (mida == -1 or mida_prc < mida) {
                pos = pos_prc;
                mida = mida_prc;
                mem_lliure = mem_lliure_prc;
                it_final = it;
            }
            else if(mida == mida_prc and mem_lliure_prc > mem_lliure) {
                pos = pos_prc;
                mida = mida_prc;
                mem_lliure = mem_lliure_prc;
                it_final = it;
            }
        }
        if (not aux2.left().empty()) aux.push(aux2.left());
        if (not aux2.right().empty()) aux.push(aux2.right());
        aux.pop();
    }
    if (mida != -1) {
        it_final->second.ejecutar_proceso(p, pos);
        return true;
    }
    return false;
}

void Cluster::compactar_memoria_procesador(string identificador) {
    if (not existe_procesador(identificador)) cout << "error: no existe procesador" << endl;
    else {
        map<string, Procesador>::iterator it3 = procesadors.find(identificador);
        it3->second.compactar_memoria_prc();
    }
}

void Cluster::compactar_memoria_cluster() {
    map<string, Procesador>::iterator it = procesadors.begin();
    while (it != procesadors.end()) {
        it->second.compactar_memoria_prc();
        ++it;
    }
}

Procesador Cluster::consultar_procesador(string identificador) {
    map<string, Procesador>::iterator it = procesadors.find(identificador);
    return it->second;
}

bool Cluster::existe_procesador(string identificador) {
    map<string, Procesador>::iterator it = procesadors.find(identificador);
    return it != procesadors.end();
}

bool Cluster::no_tiene_procesadores_aux(string identificador, const BinTree<string>& estruct) {
    if (estruct.empty()) return false;
    if (estruct.value() == identificador) {
        return (estruct.left().empty() and estruct.right().empty());
    }
    else {
        return no_tiene_procesadores_aux(identificador, estruct.left()) or no_tiene_procesadores_aux(identificador, estruct.right());
    }
}

BinTree<string> Cluster::consultar_estructura() {
    return estructura;
}

map<string, Procesador> Cluster::consultar_procesadors() {
    return procesadors;
}

void Cluster::imprimir_procesador(string identificador) {
    if (not existe_procesador(identificador)) cout << "error: no existe procesador" << endl;
    else {
        consultar_procesador(identificador).imprimir_procesador();
    }
}

void Cluster::imprimir_procesadores_cluster() {
    map<string, Procesador>::iterator it = procesadors.begin();
    while (it != procesadors.end()) {
        cout << it->first << endl;
        it->second.imprimir_procesador();
        ++it;
    }
}

void Cluster::imprimir_estructura_cluster(const BinTree<string>& estruct) {
    if (estruct.empty()) cout << " ";
    else {
        cout << "(" << estruct.value();
        imprimir_estructura_cluster(estruct.left());
        imprimir_estructura_cluster(estruct.right());
        cout << ")";
    }
}
