/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 10 de junio de 2024, 17:17
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void solicitarDatos(int &anio,int &ciclo);
void leerAlumnos(const char *nombArch,struct Alumno *alumnos,int &numAlu);
void leerCursos(const char *nombArch,struct Curso *cursos,int &numCur);
void leerEscalas(const char *nombArch,struct Escala *escalas,int &numEsc);
void updateCursos(const char *nombArch,struct Alumno *alumnos,int numAlu,
             struct Curso *cursos,int numCur,struct Escala *escalas,int numEsc,int semestre);
int buscarAlumno(int codAlumno,struct Alumno *alumnos,int numAlu);
int buscarEscala(int semestre,char escala, struct Escala *escalas, int numEsc);
#endif /* FUNCIONESAUXILIARES_H */

