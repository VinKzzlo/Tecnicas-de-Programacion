/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   FuncionesAuxiliares.h
 * Author: Alessandro Salvador Santé Vega - 20223006
 *
 * Created on 10 de junio de 2024, 07:22 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerCalificaciones(const char *nombArch,
                        struct Alumno *arrAlumnos,int &numAlu); 
int buscarAlumno(int codAlu,struct Alumno *arrAlumnos,int numAlu);
void insertarDatos(int codAlu,double creditos,int nota,
                  struct Alumno *arrAlumnos,int &numAlu);
void actualizarDatos(double creditos,int nota,struct Alumno *arrAlumnos,int pos);
void actualizarPromedios(struct Alumno *arrAlumnos,int numAlu);

void leerAlumnos(const char *nombArch,
                 struct Alumno *arrAlumnos,int numAlu);
void leerFacultades(const char *nombArch,
                    struct Alumno *arrAlumnos,int numAlu);
void modificarCadena(char *nombFacu);

void emitirReporte(const char *nombArch,
                    struct Alumno *arrAlumnos,int numAlu);
void imprimeEncabezado(ofstream &arch);
void imprimeLinea(ofstream &arch,char car);
#endif /* FUNCIONESAUXILIARES_H */

