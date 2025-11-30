/*
 *
 * Proyecto:    Lab9_25_2_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       25/11/2025
 *
 */

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "Nodo.h"
#define TAM_LINEA 120

void cargarCategorias(const char *nombArch,struct Nodo *&lista) {
    ifstream archIn(nombArch,ios::in);
    if (not archIn.is_open()) {
        cout << "ERROR: no se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }

    lista = nullptr;
    struct Categoria categoria{};
    while (true) {
        leerCategoria(archIn, categoria);
        if (archIn.eof()) break;
        insertarOrdenado(categoria, lista);
    }
}

void leerCategoria(ifstream &archIn, struct Categoria &categoria) {
    categoria.codigo = leeCadenaExacta(archIn,9,',');
    if (archIn.eof()) return;
    categoria.nombre = leeCadenaExacta(archIn,40,',');
    categoria.descripcion = leeCadenaExacta(archIn,100);
}

void insertarOrdenado(struct Categoria &categoriaNueva, struct Nodo *&lista) {
    struct Nodo *aux = lista, *ant=nullptr, *nuevo;
    nuevo = new struct Nodo;
    nuevo->categoria = categoriaNueva;
    while (aux != nullptr and strcmp(categoriaNueva.codigo, aux->categoria.codigo)>0) {
        ant = aux;
        aux = aux->siguiente;
    }
    nuevo->siguiente = aux;
    if (ant==nullptr) lista = nuevo;
    else ant->siguiente = nuevo;
}

void actualizarCategoriasConReproducciones(const char *nombArch, struct Nodo *lista) {
    ifstream archIn(nombArch,ios::in);
    if (not archIn.is_open()) {
        cout << "ERROR: no se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    struct Nodo *nodoBuscado;
    while (true) {
        char *codigo = leeCadenaExacta(archIn,9,',');
        if (archIn.eof())break;
        nodoBuscado = buscarCategoria(codigo,lista);
        if (nodoBuscado != nullptr)
            actualizarCategoria(archIn,nodoBuscado->categoria);
        else
            while (archIn.get() != '\n');
    }
}

struct Nodo *buscarCategoria(const char *codigo,struct Nodo *lista) {
    struct Nodo *aux = lista;
    while (aux and strcmp(codigo, aux->categoria.codigo) > 0) {
        aux = aux->siguiente;
    }
    if (aux == nullptr or strcmp(codigo, aux->categoria.codigo) < 0)
        return nullptr;
    else
        return aux;
}

void actualizarCategoria(ifstream &archIn,struct Categoria &categoria) {
    double dropOff;
    int duracion;
    char *nombCanal = leeCadenaExacta(archIn,60,',');

    archIn >> dropOff;
    archIn.get();
    duracion = leerDuracion(archIn);

    if (duracion > categoria.duracionMaxima) {
        categoria.duracionMaxima = duracion;
        categoria.canalConDuracionMaxima = nombCanal;
    }
    categoria.duracionTotal += duracion;

    int n = categoria.cantidadDeReproducciones;
    categoria.arrDropOff[n] = dropOff;
    categoria.cantidadDeReproducciones++;
}

void calcularPromediosDeDropOff(struct Nodo *lista) {
    struct Nodo *aux = lista;
    while (aux) {
        promedioDropOff(aux->categoria);
        aux = aux->siguiente;
    }
}

void promedioDropOff(struct Categoria &categoria) {
    int n = categoria.cantidadDeReproducciones;
    double totalDropOff=0.0;
    for (int i=0; i<n; i++) {
        totalDropOff += categoria.arrDropOff[i];
    }
    categoria.promedioDropOff = totalDropOff/n;
}

void eliminarNodos(struct Nodo *&lista) {
    struct Nodo *aux = lista, *ant = nullptr, *sale;
    while (aux) {
        if (aux->categoria.promedioDropOff >= 3.5) {
            ant = aux;
            aux = aux->siguiente;
        }
        else { // Se eliminan los menores a 3.5
            sale = aux;
            if (ant == nullptr) {
                lista = aux->siguiente;
                aux = lista;
            }
            else {
                ant->siguiente = aux->siguiente;
                aux = aux->siguiente;
            }
            delete sale;
        }
    }
}

int leerDuracion(ifstream &archIn) {
    int hh,mm,ss;
    archIn >> hh;
    archIn.get();
    archIn >> mm;
    archIn.get();
    archIn >> ss;
    archIn.get();
    return hh*3600+mm*60+ss;
}

char *leeCadenaExacta(ifstream &archIn, int size, char delim){
    char buffer[size], *ptr;
    archIn.getline(buffer, size, delim);
    if (archIn.eof()) return nullptr;
    ptr = new char[strlen(buffer)+1];
    strcpy(ptr, buffer);
    return ptr;
}

void emiteReportePorCategorias(const char *nombArch, struct Nodo *lista) {
    ofstream archRep(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archRep<<setprecision(2)<<fixed;
    struct Nodo *aux = lista;
    archRep << setw((21+TAM_LINEA)/2) << "REPORTE DE CATEGORIAS" << endl;
    while (aux) {
        imprimeCategoria(archRep,aux->categoria);
        aux = aux->siguiente;
    }

}

void imprimeCategoria(ofstream &archRep,const struct Categoria &categoria) {
    imprimeLinea(archRep,'=');
    archRep << "Codigo: " << setw(5) << ' ' << categoria.codigo << endl;
    archRep << "Nombre: " << setw(5) << ' ' << categoria.nombre << endl;
    archRep << "Descripcion: " << categoria.descripcion << endl;
    imprimeLinea(archRep,'-');
    if (categoria.cantidadDeReproducciones>0) {
        imprimeDetalleReproducciones(archRep,categoria);
    }
}

void imprimeDetalleReproducciones(ofstream &archRep,const struct Categoria &categoria) {
    archRep << "INFORMACION DE LAS REPRODUCCIONES" << endl;
    archRep << "DURACION MAXIMA:" << endl;
    archRep << "NOMBRE DEL CANAL: " << categoria.canalConDuracionMaxima << endl;
    archRep << "DURACION:" << setw(9) << ' ';
    imprimeDuracion(archRep,categoria.duracionMaxima);
    imprimeLinea(archRep,'-');
    archRep << "LISTA DE DROP-OFF:";
    int n = categoria.cantidadDeReproducciones;
    for (int i=0; i<n; i++) archRep << setw(8) << categoria.arrDropOff[i];
    archRep << endl;
    archRep << "PROMEDIO DE DROP-OFF: " << setw(12) << categoria.promedioDropOff << endl;
    archRep << "TIEMPO DE DURACION TOTAL: ";
    imprimeDuracion(archRep,categoria.duracionTotal);

}

void imprimeDuracion(ofstream &archRep, int duracion) {
    int hh = duracion/3600;
    int mm = (duracion%3600)/60;
    int ss = duracion%60;

    archRep << setfill('0') << setw(2) << hh << ":";
    archRep << setfill('0') << setw(2) << mm << ":";
    archRep << setfill('0') << setw(2) << ss << setfill(' ');
    archRep << endl;
}

void imprimeLinea(ofstream &archRep, char car) {
    for (int i=0; i < TAM_LINEA; i++)
        archRep.put(car);
    archRep << endl;
}