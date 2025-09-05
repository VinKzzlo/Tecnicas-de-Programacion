/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 30 de junio de 2024, 20:36
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "Articulo.h"
#include "ArticuloPedido.h"
#include "Vendedor.h"
/*
 * 
 */
int main(int argc, char** argv) {
    int numArt, numVend;
    struct Articulo *articulos;
    articulos = new struct Articulo[200]{};
    leerArticulos("Articulos.csv",articulos,numArt);
    mostrarArticulos(articulos,numArt,"PruebaArticulos.txt");
    struct Vendedor *vendedores;
    vendedores = new struct Vendedor[150]{};
    leerVendedores("Vendedores.csv",vendedores,numVend);
    mostrarVendedores(vendedores,numVend,"PruebaVendedores.txt");
    leerVentas("Ventas.txt",articulos,numArt,vendedores,numVend);
    mostrarArticulos(articulos,numArt,"ReporteArticulos.txt");
    mostrarVendedores(vendedores,numVend,"ReporteVentas.txt");
    return 0;
}

