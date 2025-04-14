
/* 
 * File:   FuncionesAuxiliares.cpp
 * Author: Alessandro Salvador Santé Vega - 20223006
 * Created on 17 de junio de 2024, 07:10 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <cstring>
#include "FuncionesAuxiliares.h"
#include "Libro.h"
#include "Cliente.h"
#define NO_ENCONTRADO -1
#define TAMLINEA 169
void leerClientes(const char *nombArch,struct Cliente *arrClientes,int &numClientes){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int dni;
    char *nombre;
    numClientes=0;
    while(true){
        arch>>dni;
        if(arch.eof())break;
        arch.get();//Sacamos la coma
        nombre = leerCadenaExacta(arch,'\n');
        arrClientes[numClientes].dni = dni;
        arrClientes[numClientes].nombre = nombre;
        numClientes++;
    }
}
void leerLibros(const char *nombArch,struct Libro *arrLibros,int &numLibros){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    numLibros=0;
    char *codigo,*titulo,*autor;
    double precio;
    while(true){
        codigo = leerCadenaExacta(arch,',');
        if(arch.eof())break;
        titulo = leerCadenaExacta(arch,',');
        autor = leerCadenaExacta(arch,',');
        arch>>precio;
        arch.get();//como se lee una cadena al inicio, es necesario borrar el salto de linea del buffer
        arrLibros[numLibros].codigo = codigo;
        arrLibros[numLibros].titulo = titulo;
        arrLibros[numLibros].autor = autor;
        arrLibros[numLibros].precio = precio;
        //Se asigna el espacio para el arreglo de estructuras de ventas para cada libro
        arrLibros[numLibros].ventas = new struct Venta[10];
        numLibros++;
    }
}

void actualizarVentas(const char *nombArch,struct Libro *arrLibros,int numLibros){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int dni,dd,mm,aa, calificacion, posLibro, nv;
    char *codigo;
    while(true){
        codigo = leerCadenaExacta(arch,',');
        if(arch.eof())break;
        arch>>dni;
        arch.get();//SacamosLaComa
        leerFecha(arch,dd,mm,aa);
        arch.get();
        arch>>calificacion;
        arch.get();//como se lee una cadena al inicio, es necesario borrar el salto de linea del buffer
        posLibro = buscarLibro(codigo,arrLibros,numLibros);
        if(posLibro != NO_ENCONTRADO){
            nv = arrLibros[posLibro].librosVendidos;//nv: num de venta, indice para mantener codigo ordenado
            arrLibros[posLibro].ventas[nv].dni = dni;
            arrLibros[posLibro].ventas[nv].calificacion = calificacion;
            arrLibros[posLibro].sumaDeCalificaciones += calificacion;   
            actualizarFecha(arrLibros[posLibro].ventas[nv].fecha,dd,mm,aa);
            arrLibros[posLibro].librosVendidos++;
        }
    }
    determinarRanking(arrLibros,numLibros);
}

void leerFecha(ifstream &arch,int &dd,int &mm,int &aa){
    char c;
    arch>>dd>>c>>mm>>c>>aa;
}


int buscarLibro(char *codigo,struct Libro *arrLibros,int numLibros){
    for(int i=0;i<numLibros;i++)
        if(strcmp(codigo,arrLibros[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

void actualizarFecha(struct Fecha fecha,int dd,int mm, int aa){
    fecha.dd = dd;
    fecha.mm = mm;
    fecha.aa = aa;
    fecha.fecha = aa*10000+mm*100+dd;
}

void determinarRanking(struct Libro *arrLibros,int numLibros){
    double promedio;
    for(int i=0;i<numLibros;i++){
        if(arrLibros[i].librosVendidos>0){
            promedio = double(arrLibros[i].sumaDeCalificaciones)/(arrLibros[i].librosVendidos);
        }
        if(promedio>=75)
            arrLibros[i].ranking = 5;
        else if(promedio>=50)
            arrLibros[i].ranking = 3;
        else if(promedio>=25)
            arrLibros[i].ranking = 2;
        else
            arrLibros[i].ranking = 1;
        if(arrLibros[i].librosVendidos==0) arrLibros[i].ranking=0;
    }
}

void ordenarLibros(struct Libro *arrLibros,int numLibros){
    for(int i=0;i<numLibros-1;i++)
        for(int j=i+1;j<numLibros;j++)
            if(arrLibros[i].ranking<arrLibros[j].ranking or
               arrLibros[i].ranking==arrLibros[j].ranking and
               strcmp(arrLibros[i].titulo,arrLibros[j].titulo)>0){
                cambiarLibros(arrLibros[i],arrLibros[j]);
            }
}

void cambiarLibros(struct Libro &libroI,struct Libro &libroJ){
    struct Libro aux;
    aux = libroI;
    libroI = libroJ;
    libroJ = aux;
}

void emitirReporte(const char *nombArch,struct Libro *arrLibros,int numLibros,
                   struct Cliente *arrClientes,int numClientes){
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    imprimeEncabezado(arch);
    for(int i=0;i<numLibros;i++){
        imprimeLinea(arch,'=');
        arch<<left<<"LIBRO NO. "<<right<<setfill('0')<<setw(3)<<i+1<<setfill(' ')<<endl;
        arch<<left<<setw(5)<<' '<<setw(10)<<"CODIGO"<<setw(70)<<"TITULO"
            <<setw(42)<<"AUTOR"<<setw(11)<<"PRECIO"<<setw(21)<<"LIBROS VENDIDOS"
            <<setw(12)<<"RANKINGS"<<endl;
        arch<<setw(5)<<' '<<setw(10)<<arrLibros[i].codigo<<setw(70)<<arrLibros[i].titulo
            <<setw(40)<<arrLibros[i].autor<<right<<setw(8)<<arrLibros[i].precio
            <<setw(11)<<arrLibros[i].librosVendidos<<setw(20)<<arrLibros[i].ranking<<left<<endl;
        imprimeLinea(arch,'-');
        arch<<setw(5)<<' '<<"VENTAS REALIZADAS:"<<endl;
        if(arrLibros[i].librosVendidos>0){
            imprimeClientes(arrLibros[i].ventas,arrLibros[i].librosVendidos,arrClientes,numClientes,arch);
        }
        else{
            arch<<setw(5)<<' '<<"NO SE VENDIO ESTE LIBRO"<<endl;
        }
    }
}

void imprimeClientes(struct Venta *ventas,int numVentas,struct Cliente *arrClientes,
                    int numClientes,ofstream &arch){
    arch<<setw(5)<<' '<<setw(5)<<"No."<<setw(10)<<"DNI"<<setw(45)<<"NOMBRE"
        <<setw(20)<<"CALIFICACION"<<endl;
    for(int i=0;i<numVentas;i++){
        arch<<setw(5)<<' '<<right<<setfill('0')<<setw(2)<<i+1<<setfill(' ')
            <<setw(10)<<ventas[i].dni<<left<<"   ";
        for(int j=0;j<numClientes;j++){
            if(ventas[i].dni==arrClientes[j].dni){
                arch<<setw(45)<<arrClientes[j].nombre;
            }
        }
        arch<<right<<setw(7)<<ventas[i].calificacion<<endl;
    }
}

char* leerCadenaExacta(ifstream &arch,char delimitador){
    char buffer[100], *cadena;
    arch.getline(buffer,100,delimitador);
    if(arch.eof())return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}

void imprimeEncabezado(ofstream &arch){
    arch<<setw((TAMLINEA+16)/2)<<"LIBRERIA PUCP-TP"<<endl;
    arch<<setw((TAMLINEA+34)/2)<<"RESULTADO DE LAS VENTAS REALIZADAS"<<endl;
}
void imprimeLinea(ofstream &arch,char c){
    for(int i=0;i<TAMLINEA;i++)
        arch.put(c);
    arch<<endl;
}