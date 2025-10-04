/*
 * Proyecto:    Lab2_25-2_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       18/09/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    int fechaIni, fechaFin;
    double tarifaPubli, tarifaDuracion;

    solicitaFechasYTarifas(fechaIni,fechaFin,tarifaPubli,tarifaDuracion);
    procesaImprimeRegistroCanalesAfiliados("ArchivosDeDatos/twitchdataTP.txt","ArchivosDeReportes/ReporteTwitch.txt",
                                            fechaIni,fechaFin,tarifaPubli,tarifaDuracion);

    return 0;
}