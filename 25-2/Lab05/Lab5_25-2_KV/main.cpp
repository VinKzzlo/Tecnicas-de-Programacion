/*
 * Proyecto:    Lab5_25-2_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       6/10/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_CANALES 120
#define MAX_ETIQUETAS 120
#define MAX_ETIQUETAS 120
#define MAX_ETIQENCAN 600
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    int arrCanalCodNum[MAX_CANALES], cantCanales=0;
    double arrCanalRating[MAX_CANALES];
    char arrCanalCodLet[MAX_CANALES];
    double tarifa;
    solicitaTarifa(tarifa);

    cargarCanales("ArchivosDeDatos/Canales.txt",arrCanalCodNum,arrCanalCodLet,arrCanalRating,cantCanales);

    int arrEtiquetaCod[MAX_ETIQUETAS], arrEtiquetaDuracion[MAX_ETIQUETAS],cantEtiquetas=0;

    cargarEtiquetas("ArchivosDeDatos/Etiquetas.txt", arrEtiquetaCod,arrEtiquetaDuracion,cantEtiquetas);

    int arrEtiqCanNumCanal[MAX_ETIQENCAN], arrEtiqCanCodEtiqueta[MAX_ETIQENCAN], cantEtiquetasEnCanales=0;
    int arrEtiqCanTotalRep[MAX_ETIQENCAN]{}, arrEtiqCanTiempoTotal[MAX_ETIQENCAN]{};
    char arrEtiqCanLetCanal[MAX_ETIQENCAN];

    cargarEtiquetasEnCanales("ArchivosDeDatos/EtiquetasEnCanales.txt", arrEtiqCanNumCanal,arrEtiqCanLetCanal,
        arrEtiqCanCodEtiqueta,cantEtiquetasEnCanales);

    imprimeReporteSimple("ArchivosDeReportes/ReportePrueba.txt", arrCanalCodNum,arrCanalCodLet,arrCanalRating,cantCanales,
        arrEtiquetaCod,arrEtiquetaDuracion,cantEtiquetas,
        arrEtiqCanNumCanal,arrEtiqCanLetCanal,arrEtiqCanCodEtiqueta,cantEtiquetasEnCanales);

    ordenarEtiquetas(arrEtiquetaCod,arrEtiquetaDuracion,cantEtiquetas);

    acumulaReproducciones("ArchivosDeDatos/ReproduccionesDeEtiquetas.txt",arrEtiqCanTotalRep,arrEtiqCanTiempoTotal,
        arrEtiqCanNumCanal,arrEtiqCanLetCanal,arrEtiqCanCodEtiqueta,cantEtiquetasEnCanales,
        arrCanalCodNum,arrCanalCodLet,cantCanales,
        arrEtiquetaCod,arrEtiquetaDuracion,cantEtiquetas);

    imprimeReporteFinal("ArchivosDeReportes/ReporteDeCanalesYEtiquetas.txt",
        arrCanalCodNum,arrCanalCodLet,arrCanalRating,cantCanales,
        arrEtiquetaCod,arrEtiquetaDuracion,cantEtiquetas,
        arrEtiqCanTotalRep,arrEtiqCanTiempoTotal,
        arrEtiqCanNumCanal,arrEtiqCanLetCanal,arrEtiqCanCodEtiqueta,cantEtiquetasEnCanales,tarifa);

}