/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 17 de junio de 2024, 17:34
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void solicitarDatos(int &semestre);
void leerEscalas(const char *nombArch,struct Escala *escalas,int &numEsc);
void leerCursos(const char *nombArch,struct Curso *cursos,int &numCur);
void actualizarMatricula(const char *nombArchMat,int semestre,
                         struct Escala *escalas, int numEsc,
                         struct Curso *cursos,int numCur, const char *nombArchAlu);
void actualizarAlumnos(ifstream &archAlu,struct Curso *cursos,int numCur,
                       struct Escala *escalas, int numEsc,int semestre);
int buscarCurso(int codCur,struct Curso *cursos,int numCur);
int buscarEscala(char escala,struct Escala *escalas,int numEsc,int semestre);
char *leerCadenaExacta(ifstream &arch,char delimitador);
void modificarCadena(char *nombre);
void ordenarDatos(struct Curso *cursos,int numCur);
void ordenarCursos(struct Curso *cursos,int numCur);
void ordenarAlumnos(struct Alumno *alumnos,int numAlu);
void cambiarCursos(struct Curso &cursoI, struct Curso &cursoJ);
void cambiarAlumnos(struct Alumno &alumnoI,struct Alumno &alumnoJ);
void emitirReporte(const char *nombArch,int semestre,
                   struct Curso *cursos,int numCur);
void imprimirAlumnosMatriculados(ofstream &arch,struct Alumno *alumnos,
                                 int numAlu, double creditos);
void imprimeEncabezado(ofstream &arch,int semestre);
void imprimeLinea(ofstream &arch,char c);
#endif /* FUNCIONESAUXILIARES_H */

