/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 15 de junio de 2024, 2:03
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void solicitarDatos(int &semestre); 
void leerEscalas(const char *nombArch,struct Escala *escalas,int &numEsc);
void leerCursos(const char *nombArch,struct Curso *cursos,int &numCur);
char* leerCadenaExacta(ifstream &arch,char delimitador);
void leerMatricula(const char *nombArchMat,struct Curso *cursos,
                   int numCur, int semestre,const char *nombArchAlu,
                   struct Escala *escalas,int numEsc);
void actualizarAlumnos(ifstream &archAlu,struct Curso *cursos,int numCur,
                       struct Escala *escalas,int numEsc, int semestre);
int buscarCurso(int codCur,struct Curso *cursos,int numCur);
int buscarEscala(const struct Escala *escalas,int numEsc,char escala,int semestre);
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
void cadenaAMayus(char *nombre);
#endif /* FUNCIONESAUXILIARES_H */

