/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 * Author: 51969
 *
 * Created on 8 de mayo de 2024, 22:51
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void cargardatosmedicos(int *arrmedicos, double *arrtarifa, int *arrpacmed, int *arrpac
, double *arringreso, double *arringresomed, int &cantmedicos);
void cargardatosmedicinas(int *arrmedicinas, double *arrprecio, int* arrcant, 
        double *arringreso, double *arrdescuento, int &cantmedicinas);
void cargarcitas(int *arrmedicos, double *arrtarifa, int *arrpacmed, int *arrpac
        , double *arringreso, double *arringresomed, int cantmedicos,
        int *arrmedicinas, double *arrprecio, int *arrcant, 
        double *arringresomedmed, double *arrdescuento, int cantmedicinas);
int buscararrint(int cod, int *arrcod, int cant);
void reportedeingreso(int *arrmedicos, double *arrtarifa, int *arrpacmed, int *arrpac
        , double *arringreso, double *arringresomed, int &cantmedicos, ofstream &archReporte);
#endif /* FUNCIONES_H */

