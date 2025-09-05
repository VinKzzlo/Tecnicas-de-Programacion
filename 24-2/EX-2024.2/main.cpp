/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: aml
 *
 * Created on 3 de julio de 2025, 11:12 AM
 */


#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    struct Palabra arrPalabra[100];
    int cantPalabras,cantPlatos,cantAtenciones;
    struct Plato *arrPlatos;
    struct Atencion arrAtenciones[100]{};
    arrPlatos = new struct Plato [200]{};
    //para el lexicom
    cargarLexicon(arrPalabra,cantPalabras);
    //para los platos
    cargarPlatos(arrPlatos,cantPlatos);
    //actualizar datos
    procesarAtenciones(arrAtenciones,arrPlatos,cantPlatos,cantAtenciones);
    //leer comentarios y obtener polaridad
    leerComentarios(arrAtenciones,cantAtenciones,arrPalabra,cantPalabras);
    emitirReporte(arrAtenciones,cantAtenciones);
    return 0;
}

