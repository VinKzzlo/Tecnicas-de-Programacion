/*
 * Proyecto:    Lab6_25-1_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       3/11/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX_CATEGORIAS 120
#define MAX_STREAMS 420
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    char *arrCategoriaCodigo[MAX_CATEGORIAS]{}, *arrCategoriaNombre[MAX_CATEGORIAS]{};
    int cantCategorias=0;

    cargarCategorias("ArchivosDeDatos/Categorias.txt",arrCategoriaCodigo,arrCategoriaNombre,cantCategorias);
    verificarCategorias("ArchivosDeReportes/ReporteDePruebaDeCategorias.txt", arrCategoriaCodigo,arrCategoriaNombre,cantCategorias);


    int arrStreamFecha[MAX_STREAMS]{}, arrStreamDuracion[MAX_STREAMS]{}, cantStreams=0;
    char *arrStreamNombCanal[MAX_STREAMS]{}, *arrStreamCodCategoria[MAX_STREAMS];
    double arrStreamRating[MAX_STREAMS]{}, arrStreamTasaDrop[MAX_STREAMS]{};
    cargarStreams("ArchivosDeDatos/Reproducciones.txt", arrStreamFecha, arrStreamDuracion,
        arrStreamNombCanal,arrStreamCodCategoria, arrStreamRating,arrStreamTasaDrop,cantStreams);
    verificarStreams("ArchivosDeReportes/ReporteDePruebaDeStreamsReproducidos.txt", arrStreamFecha, arrStreamDuracion,
        arrStreamNombCanal, arrStreamCodCategoria, arrStreamRating,arrStreamTasaDrop,cantStreams);

    emitirReportesCategoriasStreams(arrCategoriaCodigo,arrCategoriaNombre,cantCategorias,
        arrStreamFecha, arrStreamDuracion, arrStreamNombCanal, arrStreamCodCategoria,
        arrStreamRating, arrStreamTasaDrop,cantStreams);


}