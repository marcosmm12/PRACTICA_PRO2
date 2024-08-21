/** @file Prioridad.hh
    @brief Especificació de la classe Prioridad
*/

#ifndef Prioridad_HH
#define Prioridad_HH
using namespace std;

#include "Proceso.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <list>
#include <string>
#include <iostream>
#endif

/*
 * Classe Prioridad
 */

/** @class Prioridad
    @brief Conté l'identificador de la prioritat, el comptador dels processos que ha enviat al cluster i el comptadors dels que processos que han sigut rebutjats pel mateix, els processos de la sala d'espera amb aquesta prioritat per ordre d'arribada.

    Conté la seva constructora, les funcions consultores i les de lectura i escriptura. També conté funcions per enviar un determinat nombre de processos al cluster, per afegir i esborrar un procés de la prioritat.
*/
class Prioridad {

private:
    /** @brief Identificador de la prioritat */
    string iden;
    /** @brief Comptador de processos de la prioritat enviats al cluster */
    int processos_enviats;
    /** @brief Comptador de processos rebutjats pel cluster */
    int processos_rebutjats;
    /** @brief Processos de la prioritat */
    list <Proceso> processos;

public:

    //Constructores

    /** @brief Constructora que crea una prioritat buida amb iden = identificador
        \pre identificador es un string no buit
        \post Una prioritat buida que te iden = identificador
        \par Cost Constant
    */
    Prioridad(string identificador);

    //Modificadores

    /** @brief Modificadora que intenta enviar n processos al cluster, posant-los al final de la llista de processos en cas de ser rebutjats i eliminant-los en cas contrari, tot portant un recompte del processos enviats i rebutjats
        \pre n és un enter positiu que indica els processos que encara pot rebre el cluster
        \post Envia al cluster tots els processos que pugui rebre i afegeix al final de la llista els que no es poden enviar
        \par Cost Lineal
    */
    void enviar_processos(int& n, Cluster& c);

    /** @brief Modificadora que afegeix el procés p a la llista de processos de la prioritat
        \pre p és un proces no buit
        \post El proces p s'ha afegit al final de la list<Proceso> processos
        \par Cost Constant
    */
    void anadir_proceso(const Proceso& p);

    /** @brief Modificadora que borra el procés més antic de la prioritat
        \pre Cert
        \post S'ha borrat el primer procés de la llista de processos
        \par Cost Constant
    */
    void borrar_primer_proceso();

    //Consultores

    /** @brief Consultora que retorna el procés més antic de la prioritat
        \pre Cert
        \post El resultat és el primer procés de la list<Proceso> processos
        \par Cost Constant
    */
    Proceso consultar_primer_proceso();

    /** @brief Consultora que comprova si existeixen processos pendents amb aquesta prioritat
        \pre Cert
        \post El resultat és cert si la prioritat té processos, fals en cas contrari
        \par Cost Constant
    */
    bool te_processos_pendents();

    /** @brief Consultora que retorna el procés de la prioritat amb iden = identificador
        \pre identificador és un enter positiu
        \post El resultat és cert si existeix un proces amb iden = identificador a la prioritat, fals en cas contrari
        \par Cost Lineal
    */
    bool existe_proceso(int identificador);

    //Lectura i escriptura

    /** @brief Escriu els processos de la prioritat per ordre d'antiguitat i el recompte del processos que s'han enviat al cluster amb aquesta prioritat i també el recompte dels que han sigut rebutjats
        \pre Cert
        \post Escriu els processos de la prioritat per ordre d'antiguitat, el número de processos enviats al cluster i el número de processos rebutjats pel cluster
        \par Cost Lineal
    */
    void imprimir_p();

};
#endif
