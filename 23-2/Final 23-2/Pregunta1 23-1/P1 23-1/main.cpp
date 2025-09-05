/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 1 de julio de 2024, 16:33
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "Libro.h"
/*
 * 
 */
int main(int argc, char** argv) {
    struct Libro libros[50]{};
    int numLib;
    leerLibros("Libros.csv",libros,numLib);
    return 0;
}

