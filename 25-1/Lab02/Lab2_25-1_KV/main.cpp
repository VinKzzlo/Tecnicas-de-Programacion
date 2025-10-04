/*
 * Proyecto:    Lab2_25-1_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       15/09/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    imprimeReporteMultasCompanias("ArchivosDeDatos/InfraccionesCometidas.txt",
        "ArchivosDeDatos/InfraccionesDeTransito.txt","ArchivosDeReportes/ReporteMultas.txt");


    return 0;
}