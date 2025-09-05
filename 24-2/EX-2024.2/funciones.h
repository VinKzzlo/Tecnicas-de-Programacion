/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 * Author: aml
 *
 * Created on 3 de julio de 2025, 11:12 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "Palabra.h"
#include "Comentario.h"
#include "Plato.h"
#include "Atencion.h"

void cargarLexicon(struct Palabra *arrPalabra,int &cantPalabras);

char *leerCadenaExactaDelim(ifstream &arch,char delim);

void cargarPlatos(struct Plato *arrPlatos,int &cantPlatos);

void procesarAtenciones(struct Atencion *arrAtenciones,struct Plato *arrPlatos,
                        int cantPlatos,int &cantAtenciones);

int buscarPlato(char *plato,struct Plato *arrPlatos,int cantPlatos);

char *asignarCadena(const char *cadena);

void leerComentarios(struct Atencion *arrAtenciones,int cantAtenciones,
                    struct Palabra *arrPalabra,int cantPalabras);

void preprocesarCadena(char *cadena, char *&linea_pre_procesada);

void procesarComentario(char *cadenaPre,int &palabrasSeparadas,
        int &polaridadAcumulada,struct Palabra *arrPalabra,int cantPalabras);

int buscarPedido(int codigoPedido,struct Atencion *arrAtenciones,int cantAtenciones);

int buscarLexiCom(char *palabraSeparada,struct Palabra *arrPalabra,int cantPalabras);

int buscarEspacio(const char *cadena);

void imprimirLinea(ofstream &arch,char car);

void emitirReporte(struct Atencion *arrAtenciones,int cantAtenciones);

#endif /* FUNCIONES_H */

