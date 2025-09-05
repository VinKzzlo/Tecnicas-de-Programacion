/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 1 de julio de 2024, 17:16
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerLibros(const char *nombArch,struct Libro *libros,int &numLib);
char *leerCadenaExacta(ifstream &arch,char delimitador);
#endif /* FUNCIONESAUXILIARES_H */

