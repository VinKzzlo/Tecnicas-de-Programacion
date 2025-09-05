/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 1 de julio de 2024, 17:16
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <cstring>
#include "FuncionesAuxiliares.h"
#include "Libro.h"

void leerLibros(const char *nombArch,struct Libro *libros,int &numLib){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    char *codigo, *titulo, *autor, c;
    int cantidad, dni, dd,mm,aa, cantUs;
    double precio;
    numLib=0;
    while(true){
        codigo = leerCadenaExacta(arch,',');
        if(arch.eof())break;
        titulo = leerCadenaExacta(arch,',');
        autor = leerCadenaExacta(arch,',');
        arch>>cantidad>>c>>precio>>c;
        libros[numLib].codigo = codigo;
        libros[numLib].titulo = titulo;
        libros[numLib].autor = autor;
        libros[numLib].cantidad = cantidad;
        libros[numLib].precio = precio;
        libros[numLib].usuarios = new struct UsuarioConElLibro[25]{};
        while(true){
            arch>>dni>>c>>dd>>c>>mm>>c>>aa;
            cantUs = libros[numLib].cantUsuarios;
            libros[numLib].usuarios[cantUs].dni = dni;
            libros[numLib].usuarios[cantUs].fechaDeDevolucion = aa*10000 + mm*100 + dd;
            libros[numLib].cantUsuarios++;
            if(arch.get()=='\n') break;
        }
        numLib++;
    }
}

char *leerCadenaExacta(ifstream &arch,char delimitador){
    char buffer[100], *cadena;
    arch.getline(buffer,100,',');
    if(arch.eof())return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}