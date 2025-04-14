/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 12 de mayo de 2024, 12:06
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerCicloEvaluar(int &year,int &ciclo);
void generarReporte(int year,int ciclo,const char *nombArchAlu,
                    const char *nombArchCur, const char *nombArchEsc,
                    const char *nombArchMatr,const char *nombArchRep);

void imprimeMatriculaAlumno(int codigoAlu,int aaMat,int cicloMat,
                            ifstream &archMatr,ifstream &archAlu,
                            ifstream &archCur,ifstream &archEsc,ofstream &archRep,
                            double &totalPagado);

void imprimeAlumnoRetornaEscala(int codigoAlu,ifstream &archAlu,
                                ofstream &archRep,char &escalaLetra);
double determinaCostoPorCreditoEscala(int aaMat,int cicloMat,char escalaLetra,
                                      ifstream &archEsc);

void imprimeEncabezadoCursos(ofstream &archRep);
void imprimeCursoYMonto(int codCurso,int cantCur,double escala,
                        ifstream &archCur,ofstream &archRep,
                        double &creditos, double &monto);

void imprimeNombres(ifstream &archLectura,ofstream &archRep,char seleccion);
void imprimeEncabezado(ofstream &archRep, int year, int ciclo);
void imprimeLinea(ofstream &archRep,char caracter);

#endif /* FUNCIONESAUXILIARES_H */

