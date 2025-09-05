/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 29 de junio de 2024, 23:07
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
/*
 * 
 */
int main(int argc, char** argv) {
    crearClientesBIN("Clientes.csv","Clientes.bin");
    crearLibrosBIN("Libros.csv","Libros.bin");
    actualizarLibrosConVentas("Ventas.csv","Clientes.bin","Libros.bin");
    ordenarLibros("Libros.bin");
//    mostrarClientesBIN("Clientes.bin");
//    mostrarLibrosBIN("Libros.bin","Libros.txt");
    emitirReporte("Libros.bin","ReporteDePago.txt");
    return 0;
}

