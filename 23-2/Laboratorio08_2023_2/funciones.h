/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 *
 * Created on 6 de noviembre de 2023, 07:08 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void solicitarDatos(int &ciclo);
void cargarAlumnos(struct Alumno *arrAlumnos, int &cantAlumnos);
void cargarCursos(struct Curso *arrCursos, int &cantCursos);
void cargarEscalas(struct Escala *arrEscalas, int &cantEscalas);
void actualizarMatricula(const struct Alumno *arrAlumnos, int cantAlumnos, struct Curso *arrCursos,
        int cantCursos, const struct Escala *arrEscalas, int cantEscalas, int ciclo);
int buscarAlumno(const struct Alumno *arrAlumnos, int cantAlumnos, int alumno);
int buscarEscala(const struct Escala *arrEscalas, int cantEscalas, int ciclo, char escala);
int buscarCurso(const struct Curso *arrCursos, int cantCursos, int curso);
void ordenarDatos(struct Curso *arrCursos, int cantCursos);
void cambiarEstructuras(struct Curso &cursoI, struct Curso &cursoJ);
void emitirReporte(const struct Curso *arrCursos, int cantCursos, int ciclo);
void imprimirLinea(char simbolo, int cant, ofstream &archReporte);


#endif /* FUNCIONES_H */

