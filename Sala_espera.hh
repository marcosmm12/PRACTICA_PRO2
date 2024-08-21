/** @file Sala_espera.hh
    @brief Especificació de la classe Sala_espera
*/

#ifndef Sala_espera_HH
#define Sala_espera_HH

#include "Cluster.hh"
#include "Prioridad.hh"
#include "Proceso.hh"
using namespace std;

#ifndef NO_DIAGRAM
#include <map>
#include <list>
#include <iostream>
#endif

/*
 * Classe Sala_espera
 */

/** @class Sala_espera
    @brief Conté les prioritats de la sala d'espera.

    Conté la seva constructora, les funcions consultores i les de lectura i escriptura. També conté funcions per afegir i esborrar prioritats de la sala d'espera, per afegir processos i per enviar-ne altres al cluster.
*/
class Sala_espera {

private:
    /** @brief Prioritats de la sala d'espera ordenades per identificador */
    map <string, Prioridad> prioridades;

public:

    //Constructores

    /** @brief Constructora per defecte que llegeix i afegeix a la sala d'espera n prioritats
        \pre n és un enter positiu
        \post Crea una sala d'espera amb un map<string, Prioritat> prioritats que conté les n prioritats de la sala ordenades segons el seu iden
        \par Cost n*log(n)
    */
    Sala_espera(int n);

    //Modificadores

    /** @brief Modificadora que comprova que no existeixi cap prioritat amb iden = identificador i, en cas afirmatiu, afegeix la prioritat a la sala d'espera
        \pre identificador és un string no buit
        \post Si no existeix cap prioritat amb iden = identificador, s'afegeix una prioritat amb iden = identificador sense processos pendents al map<string, Prioritat> prioritats
        \par Cost log(n), sent n el número de prioritats de la sala d'espera
    */
    void alta_prioridad(string identificador);

    /** @brief Modificadora que comprova que existeixi una prioritat amb iden = identificador a la sala d'espera i que aquesta no tingui processos pendents i, en cas afirmatiu, elimina la prioritat de la sala d'espera
        \pre identificador és un string no buit
        \post Si existeix una prioritat amb iden = identificador i aquesta no té processos pendents, s'elimina del map<string, Prioritat> prioritats aquesta prioritat
        \par Cost log(n), sent n el número de prioritats de la sala d'espera
    */
    void baja_prioridad(string identificador);

    /** @brief Modificadora que comprova que existeixi una prioritat amb iden = identificador a la sala d'espera i que aquesta no tingui un procés igual a p i, en cas afirmatiu, afegeix p a la sala d'espera amb aquesta prioritat
        \pre identificador és un string no buit i p es un procés no buit
        \post Si existeix una prioritat amb iden = identificador i aquesta no conté cap procés amb iden = iden de p, s'afegeix p a la prioritat
        \par Cost log(n), sent n el número de prioritats de la sala d'espera
    */
    void alta_proceso_espera(string identificador, Proceso p);

    /** @brief Modificadora que intenta enviar al cluster n processos, sent aquests processos els que tenen major prioritat i, dinte d'una mateixa prioritat, els més antics
        \pre n és un enter positiu
        \post S'han intentat enviar n processos de la sala d'espera al cluster, col·locant-los per ordre de prioritat i antiguitat al procesador que tingui el lloc més ajustat, que quedi amb més memòria lliure i que estigui més a l'esquerra i més a prop de l'arrel del BinTree<string> estructura i retornant-los en cas de que no es puguin afegir
        \par Cost Lineal
    */
    void enviar_procesos_cluster(int n, Cluster& cluster);

    //Consultores

    /** @brief Consultora que comprova si existeix una prioritat a la sala d'espera amb iden = identificador
        \pre identificador és un string no buit
        \post El resultat és cert si existeix una prioritat amb iden = identificador, fals en cas contrari
        \par Cost log(n), sent n el número de prioritats de la sala d'espera
    */
    bool existe_prioridad(string identificador);

    /** @brief Consultora que retorna la prioritat de la sala d'espera amb iden = identificador
        \pre identificador és un string no buit
        \post El resultat és la prioritat del map<string, Prioritat> prioritats amb iden = identificador
        \par Cost log(n) + m, sent n el número de prioritats de la sala d'espera i m el número de processos d'aquesta prioritat
    */
    Prioridad consultar_prioridad(string identificador);

    //Lectura i escriptura

    /** @brief Escriu la prioritat de la sala d'espera amb iden = identificador, escrivint els seus processos del més antic al més recent i escrivint el número de processos enviats per la prioritat al cluster i el número de processos rebutjats per aquest
        \pre identificador és un string no buit
        \post Si existeix una prioritat amb iden = identificador, s'han escrit els processos pendents d'aquesta en ordre decreixent d'antiguitat, el número de processos de la prioritat enviats al cluster i el número de processos que aquest ha rebutjat
        \par Cost log(n) + m, sent n el número de prioritats de la sala d'espera i m el número de processos d'aquesta prioritat
    */
    void imprimir_prioridad(string identificador);

    /** @brief Escriu les prioritats de la sala d'espera de major a menor prioritat, tot escrivint l'identificador de cada prioritat i seguint la funcionalitat imprimir_p()
        \pre Cert
        \post S'han escrit els processos pendents de les prioritats de la sala d'espera per ordre creixent de iden, escrivint per a cada prioritat els processos pendents en ordre decreixent d'antiguitat, el número de processos de la prioritat enviats al cluster i el número de processos que aquest ha rebutjat
        \par Cost Lineal en funció del número de prioritats de la sala d'espera i del número de processos de cada prioritat
    */
    void imprimir_area_espera();

};
#endif
