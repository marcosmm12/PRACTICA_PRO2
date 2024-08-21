/** @file Cluster.hh
    @brief Especificació de la classe Cluster
*/

#ifndef Cluster_HH
#define Cluster_HH

#include "Procesador.hh"
#include "BinTree.hh"
#include "Proceso.hh"
using namespace std;

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <list>
#include <queue>
#endif

/*
 * Classe Cluster
 */

/** @class Cluster
    @brief Conté l'estructura i els procesadors del cluster.

    Conté la seva constructora, les funcions consultores, les de lectura i escriptura i les funcions auxiliars. També conté operacions per modificar el cluster i per configurar-lo, per afegir i borrar processos, per avançar el temps dels processadors i per compactar la memòria dels procesadors.
*/
class Cluster {

private:
     /** @brief Estructura del cluster */
     BinTree<string> estructura;
     /** @brief Procesadors del cluster */
     map<string, Procesador> procesadors;

     //Funcions auxiliars

     /** \pre Existeix un procesador al cluster amb idn = identificador, trobat és sempre fals fins que no es trobi el procesador amb idn = identificador i es garantitza que al BinTree<string> arbre_nou no hi ha procesadors que ja estiguin al BinTree<string> estruct
         \post El BinTree<string> estruct ha susbtituït el node el valor del qual és identificador pel BinTree<string> arbre_nou
     */
     /** \par Cost Lineal */
     BinTree<string> modificar_cluster_aux(const BinTree<string>& estruct, const BinTree<string>& arbre_nou, string identificador, bool& trobat);

     /** \pre Cert
         \post Si l'identificador que es llegeix es diferent de '*', es llegeix la memòria del procesador amb aquest identificador i s'afegeix al BinTree<string> estructura i al mapa<string, Procesador> procesadors
     */
     /** \par Cost Lineal */
     void configurar_cluster_aux(BinTree<string>& estruct);

public:

     //Constructores

     /**  @brief Constructora per defecte
          \pre Cert
          \post El resultat és un cluster buit
     */
     /** \par Cost Constant */
     Cluster();

     //Modificadores

     /**  @brief Modificadora que llegeix un conjunt de procesadors, les seves connexions i les seves característiques i configura el cluster correctament
          \pre Cert
          \post Si ja existia un cluster anterior, aquest queda substituit pel cluster que es configura durant la funció
     */
     /** \par Cost Lineal */
     void configurar_cluster();

     /**  @brief Modificadora que llegeix l'identificador d'un procesador i un nou cluster i, si existeix un procesador amb aquest identificador, sense processos i sense procesadors auxiliars al cluster inicial, el substitueix pel nou cluster, ampliant el cluster inicial
          \pre identificador és un string no buit
          \post Si existeix un procesador amb idn = identificador, no té fills i no té processos en execució, es substitueix aquest procesador per un nou cluster, de manera que el cluster original queda ampliat
     */
     /** \par Cost Lineal */
     void modificar_cluster(string identificador);

     /**  @brief Modificadora que comprova si existeix un procesador al cluster amb idn = identificador i aquest no conté cap procés amb el mateix identificador que el procés p, i en cas afirmatiu l'afegeix al procesador indicat
          \pre identificador és un string no buit i p es un procés no buit
          \post Si existeix un procesador amb idn = identificador i aquest no té un proces amb iden = iden de p, s'afegeix el procés p al procesador
     */
     /** \par Cost Constant */
     void alta_proceso_procesador(string identificador, Proceso p);

     /**  @brief Modificadora que comprova si existeix un procesador al cluster amb idn = identificador i aquest té un procés amb iden = identificador_job, i en cas afirmatiu l'elimina del procesador
          \pre identificador és un string no buit i identificador_job un enter positiu
          \post Si existeix un procesador amb idn = identificador i un procés al procesador amb iden = identificador_job, s'elimina el procés del procesador
     */
     /** \par Cost Constant */
     void baja_proceso_procesador(string identificador, int identificador_job);

     /**  @brief Modificadora que afegeix els procesadors del mapa prc al mapa de procesadors del cluster inicial
          \pre Cert
          \post S'han afegit els procesadors del map<string, Procesador> de l'entrada al map<string, Procesador> procesadors del cluster
     */
     /** \par Cost n*log(n), sent n el número de procesadors a afegir */
     void anadir_procesadores(const map<string, Procesador>& prc);

