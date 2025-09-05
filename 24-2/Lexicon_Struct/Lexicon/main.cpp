/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el 3 de julio de 2025, 22:03
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "Palabra.h"
#include "Plato.h"
#include "Atencion.h"
#include "FuncionesAuxiliares.h"
/*
 * 
 */
int main(int argc, char** argv) {
    struct Palabra lexicon[30]{};
    int cantLexicon=0;    
    cargaLexicon("lexicon.csv",lexicon,cantLexicon);
    
    struct Plato platos[200]{};
    int cantPlatos=0;
    cargaPlatos("platos.csv",platos,cantPlatos);
    
    struct Atencion atenciones[100]{};
    int cantAtenciones;
    cargaAtenciones("atenciones.txt",atenciones,cantAtenciones,platos,cantPlatos);
    
    procesaComentarios("comentarios.csv",atenciones,cantAtenciones,lexicon,cantLexicon);
    
    imprimeReporte("ReporteAtencionesAnalisisSentimiento.txt",atenciones,cantAtenciones);
    
    return 0;
}

