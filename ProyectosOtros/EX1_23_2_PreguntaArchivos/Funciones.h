/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Funciones.h
 * Author: USUARIO
 *
 * Created on 12 de mayo de 2024, 10:15
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void emitirReporte(const char*nombArchAlumnos, const char*nombArchCursos, 
                   const char*nombArchEscalas, const char*nombArchMatriculas,
                   const char*nombArchRep);
void leerNombre(ifstream &archAlumnos, ofstream &archRep);
void imprimirEncabezado(ofstream &archRep);
void imprimeLinea(char c, int n, ofstream &archRep);
void imprimirEncabezado2(ofstream &archRep);
void leerNombreCurso(ifstream &archCursos, ofstream &archRep);
void lecturaVariable(ifstream &archMatri, ofstream &archRep, ifstream &archCursos);
void leerMatricula(int codigo, ifstream &archMatri,ifstream &archCursos, ofstream &archRep);
void buscarCursoMatri(ifstream &archCursos, ofstream &archRep, int codigoCursos);
#endif /* FUNCIONES_H */