     /**  @brief Modificadora que busca el procesador més òptim per afegir un procés i, si el troba, afegeix el procés i retorna cert, sinó retorna fals
          \pre p es un procés no buit
          \post El resultat és cert en cas de que s'hagi pogut afegir el proces a algun procesador del cluster, fals en cas contrari
     */
     /** \par Cost Lineal */
     bool colocar_proceso(Proceso& p);

     /**  @brief Modificadora que avança t unitats el temps a tots els procesadors
          \pre t és un enter positiu
          \post S'avança el temps en t unitats de temps a tots el procesadors del cluster, eliminant aquells que triguin una quantitat de temps inferior a l'avançat
     */
     /** \par Cost Lineal */
     void avanzar_tiempo(int t);

     /**  @brief Modificadora que comprova si existeix un procesador al cluster amb idn = identificador i, en cas afirmatiu, compacta la seva memòria desplaçant tots els processos al principi de la memòria, sense deixar forats ni solapar-se i respectant l'ordre inicial
          \pre identificador és un string no buit
          \post Mou tots els processos del procesador amb iden = identificador al principi de la memoria sense deixar llocs lliures ni solapar processos i respectant l'ordre inicial
     */
     /** \par Cost Lineal */
     void compactar_memoria_procesador(string identificador);

     /**  @brief Modificadora que compacta la memòria de tots els procesadors del cluster
          \pre Cert
          \post A tots els procesadors del cluster s'han mogut tots els processos al principi de la memòria sense deixar llocs lliures ni solapar processos i respectant l'ordre inicial
     */
     /** \par Cost Lineal */
     void compactar_memoria_cluster();

     //Consultores

     /**  @brief Consultroa que retorna el procesador del cluster amb idn = identificador
          \pre identificador es un string no buit i existeix un procesador al cluster amb iden = identificador
          \post El procesador del cluster que te idn = identificador
     */
     /** \par Cost Lineal */
     Procesador consultar_procesador(string identificador);

     /**  @brief Consultora que comprova si existeix un procés
          \pre idn es un string no buit
          \post El resultat indica es cert si existeix un procesador al cluster amb idn = identificador, fals en cas contrari
     */
     /** \par Cost log(n), sent n el numero de procesadors del cluster */
     bool existe_procesador(string idn);

     /**  @brief Consultora que comprova que el procesador amb idn = identificador no tingui procesadors auxiliars
          \pre idn es un string que correspon a l'identificador d'un procesador del cluster
          \post El resultat es cert si el procesador amb idn = identificador no te procesadors auxiliars, fals en cas contrari
     */
     /** \par Cost Lineal */
     bool no_tiene_procesadores_aux(string idn, const BinTree<string>& estruct);

     /**  @brief Consultora que retorna l'estructura del cluster
          \pre Cert
          \post L'estructura del cluster
     */
     /** \par Cost Lineal */
     BinTree<string> consultar_estructura();

     /**  @brief Consultora que retorna els procesadors del cluster
          \pre Cert
          \post El map<string, Procesador> procesadors del cluster
     */
     /** \par Cost Lineal */
     map<string, Procesador> consultar_procesadors();

     //Lectura i escriptura

     /**  @brief comprova si existeix un procesador al cluster amb idn = identificador i, en cas afirmatiu, escriu els seus processos per ordre de posició a memòria, incloent la posició i la resta de la informació de cada procés
          \pre identificador és un string no buit
          \post Si existeix un procesador amb idn = identificador, s'escriuen tots els processos d'aquest per ordre de posició a memòria, incloent la posició de cada procés i la seva informació
     */
     /** \par Cost Lineal */
     void imprimir_procesador(string identificador);

     /**  @brief Escriu tots els procesadors del cluster seguint la funcionalitat imprimir_procesador()
          \pre Cert
          \post Escriu tot els procesadors del cluster per ordre creixent d'identificador seguint la funcionalitat anterior
     */
     /**  \par Cost Lineal */
     void imprimir_procesadores_cluster();

     /**  @brief Escriu l'estructura del cluster
          \pre Cert
          \post Escriu l'estructura de procesadors del cluster
     */
     /**  \par Cost Lineal */
     void imprimir_estructura_cluster(const BinTree<string>& estruct);

};
#endif
