
// File:   funciones.h
// Author: superflash41

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerCalificaciones(const char* , int* , int* , double* , double* , int& );
void leerNotas(ifstream& , double , int* , int* , double* , double* , int& );
int buscarCod(int , int* , int , int );
void actualizarArreglos(int , double , int& , double& , double& );
void insertarOrdenado(int , int , double , int* , int* , double* , double* , int& );
void generarReporte(const char* , const char* , const char* , 
        int* , int* , double* , double* , int );
void imprimirFacultad(ifstream& , ofstream& , int ) ;
void imprimirNombreFacultad(ofstream& , char* );
void imprimirDatosAlumnos(ifstream& , ofstream& , int , 
        int* , int* , double* , double* , int );
void procesarNombre(char* , char* );
void uncap(char& );
#endif /* FUNCIONES_H */

