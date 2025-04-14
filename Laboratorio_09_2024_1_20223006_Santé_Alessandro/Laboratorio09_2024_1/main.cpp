/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Alessandro Salvador Santé Vega - 20223006
 *
 * - Descripción del programa-
 * Programa que procesa los datos de una librería contenidos en tres archivos:
 * Los libros que vende, los clientes y un registro de ventas.
 * A partir de esos datos se busca emitir un reporte de ventas por libro,
 * con la lista de los clientes que lo compraron y la calificacion que le dieron.
 * Created on 17 de junio de 2024, 07:10 PM
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "Libro.h"
#include "Cliente.h"
/*
 * 
 */
int main(int argc, char** argv) {
    struct Cliente *arrClientes;
    arrClientes = new struct Cliente[70];
    struct Libro *arrLibros;
    arrLibros = new struct Libro[300]{};//Inicializamos pues la estructura contiene algunos valores acumulativos
    int numClientes, numLibros;
    leerClientes("Clientes.csv",arrClientes,numClientes);
    leerLibros("Libros.csv",arrLibros,numLibros);
    actualizarVentas("Ventas.csv",arrLibros,numLibros);
    ordenarLibros(arrLibros,numLibros);
    emitirReporte("ReporteDePagoPorAlumno.txt",arrLibros,numLibros,
                  arrClientes,numClientes);
    return 0;
}

