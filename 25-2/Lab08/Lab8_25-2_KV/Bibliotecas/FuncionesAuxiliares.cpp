/*
 *
 * Proyecto:    Lab8_25_2_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       18/11/2025
 *
 */

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "../Estructuras/Categoria.h"
#include "../Estructuras/Reproduccion.h"
using namespace std;
#include "FuncionesAuxiliares.h"
#define TAM_LINEA 120
#define NOT_FOUND (-1)

void cargarCategorias(const char *nombArch, struct Categoria *arrCategorias, int &cantidadCategorias) {
    ifstream archCat(nombArch,ios::in);
    if (not archCat.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    cantidadCategorias = 0;
    while (true) {
        arrCategorias[cantidadCategorias].codigo = leerCadenaExacta(archCat,',');
        if (archCat.eof()) break;
        arrCategorias[cantidadCategorias].nombre = leerCadenaExacta(archCat,',');
        arrCategorias[cantidadCategorias].descripcion = leerCadenaExacta(archCat);
        //Se asigna el espacio de memoria necesario en este momento
        arrCategorias[cantidadCategorias].reproducciones = new struct Reproduccion[15]{};
        cantidadCategorias++;
    }
}

void cargarReproduccionesEnCats(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias) {
    ifstream archStr(nombArch,ios::in);
    if (not archStr.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    char *nombreCanal, *codCategoria;
    double rating;
    int duracion;

    while (true) {
        nombreCanal = leerCadenaExacta(archStr,',');
        if (archStr.eof())break;
        codCategoria = leerCadenaExacta(archStr,',');
        archStr >> rating;
        archStr.get();
        duracion = leerHora(archStr);
        archStr.get(); //Quitamos el salto de línea para el getline
        int posCategoria = buscarCategoria(codCategoria,arrCategorias,cantidadCategorias);
        if (posCategoria != NOT_FOUND) {
            int numRep = arrCategorias[posCategoria].numReproducciones;
            arrCategorias[posCategoria].reproducciones[numRep].canal = nombreCanal;
            arrCategorias[posCategoria].reproducciones[numRep].rating = rating;
            arrCategorias[posCategoria].reproducciones[numRep].duracion = duracion;
            arrCategorias[posCategoria].numReproducciones++;
        }
    }
}

void ordenarArreglosPorNombreCategoria(struct Categoria *arrCategorias,int cantidadCategorias) {
    for (int i = 0; i < cantidadCategorias-1; i++) {
        for (int j = i+1; j < cantidadCategorias; j++) {
            if (strcmp(arrCategorias[i].nombre, arrCategorias[j].nombre) > 0) {
                cambiarCategorias(arrCategorias[i],arrCategorias[j]);
            }
        }
    }
}

void cargarComentarios(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias) {
    ifstream archCom(nombArch,ios::in);
    if (not archCom.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }

    char *nombre, *comentario;
    while (true) {
        nombre = leerCadenaExacta(archCom,',');
        if (archCom.eof()) break;
        comentario = leerCadenaExacta(archCom);

        //Recorremos categorias, sus reproducciones y vamos ubicando estos comentarios en cada canal
        for (int i = 0; i < cantidadCategorias; i++)
            for (int j = 0; j < arrCategorias[i].numReproducciones; j++)
                if (strcmp(arrCategorias[i].reproducciones[j].canal, nombre) == 0) {
                    int numComentarios = arrCategorias[i].reproducciones[j].numComentarios;
                    //Asignamos espacio
                    arrCategorias[i].reproducciones[j].comentarios[numComentarios] = new char[strlen(comentario)+1];
                    //Copiamos la cadena
                    strcpy(arrCategorias[i].reproducciones[j].comentarios[numComentarios], comentario);
                    arrCategorias[i].reproducciones[j].numComentarios++;
                }

    }

}


void cambiarCategorias(struct Categoria &catI, struct Categoria &catJ) {
    struct Categoria aux;
    aux = catI;
    catI = catJ;
    catJ = aux;
}

char *leerCadenaExacta(ifstream &archIn, char delim) {
    char buffer[100], *ptr;
    archIn.getline(buffer, 100, delim);
    if (archIn.eof()) return nullptr;
    ptr = new char [strlen(buffer) + 1];
    strcpy(ptr, buffer);
    return ptr;
}

int leerHora(ifstream &archIn) {
    int hh, mm, ss;
    archIn >> hh;
    archIn.get();
    archIn >> mm;
    archIn.get();
    archIn >> ss;
    return hh*3600 + mm*60 + ss;
}

int buscarCategoria(char *codCategoria,struct Categoria *arrCategorias,int cantidadCategorias) {
    for (int i=0; i<cantidadCategorias; i++) {
        if (strcmp(codCategoria, arrCategorias[i].codigo)==0)
            return i;
    }
    return NOT_FOUND;
}

void imprimeReportePorCategorias(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias) {
    ofstream archRep(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archRep<<setprecision(2)<<fixed;
    archRep << setw((TAM_LINEA+22)/2) << "REPORTE POR CATEGORIAS" << endl;
    for (int i = 0; i < cantidadCategorias; i++) {
        imprimeLinea(archRep,TAM_LINEA,'=');
        archRep << "Codigo:" << setw(6) << ' ' << arrCategorias[i].codigo << endl;
        archRep << "Nombre:" << setw(6) << ' ' << arrCategorias[i].nombre<< endl;
        archRep << "Descripcion: " << arrCategorias[i].descripcion << endl;
        imprimeLinea(archRep,TAM_LINEA,'-');
        archRep << "REPRODUCCIONES:" << endl;
        for (int j = 0; j < arrCategorias[i].numReproducciones; j++) {
            imprimeReproduccion(archRep,arrCategorias[i].reproducciones[j]);
        }
    }
}

void imprimeReproduccion(ofstream &archRep,struct Reproduccion reproduccion) {
    archRep << "CANAL: " << left << setw(25) << reproduccion.canal << right;
    archRep << "RATING: " << setw(8) << reproduccion.rating << setw(8) << "";
    archRep << "DURACION: " << setw(3) << "";
    imprimeHora(archRep,reproduccion.duracion);
    archRep << endl;
    int numComentarios = reproduccion.numComentarios;
    archRep << setw(5) << "" << "COMENTARIOS:" << endl;
    imprimeComentarios(archRep,reproduccion.comentarios, numComentarios);
}

void imprimeComentarios(ofstream &archRep,char **comentarios, int numComentarios) {
    for (int i=0; i<numComentarios; i++) {
        archRep << setw(7) << "- ";
        archRep << comentarios[i] << endl;
    }
}

void imprimeLinea(ofstream &archOut, int size, char car) {
    for (int i=0; i<size; i++) {
        archOut.put(car);
    }
    archOut << endl;
}

void imprimeHora(ofstream &archOut, int tiempoSegundos) {
    int hh = tiempoSegundos / 3600;
    int mm = (tiempoSegundos%3600)/60;
    int ss = tiempoSegundos%60;

    archOut << setfill('0') << setw(2) << hh << ':';
    archOut << setw(2) << mm << ':';
    archOut << setw(2) << ss << setfill(' ');

}