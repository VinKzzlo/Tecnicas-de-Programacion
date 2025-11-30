/*
 *
 * Proyecto:    Lab10_25_1_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       24/11/2025
 *
 */

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "Nodo.h"

void crearListaOrdenada(const char *nombArch,struct Nodo *&lista) {
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << nombArch << endl;
        exit(1);
    }
    struct Cuenta cuentaNueva{};
    lista = nullptr;
    while (true) {
        leerAlumno(arch,cuentaNueva);
        if (arch.eof()) break;
        insertarOrdenado(cuentaNueva,lista);
    }
}

void leerAlumno(ifstream &arch,struct Cuenta &cuentaNueva) {
    arch >> cuentaNueva.codigo;
    if (arch.eof()) return;
    arch.get();
    cuentaNueva.nombre = leeCadenaExacta(arch,',');
    arch >> cuentaNueva.saldo;
    arch.get(); //Sacamos el salto de línea del buffer
}

void insertarOrdenado(struct Cuenta cuentaNueva,struct Nodo *&lista) {
    struct Nodo *p = lista, *ant = nullptr, *nuevo;
    nuevo = new struct Nodo;
    nuevo->cuenta = cuentaNueva;

    while (p != nullptr and cuentaNueva.codigo > p->cuenta.codigo) {
        ant = p;
        p = p->siguiente;
    }
    nuevo->siguiente = p;
    if (ant == nullptr) lista = nuevo;
    else ant->siguiente = nuevo;

}

void mostrarLista(const char *nombArch, Nodo *lista) {
    ofstream archRep(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout << "Error al abrir el archivo" << nombArch << endl;
        exit(1);
    }
    struct Nodo *p = lista;
    while (p) {
        archRep << p->cuenta.codigo << setw(10) << " " << p->cuenta.nombre << endl;
        p = p->siguiente;
    }
}

void registrarMovimientos(const char *nombArch,struct Nodo *lista) {
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << nombArch << endl;
        exit(1);
    }
    struct Nodo *p;
    int fecha, codigo, montoMovimiento;
    while (true) {
        fecha = leerFecha(arch);
        if (arch.eof())break;
        arch.get();//Sacamos la coma
        while (true) {
            arch >> codigo;
            arch.get();//Sacamos la coma
            arch >> montoMovimiento;
            p = buscarCuenta(codigo,lista);
            if (p != nullptr)
                actualizarCuenta(fecha,montoMovimiento,p->cuenta);
            if (arch.get()=='\n')
                break;
        }
    }
}

struct Nodo *buscarCuenta(int codigo, struct Nodo *lista) {
    struct Nodo *p = lista;
    while (p and codigo > p->cuenta.codigo) {
        p = p->siguiente;
    }
    if (p == nullptr or codigo < p->cuenta.codigo)
        return nullptr;
    else
        return p;
}

void actualizarCuenta(int fecha, double montoMovimiento, struct Cuenta &cuenta) {
    if (cuenta.saldo + montoMovimiento < 0) {
        cuenta.fechaSobregiro = fecha;
        cuenta.sobregiro = true;
    }
    cuenta.saldo += montoMovimiento;
}

void emiteReporteSaldos(const char *nombArch, struct Nodo *lista) {
    ofstream archRep(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout << "Error al abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archRep<<setprecision(2)<<fixed;
    struct Nodo *p = lista;
    while (p) {
        imprimeCuenta(archRep,p->cuenta);
        p = p->siguiente;
    }
}


int leerFecha(ifstream &arch) {
    int dd,mm,aa;
    arch >> dd;
    if (arch.eof()) return 0;
    arch.get();
    arch >> mm;
    arch.get();
    arch >> aa;
    return aa*10000+mm*100+dd;
}

char *leeCadenaExacta(ifstream &arch, char delim) {
    char buffer[100], *ptr;
    arch.getline(buffer, 100, delim);
    if (arch.eof()) return nullptr;
    ptr = new char[strlen(buffer) + 1];
    strcpy(ptr, buffer);
    return ptr;
}

void imprimeCuenta(ofstream &archRep,const struct Cuenta &cuenta) {
    archRep << cuenta.codigo << setw(10) << " " << cuenta.nombre << setw(10) << cuenta.saldo << setw(10);
    if (cuenta.sobregiro) {
        archRep << "SI";
        archRep << setw(10) << " ";
        imprimeFecha(archRep,cuenta.fechaSobregiro);
    }
    else {
        archRep << "NO";
        archRep << setw(10) << " ";
        archRep << setfill('-') << setw(3) << '/';
        archRep << setfill('-') << setw(3) << '/';
        archRep << setw(5) << ' ' << setfill(' ');
    }
    archRep << endl;
}

void imprimeFecha(ofstream &archrRep, int fecha) {
    int aa = fecha / 10000;
    int mm = (fecha % 10000) / 100;
    int dd = fecha % 100;
    archrRep << setfill('0') << setw(2) << dd << '/';
    archrRep << setfill('0') << setw(2) << mm << '/';
    archrRep << setfill(' ') << setw(4) << aa;
}