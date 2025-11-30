/*
 * Proyecto:    Lab9_25-2_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       25/11/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Bibliotecas/Nodo.h"
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    struct Nodo *lista;

    cargarCategorias("ArchivosDeDatos/Categorias.csv",lista);
    emiteReportePorCategorias("ArchivosDeReportes/ReporteDePruebaDeCategorias.txt",lista);
    actualizarCategoriasConReproducciones("ArchivosDeDatos/StreamsReproducidos.csv",lista);
    calcularPromediosDeDropOff(lista);
    emiteReportePorCategorias("ArchivosDeReportes/ReporteDeCategoriasCompleto.txt",lista);
    eliminarNodos(lista);
    emiteReportePorCategorias("ArchivosDeReportes/ReporteDeCategoriasEliminados.txt",lista);
}