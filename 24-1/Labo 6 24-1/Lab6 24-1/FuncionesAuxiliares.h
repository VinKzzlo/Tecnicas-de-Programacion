/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 1 de junio de 2024, 1:14
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void solicitarDatos(int &facultad);
void cargarCalif(const char *nombArch, int *arrCodigoAlumnos,int *arrNumCursos,
                         double *arrSumaPonderada,double *arrNumCreditos,
                         int &cantAlu);
void leerNotas(ifstream &arch,double creditos,int *arrCodigoAlumnos,int *arrNumCursos,
               double *arrSumaPonderada, double *arrNumCreditos, int &cantAlu);
int buscarAlumno(int codigo,int *arrCodigoAlumnos,int cantAlu);
void insertarOrdenado(int codigo,double creditos, int nota,
                      int *arrCodigoAlumnos,int *arrNumCursos,
                      double *arrSumaPonderada, double *arrNumCreditos,
                      int &cantAlu);
void actualizarArreglos(double creditos,int nota,int &numCursos,
                        double &sumaPonderada,double &numCreditos);
void emitirReporte(const char *nombArchAlu,const char *nombArchFac,const char *nombArchRep,
                   int *arrCodigoAlumnos,int *arrNumCursos,
                   double *arrSumaPonderada,double *arrNumCreditos,
                   int cantAlu,int facultad);
void imprimeAlumnos(int facultad,ifstream &archAlu,ofstream &archRep,
                   int *arrCodigoAlumnos,int *arrNumCursos,
                   double *arrSumaPonderada,double *arrNumCreditos,int cantAlu);


void imprimeEncabezado(ifstream &archFac,ofstream &archRep,int facultad);
void imprimeLinea(ofstream &archRep,char c);

void modificarNombre(char *nombAlu,char *nombModAlu);
void quitaEspacios(char *nombre);
int longitud(char *nombre);
#endif /* FUNCIONESAUXILIARES_H */

