/*
 * Proyecto:    Ex1P1_25-2_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       19/10/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    procesarReproduccionesDeStreams("ArchivosDeDatos/Streams.txt","ArchivosDeDatos/Categorias.txt",
        "ArchivosDeDatos/Idiomas.txt","ArchivosDeDatos/Canales.txt",
        "ArchivosDeReportes/ReporteDeReproduccionDeStreams.txt");
    return 0;
}