/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 27 de mayo de 2024, 13:57
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void solicitarDatos(int &anio,int &ciclo);

void leerAlumnos(const char *nombArch, int *alumnoCods,
                 char *alumnoEsc, int &cantAlu);
void insertarOrdenado(int *alumnoCods,char *alumnoEsc,
                      int codigo,char escala,int &cantAlu);

void leerCursos(const char *nombArch,int *cursosCods,
                double *cursosCreds, int &cantCur);
void insertarCurOrd(int *cursosCods,double *cursosCreds,int &cantCur,
                    int codigo,double creditos);

void leerEscalas(const char *nombArch,int *escSemestre,double *escCostoXCred,
                 char *escLetra,int &cantEsc);
void insertarEscOrd(int *escSemestre,double *escCostoXCred,char *escLetra,
                    int &cantEsc,int semestre,char escala,double costo);

void updateTotalAlu(const char *nombArch,int semestre,
                    int *alumnoCods, char *alumnoEsc, int cantAlu,
                    int *cursosCods, double *cursosCreds, int cantCur,
            int *escSemestre,double *escCostoXCred, char *escLetra,int cantEsc,
            int *alumnoNroCurs,double *alumnoCredsMat,double *alumnoMontoPaga);
int busquedaBinaria(int *arreglo,int dato,int cantidad);
int buscarEscala(int semestre,char alumnoEsc,int *escSemestre,char *escLetra,
                 int cantEsc);

void emitirReporte(const char *nombArchNomb,const char *nombArchApell,
                  const char *nombArchRep,int semestre,
                  int *alumnoCods,int *alumnoNroCurs,double *alumnoCredsMat,
                  char *alumnoEsc,double *alumnoMontoPaga,int cantAlu);
void imprimePorAlumno(ifstream &archNomb,ifstream &archApell,ofstream &archRep,
                      int *alumnoCods,int *alumnoNroCurs,double *alumnoCredsMat,
                      char *alumnoEsc,double *alumnoMontoPaga,int cantAlu);
void modificaTexto(const char *apellidoMat,const char *apellidoPat_Nomb,
                   char *nombreCompleto);
int longitud(const char *arreglo);
void copiar(char *destino, const char *fuente);
void agregaEspaciosYPasaMayus(char *arreglo);

void imprimeEncabezado(ofstream &archRep,int semestre);
void imprimeLinea(ofstream &archRep,char c);

#endif /* FUNCIONESAUXILIARES_H */


