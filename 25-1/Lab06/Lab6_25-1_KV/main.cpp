/*
 * Proyecto:    Lab6_25-1_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       1/11/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_INFRACCIONES 150
#define MAX_REPRESENTANTES 660


int main() {

    int arrCodigoInfraccion[MAX_INFRACCIONES]{}, cantInfracciones=0;
    double arrMultasInfraccion[MAX_INFRACCIONES]{};

    leerTablaInfraccioness("ArchivosDeDatos/TablaDeInfracciones.txt", arrCodigoInfraccion,arrMultasInfraccion,cantInfracciones);
    comprobarLecturaInfracciones("ArchivosDeReportes/PruebaInfracciones.txt",arrCodigoInfraccion,arrMultasInfraccion,cantInfracciones);

    int arrDni[MAX_REPRESENTANTES]{}, arrMasMultaAntigua[MAX_REPRESENTANTES]{}, arrUltimaPendiente[MAX_REPRESENTANTES]{};
    double arrTotalMultas[MAX_REPRESENTANTES]{}, arrTotalPagadas[MAX_REPRESENTANTES]{}, arrTotalPendientes[MAX_REPRESENTANTES]{};
    int cantRepresentantes=0;

    leerInfraccionesCometidas("ArchivosDeDatos/InfraccionesCometidas.txt","ArchivosDeReportes/PlacasRegistradas.txt",
        arrCodigoInfraccion,arrMultasInfraccion,cantInfracciones,
        arrDni, arrMasMultaAntigua,arrUltimaPendiente,arrTotalMultas,arrTotalPagadas,arrTotalPendientes,cantRepresentantes);


}