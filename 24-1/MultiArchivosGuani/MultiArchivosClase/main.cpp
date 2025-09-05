/* 
 * Archivo:   main.cpp
 * Autor:     VinKzzlo
 *
 * Creado el 21 de abril de 2024, 18:53
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesReporte.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    emitirReporteDeFacturas("Clientes.txt","Facturas.txt","Productos.txt",
                            "ReporteDeFacturas.txt");
            
    return 0;
}

