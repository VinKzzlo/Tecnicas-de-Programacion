/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: 51969
 *
 * Created on 8 de mayo de 2024, 22:44
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
#include "funciones.h"
#define MEDICOS 40
#define MEDICINAS 211

/*
 * 
 */
int main(int argc, char** argv) {
    int  arrmedicos[MEDICOS], arrpacmed[MEDICOS], arrpac[MEDICOS], cantmedicos=0,
            arrmedicinas[MEDICINAS], arrcant[MEDICINAS], cantmedicinas=0;
    double arrtarifa[MEDICOS], arringreso[MEDICOS], arringresomed[MEDICOS],
            arrprecio[MEDICINAS], arrdescuento[MEDICINAS], arringresomedmed[MEDICINAS];
    cargardatosmedicos(arrmedicos, arrtarifa, arrpacmed, arrpac
    , arringreso, arringresomed, cantmedicos);
    cargardatosmedicinas(arrmedicinas, arrprecio, arrcant, 
         arringresomedmed, arrdescuento, cantmedicinas);
    cargarcitas(arrmedicos, arrtarifa, arrpacmed, arrpac
        , arringreso, arringresomed, cantmedicos,
        arrmedicinas, arrprecio, arrcant, 
        arringresomedmed, arrdescuento, cantmedicinas);
    ofstream archReporte("ReporteDeIngresos.txt", ios::out);
    reportedeingreso(arrmedicos, arrtarifa, arrpacmed, arrpac
        , arringreso, arringresomed, cantmedicos, archReporte);
    return 0;
}

