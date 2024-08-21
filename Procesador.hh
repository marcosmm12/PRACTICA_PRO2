/** @file Procesador.hh
    @brief Especificació de la classe Procesador
*/

#ifndef Procesador_HH
#define Procesador_HH

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
#include <string>
#include <iostream>
#endif

using namespace std;

/*
 * Classe Procesador
 */

/** @class Procesador
    @brief Conté l'identificador del procesador, la seva memòria total i la que li queda lliure i els processos que conté el procesador i com estan distribuïts aquests en memòria.

    Conté la seva constructora, les funcions consultores i les de lectura i escriptura. També conté funcions per compactar la memòria del procesador, per afegir i esborrar processos, per buscar forats on col·locar diferents processos i per avançar el temps del procesador .
*/
class Procesador {

private:
    /** @brief Identificador del procesador */
    string idn;
    /** @brief Memòria total del procesador */
    int mem;
    /** @brief Memòria lliure del procesador */
    int mem_lliure;
    /** @brief Processos del procesador ordenats per posició a memòria */
    map <int, Proceso> procesos_en_eje;
    /** @brief Identificador dels processos i la seva posició inicial a memoria */
    map <int, int> memoria_prc;
    /** @brief Forats del processador i la posició inicial on comencen aquests forats */
    map <int, set<int>> llocs_lliures;

public:

    //Constructores

    /** @brief Constructora per defecte
        \pre Cert
        \post El resultat és un procesador buit
        \par Cost Constant
    */
    Procesador();

    /** @brief Constructora que crea un procesador buit amb idn = identificador i memòria total = mem1
        \pre mem1 es un enter positiu
        \post El resultat és un procesador buit d'idn = identificador i de mem = mem1
        \par Cost Constant
    */
    Procesador(string identificador, int mem1);

    //Modificadores

    /** @brief Modificadora que mou tots els processos del procesador al principi de la memòria, sense solapar-ne cap i sense deixar llocs lliures, tot respectant l'ordre inicial
        \pre Cert
        \post Es mouen tots els processos del procesador al principi de la memòria, sense deixar forats ni solapar-se i respectant l'ordre inicial
        \par Cost Lineal
    */
    void compactar_memoria_prc();

    /** @brief Modificadora que afegeix el procés p al procesador, ocupant el lloc de memòria que comença a la posició pos
        \pre pos és un enter que correspon a la posició inicial d'un forat a memòria de mida igual o superior a la que ocupa el procés i p es un procés no buit
        \post El procés s'ha afegit al map<int, Proceso> procesos_en_eje, al map<int, int> memoria_prc i la posició s'ha eliminat del map<int, set<int>> llocs_lliures
        \par Cost log(n), sent n el número de processos que té el procesador
    */
    void ejecutar_proceso(Proceso p, int pos);

    /** @brief Modificadora que elimina el procés amb iden = identificador del procesador
        \pre Existeix un procés al procesador amb iden = identificador
        \post El procés amb iden = identificador s'ha eliminat del map<int, Proceso> procesos_en_eje, del map<int, int> memoria_prc i el forat que s'allibera s'ha afegit al map<int, set<int>> ajuntant-se amb els forats frontera, si és que en té
        \par Cost log(n), sent n el número de processos que té el procesador
    */
    void eliminar_proceso(int identificador);

    /** @brief Modificadora que avança el temps al procesador en t unitats, eliminant els processos que hagin acabat un cop passades aquestes unitats
        \pre t és un enter positiu
        \post Tots els processos del procesador progresen t unitats de temps i, si el seu temps és negatiu, son eliminats
        \par Cost Lineal
    */
    void avanzar_tiempo_procesador(int t);

    //Consultores

    /** @brief Consultora que comprova si existeix un procés amb iden = identificador al procesador
        \pre identificador és un enter positiu
        \post El resultat és cert si existeix un procés amb iden = identificador al procesador, fals en cas contrari
        \par Cost log(n), sent n el número de processos del procesador
    */
    bool existe_proceso(int identificador);

    /** @brief Consultora que busca el forat del procesador que més s'ajusta a mem1 i retorna la seva mida i on comença
        \pre mem1 i identificador son enters positius
        \post mida conté la mida del forat que més s'ajusta a mem1 i pos conté la posició on comença aquest forat; ambdós seran -1 en cas de no trobar un forat de mida igual o superior a mem1
        \par Cost log(n), sent n el número de forats que te el procesador
    */
    void buscar_hueco_aux(int mem1, int& mida, int identificador, int& pos);

    /** @brief Consultora que busca el forat del procesador que més s'ajusta a mem1 i retorna on comença
        \pre mem1 es un enter positiu
        \post Retorna la pos on comença el forat del procesador que més s'ajusta a mem1, -1 en cas de no trobar cap forat de mida igual o superior a mem1
        \par Cost log(n), sent n el número de forats que té el procesador
    */
    int buscar_hueco(int mem1);

    /** @brief Consultora que retorna la memòria lliure del procesador
        \pre Cert
        \post Retorna la memòria lliure del procesador
        \par Cost Constant
    */
    int consultar_mem_lliure();

    /** @brief Consultora que retorna el procés del procesador amb iden = identificador
        \pre Al procesador existeix un procés amb iden = identificador
        \post El procés del map<int, Proceso> procesos_en_eje que té idn = identificador
        \par Cost 2*log(n), sent n el número de processos que té el procesador
    */
    Proceso consultar_proceso(int identificador);

    /** @brief Consultora que comprova si el procesador té processos en execució
        \pre Cert
        \post El resultat és cert si el procesador té processos en execució, fals en cas contrari
        \par Cost Constant
    */
    bool hi_ha_procesos_en_exe();

    //Lectura i escriptura

    /** @brief Llegeix l'identificador i la memòria d'un procesador i en crea un d'aquestes característiques
        \pre Cert
        \post Llegeix el idn i la memòria d'un procesador, fent que la seva mem_lliure sigui memòria i que llocs_lliures tingui un forat de mida memòria que comença a la posició 0
        \par Cost Constant
    */
    void leer_procesador();

    /** @brief Escriu la posició inicial de cada procés i la resta d'informació de cadascun
        \pre Cert
        \post Imprimeix els processos del procesador per ordre de posició ocupada a la memòria, incloent la posició i la resta de dades de cada procés
        \par Cost Lineal
    */
    void imprimir_procesador() const;

};
#endif
