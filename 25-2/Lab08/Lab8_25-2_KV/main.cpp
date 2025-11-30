/*
 * Proyecto:    Lab8_25-2_KV
 * Archivo:     
 * Autor:       VinKzzlo
 * Fecha:       18/11/2025
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Estructuras/Reproduccion.h"
#include "Estructuras/Categoria.h"
#include "Bibliotecas/FuncionesAuxiliares.h"

#define MAX_CATEGORIAS 120
int main() {
    int cantidadCategorias;
    struct Categoria *arrCategorias = new struct Categoria[MAX_CATEGORIAS]{};

    cargarCategorias("ArchivosDeDatos/categorias.csv",arrCategorias,cantidadCategorias);
    imprimeReportePorCategorias("ArchivosDeReporte/ReporteDePruebaDeCategorias.txt",arrCategorias,cantidadCategorias);
    cargarReproduccionesEnCats("ArchivosDeDatos/StreamsReproducidos.csv",arrCategorias,cantidadCategorias);
    imprimeReportePorCategorias("ArchivosDeReporte/ReporteDePruebaConReproducciones.txt",arrCategorias,cantidadCategorias);
    ordenarArreglosPorNombreCategoria(arrCategorias,cantidadCategorias);
    imprimeReportePorCategorias("ArchivosDeReporte/ReporteDePruebaOrdenado.txt",arrCategorias,cantidadCategorias);
    cargarComentarios("ArchivosDeDatos/ComentariosAlCanal.csv",arrCategorias,cantidadCategorias);
    imprimeReportePorCategorias("ArchivosDeReporte/ReporteDePruebaConComentarios.txt",arrCategorias,cantidadCategorias);

    return 0;
}