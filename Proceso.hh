/** @file Proceso.hh
    @brief Especificació de la classe Proceso
*/

#ifndef Proceso_HH
#define Proceso_HH
using namespace std;

#ifndef NO_DIAGRAM
#include <iostream>
#endif

/*
 * Classe Proceso
 */

/** @class Proceso
    @brief Conté l'identificador del procés, la memòria que ocupa i el temps que triga en executar-se.

    Conté la seva constructora, les funcions consultores i les de lectura i escriptura.
*/
class Proceso {

private:
    /** @brief Identificador del proces */
    int iden;
    /** @brief Memoria que ocupa el proces */
    int memoria;
    /** @brief Temps que triga en executar-se el proces */
    int tiempo;

public:

    //Constructores

    /** @brief Constructora per defecte
        \pre Cert
        \post El resultat és un proces buit
        \par Cost Constant
    */
    Proceso();

    //Modificadores

    /** @brief Modificadora que resta al temps que falta perquè el procés acabi d'executar-se t unitats
        \pre t és un enter positiu
        \post tiempo es veu reduït en t unitats
        \par Cost Constant
    */
    bool restar_tiempo(int t);

    //Consultores

    /** @brief Consultora que retorna el temps que falta perquè acabi d'executar-se el procés
        \pre Cert
        \post El resultat és l'enter tiempo
        \par Cost Constant
    */
    int consultar_tiempo();

    /** @brief Consultora que retorna la memòria que ocupa el procés
        \pre Cert
        \post El resultat és l'enter memoria
        \par Cost Constant
    */
    int consultar_memoria();

    /** @brief Consultora que retorna l'identificador del procés
        \pre Cert
        \post El resultat és l'enter iden
        \par Cost Constant
    */
    int consultar_iden();

    //Lectura i escriptura

    /** @brief Llegeix l'identificador, la memòria que ocupa i el temps que triga en executar-se un procés
        \pre Cert
        \post Llegeix els enters iden, memoria i tiempo
        \par Cost Constant
    */
    void leer_proceso();

    /** @brief Escriu l'identificador, la memòria que ocupa i el temps que falta perquè acabi d'executar-se un procés
        \pre Cert
        \post Escriu iden, tiempo i memoria
        \par Cost Constant
    */
    void imprimir_proceso() const;

};
#endif
