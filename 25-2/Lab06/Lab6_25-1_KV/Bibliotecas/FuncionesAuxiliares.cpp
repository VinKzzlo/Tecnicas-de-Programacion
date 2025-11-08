/*
 *
 * Proyecto:    Lab6_25_1_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       3/11/2025
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "FuncionesAuxiliares.h"
#define NOT_FOUND (-1)

void cargarCategorias(const char *nombArch, char **arrCategoriaCodigo, char **arrCategoriaNombre, int &cantCategorias) {
    ifstream archIn(nombArch,ios::in);
    if (not archIn.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }

    char *codigo, *nombre;
    while (true) {
        codigo = leeCadenaExacta(archIn,' ');
        if (archIn.eof())break;
        archIn >> ws;
        nombre = leeCadenaExacta(archIn);
        arrCategoriaCodigo[cantCategorias] = codigo;
        arrCategoriaNombre[cantCategorias] = nombre;
        cantCategorias++;
    }


}

void verificarCategorias(const char *nombArch, char **arrCategoriaCodigo, char **arrCategoriaNombre, int cantCategorias) {
    ofstream archRep(nombArch, ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }

    archRep << "REPORTE DE CATEGORIAS LEIDAS" << endl;
    imprimeLinea(archRep,'=',40);
    archRep << "CODIGO CATEGORIA" << setw(20) << "NOMBRE CATEGORIA" << endl;
    imprimeLinea(archRep,'=',40);
    for (int i=0; i < cantCategorias ; i++)
        archRep << arrCategoriaCodigo[i] << setw(12) << ' ' << arrCategoriaNombre[i] << endl;

}

void cargarStreams(const char *nombArch, int *arrStreamFecha, int *arrStreamDuracion,
    char **arrStreamNombCanal, char **arrStreamCodCategoria,
    double *arrStreamRating, double *arrStreamTasaDrop, int &cantStreams) {
    ifstream archIn(nombArch,ios::in);
    if (not archIn.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }

    int dd,mm,aa, duracion;
    double rating, dropOff;
    char *nombreCanal, *categoria;
    while (true) {
        archIn >> dd;
        if (archIn.eof())break;
        archIn.get();
        archIn >> mm;
        archIn.get();
        archIn >> aa >> ws;
        nombreCanal = leeCadenaExacta(archIn, ' ');
        archIn >> ws;
        categoria = leeCadenaExacta(archIn,' ');
        archIn >> rating >> dropOff;
        duracion = leerHora(archIn);
        arrStreamFecha[cantStreams] = aa*10000 + mm*100 + dd;
        arrStreamDuracion[cantStreams] = duracion;
        arrStreamRating[cantStreams] = rating;
        arrStreamTasaDrop[cantStreams] = dropOff;
        arrStreamNombCanal[cantStreams] = nombreCanal;
        arrStreamCodCategoria[cantStreams] = categoria;

        cantStreams++;
    }
}

void verificarStreams(const char *nombArch, int *arrStreamFecha, int *arrStreamDuracion,
    char **arrStreamNombCanal, char **arrStreamCodCategoria,
    double *arrStreamRating, double *arrStreamTasaDrop, int cantStreams) {
    ofstream archRep(nombArch, ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archRep << setprecision(2) << fixed;
    archRep << "REPORTE DE STREAMS REPRODUCIDOS LEIDOS" << endl;
    imprimeLinea(archRep,'=',110);
    archRep << "FECHA" << setw(22) << "NOMBRE CANAL" <<  setw(20) << "CATEGORIA STREAM" << setw(20) << "RATING CALIDAD"
            << setw(20) << "TASA DROP-OFF" << setw(20) << "DURACION" <<endl;
    imprimeLinea(archRep,'=',110);
    for ( int i=0 ; i<cantStreams ; i++) {
        imprimeFecha(archRep,arrStreamFecha[i]);
        archRep << setw(5) << ' ' << left << setw(20) << arrStreamNombCanal[i] ;
        archRep << setw(15) << arrStreamCodCategoria[i] << right << setw(15) << arrStreamRating[i];
        archRep << setw(17) << arrStreamTasaDrop[i] << setw(17) << ' ';
        imprimeHora(archRep,arrStreamDuracion[i]);
        archRep << endl;
    }
}

void emitirReportesCategoriasStreams(char **arrCategoriaCodigo, char **arrCategoriaNombre, int cantCategorias,
    int *arrStreamFecha, int *arrStreamDuracion, char **arrStreamNombCanal, char **arrStreamCodCategoria,
    double *arrStreamRating, double *arrStreamTasaDrop, int cantStreams) {

    for (int i=0 ; i < cantCategorias ; i++ ) {
        char *nombArch, *enlace;
        generaArchivoEnlace(arrCategoriaNombre[i],nombArch,enlace);
        imprimeReporte(arrCategoriaCodigo[i],arrCategoriaNombre[i],nombArch,enlace,
            arrStreamFecha, arrStreamDuracion, arrStreamNombCanal, arrStreamCodCategoria,
            arrStreamRating, arrStreamTasaDrop,cantStreams);
    }

}

void imprimeReporte(char *codCategoria, char *nombreCategoria, const char *nombArch, const char *enlace,
    int *arrStreamFecha, int *arrStreamDuracion, char **arrStreamNombCanal,
    char **arrStreamCodCategoria, double *arrStreamRating, double *arrStreamTasaDrop, int cantStreams) {
    ofstream archRep(nombArch, ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archRep << setprecision(2) << fixed;

    double sumaRating=0, sumaDropOff=0, duracionTotal=0;
    int cantReproducciones=0;
    archRep << "Codigo: " << codCategoria << endl;
    archRep << "Nombre: " << nombreCategoria << endl;
    archRep << "Enlace: " << enlace << endl;
    archRep << "REPRODUCCIONES:" << endl;
    imprimeLinea(archRep, '=', 72);
    archRep << "FECHA" << setw(13) << "CANAL" << setw(23) << "RATING" << setw(13) << "DROP-OFF" << setw(15) << "DURACION" << endl;
    for (int i=0 ; i < cantStreams ; i++)
        if (strcmp(codCategoria,arrStreamCodCategoria[i])==0) {
            imprimeFecha(archRep,arrStreamFecha[i]);
            archRep << setw(3) << ' ' << left << setw(20) << arrStreamNombCanal[i] << right;
            archRep << setw(7) << arrStreamRating[i] << setw(12) << arrStreamTasaDrop[i] << setw(9) << ' ';
            imprimeHora(archRep,arrStreamDuracion[i]);
            archRep << endl;
            sumaRating += arrStreamRating[i];
            sumaDropOff += arrStreamTasaDrop[i];
            duracionTotal += arrStreamDuracion[i];
            cantReproducciones++;
        }
    imprimeLinea(archRep, '=', 72);
    archRep << "PROMEDIO DE RATING: " << sumaRating/cantReproducciones << endl;
    archRep << "PROMEDIO DE DROP-OFF: " << sumaDropOff/cantReproducciones << endl;
    archRep << "DURACION TOTAL: ";
    imprimeHora(archRep,duracionTotal);
    archRep << endl;
}


char *leeCadenaExacta(ifstream &archIn, char delim) {
    char buffer[60], *cadena;
    archIn.getline(buffer,60,delim);
    if (archIn.eof())return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}

int leerHora(ifstream &archIn) {
    int hh,mm,ss;

    archIn >> hh;
    archIn.get();
    archIn >> mm;
    archIn.get();
    archIn >> ss;

    return hh*3600+mm*60+ss;
}

void imprimeHora(ofstream &archRep, int tiempoSegundos) {
    int hh = tiempoSegundos / 3600;
    int mm = (tiempoSegundos % 3600) / 60;
    int ss = tiempoSegundos % 60;

    archRep << setfill('0') << setw(2) << hh << ':';
    archRep << setw(2) << mm << ':';
    archRep << setw(2) << ss << setfill(' ') ;
}

void imprimeFecha(ofstream &archRep, int fecha) {
    int aa = fecha / 10000;
    int mm = (fecha % 10000) / 100;
    int dd = fecha % 100;

    archRep << setfill('0') << setw(2) << dd << '/';
    archRep << setw(2) << mm << '/';
    archRep << setw(4) << aa << setfill(' ') ;
}

void generaArchivoEnlace(const char *categoria, char *&nombArch, char *&enlace) {
    char *categoriaMod = new char[strlen(categoria)+1];
    bool mayus=true;
    int i=0;
    for (i; categoria[i]; i++) {
        if (mayus) {
            if (categoria[i] >= 'a' and categoria[i] <= 'z')
                categoriaMod[i] = (categoria[i] - ('a'-'A'));
            mayus = false;
        }
        else {
            categoriaMod[i] = categoria[i];
            if (categoria[i]=='_') mayus = true;
        }
    }
    categoriaMod[i] = '\0';

    char auxNombre[100] = "ArchivosDeReportes/";
    char auxEnlace[150] = "https://Laboratorio06_2025_2/ArchivosDeReportes/";

    strcat(auxNombre, categoriaMod);
    strcat(auxNombre, ".txt");
    nombArch = new char[strlen(auxNombre)+1];
    strcpy(nombArch,auxNombre);

    strcat(auxEnlace, categoriaMod);
    enlace = new char[strlen(auxEnlace)+1];
    strcpy(enlace,auxEnlace);

}

void imprimeLinea(ofstream &archRep, char car, int size) {
    for (int i=0; i < size ; i++)
        archRep.put(car);
    archRep << endl;
}