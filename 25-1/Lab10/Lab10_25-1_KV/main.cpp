/*
 * Proyecto:    Lab10_25-1_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       24/11/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    struct Nodo *lista;

    crearListaOrdenada("ArchivosDeDatos/CuentasBancarias.csv", lista);
    //mostrarLista("ArchivosDeReportes/waza.txt",lista);
    registrarMovimientos("ArchivosDeDatos/MovimientosDeCuentas.csv",lista);
    emiteReporteSaldos("ArchivosDeReportes/ReporteDeSaldosFinales.txt", lista);
}