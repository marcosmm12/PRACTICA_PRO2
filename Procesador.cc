/** @file Procesador.cc
    @brief Codi de la classe Procesador
*/

#include "Procesador.hh"
#include <iostream>
using namespace std;

Procesador::Procesador() {
    idn = "";
    procesos_en_eje.clear();
    memoria_prc.clear();
    llocs_lliures.clear();
    llocs_lliures.insert(make_pair(0, set<int> {0}));
}

Procesador::Procesador(string identificador, int mem1) {
    idn = identificador;
    mem = mem1;
    mem_lliure = mem1;
    procesos_en_eje.clear();
    memoria_prc.clear();
    llocs_lliures.clear();
    llocs_lliures.insert(make_pair(mem, set<int> {0}));
}

void Procesador::compactar_memoria_prc() {
        map<int, Proceso>::iterator it = procesos_en_eje.begin();
        int pos = 0;
        while (it != procesos_en_eje.end()) {
            Proceso p = it->second;
            it = procesos_en_eje.erase(it);
            it = procesos_en_eje.insert(it, make_pair(pos, p));
            map<int, int>::iterator it2 = memoria_prc.find(p.consultar_iden());
            it2->second = pos;
            pos += it->second.consultar_memoria();
            ++it;
        }
        llocs_lliures.clear();
        llocs_lliures.insert(make_pair(mem - pos, set<int> {pos}));
}

void Procesador::ejecutar_proceso(Proceso p, int pos) {
    map<int, set<int>>::iterator it2 = llocs_lliures.lower_bound(p.consultar_memoria());
    memoria_prc.insert(make_pair(p.consultar_iden(), pos));
    procesos_en_eje.insert(make_pair(pos, p));
    mem_lliure = mem_lliure - p.consultar_memoria();
    int hueco = it2->first - p.consultar_memoria();
    it2->second.erase(it2->second.begin());
    if (it2->second.empty()) llocs_lliures.erase(it2);
    if (hueco > 0) {
        it2 = llocs_lliures.find(hueco);
        if (it2 == llocs_lliures.end()) {
            llocs_lliures.insert(make_pair(hueco, set<int> {pos + p.consultar_memoria()}));
        }
        else it2->second.insert(pos + p.consultar_memoria());
    }
}


void Procesador::eliminar_proceso(int identificador) {
    map<int, int>::iterator it1 = memoria_prc.find(identificador);
    map<int, Proceso>::iterator it2 = procesos_en_eje.find(it1->second);
    int hueco = it2->second.consultar_memoria();
    int pos = it1->second;
    mem_lliure = mem_lliure + it2->second.consultar_memoria();
    //Juntar el lloc de la dreta
    map<int, Proceso>::iterator it_costat = it2;
    ++it_costat;
    int nova_pos = pos + hueco;
    if (it_costat != procesos_en_eje.end()) {
        if (it_costat->first > nova_pos) {
            int dif = it_costat->first - nova_pos;
            hueco += dif;
            map<int, set<int>>::iterator it_mem = llocs_lliures.find(dif);
            it_mem->second.erase(nova_pos);
            if (it_mem->second.empty()) llocs_lliures.erase(it_mem);
        }
    }
    else {
        int dif = mem - nova_pos; //si estem al final hem de mirar que no hagi un forat al final
        if (dif != 0) {
            hueco += dif;
            map<int, set<int>>::iterator it_mem = llocs_lliures.find(dif);
            it_mem->second.erase(nova_pos);
            if (it_mem->second.empty()) llocs_lliures.erase(it_mem);
        }
    }
    it_costat = it2;
    //Juntar el lloc de l'esquerra
    if (it2 != procesos_en_eje.begin()) {
        --it_costat;
        nova_pos = it_costat->first + it_costat->second.consultar_memoria();
        if (nova_pos != pos) {
            int dif  = pos - nova_pos;
            hueco += dif;
            pos = nova_pos;
            map<int, set<int>>::iterator it_mem = llocs_lliures.find(dif);
            it_mem->second.erase(nova_pos);
            if (it_mem->second.empty()) llocs_lliures.erase(it_mem);
        }
    }
    else if (pos != 0) {
        int dif = pos;
        hueco += dif;
        pos = 0;
        map<int, set<int>>::iterator it_mem = llocs_lliures.find(dif);
        it_mem->second.erase(it_mem->second.begin());
        if (it_mem->second.empty()) llocs_lliures.erase(it_mem);
    }
    //Acabar d'eliminar el proces
    map<int, set<int>>::iterator it3 = llocs_lliures.find(hueco);
    if (it3 == llocs_lliures.end()) llocs_lliures.insert(make_pair(hueco, set<int> {pos}));
    else it3->second.insert(pos);
    memoria_prc.erase(it1);
    procesos_en_eje.erase(it2);
}

void Procesador::avanzar_tiempo_procesador(int t) {
    if (not procesos_en_eje.empty()) {
        map<int, Proceso>::iterator it = procesos_en_eje.begin();
        while (it != procesos_en_eje.end()) {
            if (it->second.restar_tiempo(t)) {
                mem_lliure += it->second.consultar_memoria();
                map<int, int>::iterator it_aux = memoria_prc.find(it->second.consultar_iden());
                memoria_prc.erase(it_aux);
                it = procesos_en_eje.erase(it);
            }
            else ++it;
        }
        llocs_lliures.clear();
        map<int,Proceso>::iterator it_aux = procesos_en_eje.begin();
        int pos = 0;
        while (it_aux != procesos_en_eje.end()) {
            if (pos != it_aux->first) {
                llocs_lliures[it_aux->first - pos].insert(pos);
            }
            pos = it_aux->first + it_aux->second.consultar_memoria();
            ++it_aux;
        }
        if (mem > pos) llocs_lliures[mem - pos].insert(pos);
    }
}

bool Procesador::existe_proceso(int identificador) {
    map<int, int>::iterator it = memoria_prc.find(identificador);
    if (it == memoria_prc.end()) return false;
    return true;
}

void Procesador::buscar_hueco_aux(int mem1, int& mida, int identificador, int& pos) {
    map<int, set<int>>::iterator it = llocs_lliures.lower_bound(mem1);
    if (it != llocs_lliures.end() and not existe_proceso(identificador)) {
        mida = it->first;
        pos = *it->second.begin();
    }
    else {
        mida = -1;
        pos = -1;
    }
}

int Procesador::buscar_hueco(int mem1) {
    map<int, set<int>>::iterator it = llocs_lliures.lower_bound(mem1);
    if (it != llocs_lliures.end()) {
        return *it->second.begin();
    }
    return -1;
}

int Procesador::consultar_mem_lliure() {
    return mem_lliure;
}

Proceso Procesador::consultar_proceso(int identificador) {
    map<int, int>::iterator it = memoria_prc.find(identificador);
    map<int, Proceso>::iterator it2 = procesos_en_eje.find(it->second);
    return it2->second;
}

bool Procesador::hi_ha_procesos_en_exe() {
    if (memoria_prc.empty()) return false;
    return true;
}

void Procesador::leer_procesador() {
    cin >> idn >> mem;
    mem_lliure = mem;
    procesos_en_eje.clear();
    memoria_prc.clear();
    llocs_lliures.clear();
    llocs_lliures.insert(make_pair(mem, set<int> {0}));
}

void Procesador::imprimir_procesador() const{
    map<int, Proceso>::const_iterator it = procesos_en_eje.begin();
    while (it != procesos_en_eje.end()) {
        cout << it->first << ' ';
        it->second.imprimir_proceso();
        ++it;
    }
}
