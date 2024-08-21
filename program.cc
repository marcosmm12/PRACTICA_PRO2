/** @file program.cc
    @brief Codi principal del programa
*/

#include "Cluster.hh"
#include "Sala_espera.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <list>
#include <iostream>
#endif

using namespace std;

int main() {
    Cluster cluster;
    cluster.configurar_cluster();
    int num_prioridades;
    cin >> num_prioridades;
    Sala_espera sala_espera(num_prioridades);
    string comando;
    cin >> comando;
    while (comando != "fin") {
        if ((comando == "configurar_cluster") or (comando == "cc")) {
            cout << "#" << comando << endl;
            cluster.configurar_cluster();
        }
        else if ((comando == "modificar_cluster") or (comando == "mc")) {
            string identificador;
            cin >> identificador;
            cout << "#" << comando << ' ' << identificador << endl;
            cluster.modificar_cluster(identificador);
        }
        else if ((comando == "alta_prioridad") or (comando == "ap")) {
            string identificador;
            cin >> identificador;
            cout << "#" << comando << ' ' << identificador << endl;
            sala_espera.alta_prioridad(identificador);
        }
        else if ((comando == "baja_prioridad") or (comando == "bp")) {
            string identificador;
            cin >> identificador;
            cout << "#" << comando << ' ' << identificador << endl;
            sala_espera.baja_prioridad(identificador);
        }
        else if ((comando == "alta_proceso_espera") or (comando == "ape")) {
            string identificador;
            cin >> identificador;
            Proceso p;
            p.leer_proceso();
            cout << "#" << comando << ' ' << identificador << ' '  << p.consultar_iden() << endl;
            sala_espera.alta_proceso_espera(identificador, p);
        }
        else if ((comando == "alta_proceso_procesador") or (comando == "app")) {
            string identificador;
            cin >> identificador;
            Proceso p;
            p.leer_proceso();
            cout << "#" << comando << ' ' << identificador << ' ' << p.consultar_iden() << endl;
            cluster.alta_proceso_procesador(identificador, p);
        }
        else if ((comando == "baja_proceso_procesador") or (comando == "bpp")) {
            string identificador;
            cin >> identificador;
            int identificador_job;
            cin >> identificador_job;
            cout << "#" << comando << ' ' << identificador << ' ' << identificador_job << endl;
            cluster.baja_proceso_procesador(identificador, identificador_job);
        }
        else if ((comando == "enviar_procesos_cluster") or (comando == "epc")) {
            int n;
            cin >> n;
            cout << "#" << comando << ' ' << n << endl;
            sala_espera.enviar_procesos_cluster(n, cluster);
        }
        else if ((comando == "avanzar_tiempo") or (comando == "at")) {
            int t;
            cin >> t;
            cout << "#" << comando << ' ' << t << endl;
            cluster.avanzar_tiempo(t);
        }
        else if ((comando == "imprimir_prioridad") or (comando == "ipri")) {
            string identificador;
            cin >> identificador;
            cout << "#" << comando << ' ' << identificador << endl;
            sala_espera.imprimir_prioridad(identificador);
        }
        else if ((comando == "imprimir_area_espera") or (comando == "iae")) {
            cout << "#" << comando << endl;
            sala_espera.imprimir_area_espera();
        }
        else if ((comando == "imprimir_procesador") or (comando == "ipro")) {
            string identificador;
            cin >> identificador;
            cout << "#" << comando << ' ' << identificador << endl;
            cluster.imprimir_procesador(identificador);
        }
        else if ((comando == "imprimir_procesadores_cluster") or (comando == "ipc")) {
            cout << "#" << comando << endl;
            cluster.imprimir_procesadores_cluster();
        }
        else if ((comando == "imprimir_estructura_cluster") or (comando == "iec")) {
            cout << "#" << comando << endl;
            cluster.imprimir_estructura_cluster(cluster.consultar_estructura());
            cout << endl;
        }
        else if ((comando == "compactar_memoria_procesador") or (comando == "cmp")) {
            string identificador;
            cin >> identificador;
            cout << "#" << comando << ' ' << identificador << endl;
            cluster.compactar_memoria_procesador(identificador);
        }
        else if ((comando == "compactar_memoria_cluster") or (comando == "cmc")) {
            cout << "#" << comando << endl;
            cluster.compactar_memoria_cluster();
        }
        cin >> comando;
    }
}
