/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 23 de junio de 2024, 15:38
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "Vendedor.h"
#include "Articulo.h"
/*
 * 
 */
int main(int argc, char** argv) {
    leerArticulosAlmacenaBIN("Articulos.csv","Articulos.bin");
    leerVendedoresAlmacenaBIN("Vendedores.csv","Vendedores.bin");
    actualizarVentas("Articulos.bin","Vendedores.bin","Ventas.txt");
    corregirVendedores("Vendedores.bin");
    ordenarVendedores("Vendedores.bin");
    mostrarArchivoBinarioArt("Articulos.bin");
    mostrarArchivoBinarioVend("Vendedores.bin");
    emitirReporte("Articulos.bin","Vendedores.bin","ReporteDePagos.txt");
    return 0;
}

