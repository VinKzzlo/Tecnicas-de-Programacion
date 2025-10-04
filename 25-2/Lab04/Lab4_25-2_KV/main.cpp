/*
 * Proyecto:    Lab4_25-2_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       3/10/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_CANALES 120
#define MAX_ETIQUETAS 120
int main() {
    double tarifa;
    solicitarTarifa(tarifa);

    //Arreglos Canales
    int arrCanalCodNum[MAX_CANALES]{}, arrCanalFechaCreacion[MAX_CANALES]{}, arrCanalPorcentaje[MAX_CANALES]{};
    int arrCanalNumRepro[MAX_CANALES]{}, arrCanalTiempoRepro[MAX_CANALES]{};
    double arrCanalRating[MAX_CANALES]{}, arrCanalIngresos[MAX_CANALES]{};
    char arrCanalCodLetra[MAX_CANALES]{};
    int cantCanales=0;

    cargarArreglosCanales("ArchivosDeDatos/Canales.txt",
        arrCanalFechaCreacion,arrCanalCodNum,arrCanalRating,arrCanalCodLetra,arrCanalPorcentaje,cantCanales);

    //Arreglos Etiquetas
    int arrEtiqCod[MAX_ETIQUETAS]{}, arrEtiqDuracion[MAX_ETIQUETAS];
    int arrEtiqNumRepro[MAX_ETIQUETAS]{}, arrEtiqTiempoRepro[MAX_ETIQUETAS]{};
    int cantEtiquetas=0;
    cargarArreglosEtiquetas("ArchivosDeDatos/Etiquetas.txt",arrEtiqCod,arrEtiqDuracion,cantEtiquetas);

    imprimeReportePrueba("ArchivosDeReportes/ReportePrueba.txt",
                        arrCanalFechaCreacion,arrCanalCodNum,arrCanalRating,arrCanalCodLetra,arrCanalPorcentaje,cantCanales,
                        arrEtiqCod,arrEtiqDuracion,cantEtiquetas);

    procesarReproduccionesEtiquetas("ArchivosDeDatos/ReproduccionesDeEtiquetas.txt",
        arrCanalCodLetra,arrCanalCodNum,arrCanalRating,arrCanalPorcentaje,arrCanalNumRepro,arrCanalTiempoRepro,arrCanalIngresos,cantCanales,
        arrEtiqCod,arrEtiqDuracion,arrEtiqNumRepro,arrEtiqTiempoRepro,cantEtiquetas,tarifa);

    imprimirReporteFinal("ArchivosDeReportes/ReporteFinal.txt",
        arrCanalCodNum,arrCanalFechaCreacion,arrCanalPorcentaje,arrCanalNumRepro,arrCanalTiempoRepro,
        arrCanalRating,arrCanalIngresos,arrCanalCodLetra,cantCanales,
        arrEtiqCod,arrEtiqDuracion,arrEtiqNumRepro,arrEtiqTiempoRepro,cantEtiquetas,tarifa);

    return 0;
}