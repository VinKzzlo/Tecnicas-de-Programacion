/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 3 de junio de 2024, 16:14
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void solicitarDatos(int &semestre);

void leerDatosAlumnos(const char *nombArch,int *alumnosCods,char **alumnosNomb,
                      char *alumnosEsc,int &numAlu);
void ordenarAlumnos(int *alumnosCods,char **alumnosNomb,
                    char *alumnosEsc,int numAlu);

void leerDatosCursos(const char *nombArch,int *cursosCods,double *cursosCreds,
                     int &numCur);
void ordenarCursos(int *cursosCods,double *cursosCreds, int numCur);

void leerDatosEscalas(const char *nombArch,int *escalasSemestre,
                      double *escalasPrecio, char *escalasLetra,int &numEsc);

void procesarMatricula(const char *nombArch,int semestre,
                      int *alumnosCods,char **alumnosNomb,
                      char *alumnosEsc,int numAlu,
                      int *cursosCods,double *cursosCreds, int numCur,
                      int *escalasSemestre, double *escalasPrecio, 
                      char *escalasLetra,int numEsc,
                      int *alumnosNroCur,double *alumnosCreds,double *alumnosPago);

void cambiarInt(int &datoI,int &datoJ);
void cambiarDbl(double &datoI,double &datoJ);
void cambiarStr(char *&cadenaI,char *&cadenaJ);
void cambiarChr(char &datoI,char &datoJ);

char *leerCadenaExacta(ifstream &arch,char delimitador);
void modificarCadena(char *cadena);

#endif /* FUNCIONESAUXILIARES_H */

