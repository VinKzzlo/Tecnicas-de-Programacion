/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 26 de mayo de 2024, 14:51
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define NO_ENCONTRADO -1
#define TAMLINEA 96
void leerDatosPacientes(const char *nombArch,int *pacientesDNI,int *pacientesDist,
                        double *pacientesDcto,char *pacientesClasif,int &cantPac){
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    
    
    int dni,distrito,aaNac;
    double porcDcto;
    cantPac=0;
    while(true){
        arch>>dni;
        if(arch.eof())break;
        arch>>ws;
        while(arch.get() != ']');
        arch>>distrito>>aaNac>>porcDcto;
        pacientesDNI[cantPac] = dni;
        pacientesDist[cantPac] = distrito;
        pacientesDcto[cantPac] = porcDcto;
        if(aaNac>=2019)
            pacientesClasif[cantPac] = 'A';
        else if(aaNac>=2013)
            pacientesClasif[cantPac] = 'B';
        else if(aaNac>=2006)
            pacientesClasif[cantPac] = 'C';
        else if(aaNac>=1998)
            pacientesClasif[cantPac] = 'D';
        else if(aaNac>=1965)
            pacientesClasif[cantPac] = 'E';
        else
            pacientesClasif[cantPac] = 'F';
        cantPac++;
    }
}

void leerDatosMedicinas(const char *nombArch,int *medicinaCodigo,
                        double *medicinaPrecio,int &cantMedi){
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codigo;
    double precio;
    cantMedi=0;
    while(true){
        arch>>codigo;
        if(arch.eof()) break;
        arch>>ws;
        while(arch.get() != ' ');
        arch>>precio;
        medicinaCodigo[cantMedi]=codigo;
        medicinaPrecio[cantMedi]=precio;
        cantMedi++;
    }   
}

void verificarReportePrueba(const char *nombArch,int *pacientesDNI,
                            int *pacientesDist, double *pacientesDcto,
                            char *pacientesClasif, int cantPac,
                            int *medicinaCodigo, double *medicinaPrecio,
                            int cantMedi){
    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    arch<<setw(20)<<' '<<"DATOS DE PACIENTES"<<endl;
    arch<<left<<setw(18)<<"Clasificacion"<<setw(12)<<"DNI"<<setw(10)<<"Distrito"
        <<setw(8)<<"%Descuento"<<right<<endl;
    for(int i=0;i<cantPac;i++){
        arch<<setw(7)<<pacientesClasif[i]<<setw(7)<<' '<<setw(12)<<pacientesDNI[i]
            <<setw(12)<<pacientesDist[i]<<setw(10)<<pacientesDcto[i]<<endl;
    }
    arch<<endl<<"DATOS DE MEDICINAS"<<endl;
    arch<<left<<setw(15)<<"Codigo"<<setw(10)<<"Precio"<<endl;
    for(int i=0;i<cantMedi;i++){
        arch<<right<<setw(10)<<medicinaCodigo[i]<<setw(10)<<medicinaPrecio[i]<<endl;
    }
}

void updateTotalPacientes(const char *nombArch, int *pacientesDNI,
                          int *pacientesDist, double *pacientesDcto,
                          char *pacientesClasif, int cantPac,
                          int *medicinaCodigo, double *medicinaPrecio,
                          int cantMedi,
                          int *pacientesCantCit,int *pacientesCantMeds,
                          double *pacientesPago){
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
//        9/9/2023   94683380   11:17:52   12:48:30   40414   28409   5
    int nroDNIPac, numCualq, posPac;   
    while(true){
        arch>>numCualq;
        if(arch.eof())break;
        while(arch.get()!=' ');
        arch>>nroDNIPac;
        posPac = buscarPaciente(nroDNIPac,pacientesDNI,cantPac);
        if(posPac != NO_ENCONTRADO){
            pacientesCantCit[posPac]++;
            arch>>ws;
            while(arch.get()!=' ');
            arch>>ws;
            while(arch.get()!=' ');
            arch>>numCualq;
            registrarEnPacis(arch,pacientesCantMeds[posPac],pacientesPago[posPac],
                             pacientesDcto[posPac],medicinaCodigo,medicinaPrecio,
                             cantMedi);
        }
        else while(arch.get() != '\n');
        
    }
}

void registrarEnPacis(ifstream &arch,int &pacientesCantMeds,double &pacientesPago,
                      double pacientesDcto,int *medicinaCodigo,
                      double *medicinaPrecio, int cantMedi){
    int codMedic, cantRec, posMedi;
    double precio;
    while(true){
        if(arch.get() == '\n') break;
        arch>>codMedic>>cantRec;
        posMedi = buscarMedicina(codMedic,medicinaCodigo,cantMedi);
        if(posMedi!=NO_ENCONTRADO){
            pacientesCantMeds++;
            precio = (medicinaPrecio[posMedi]*cantRec)*(1-pacientesDcto/200);
            pacientesPago += precio;
        }
        else while(arch.get() != '\n');
    }
}

int buscarPaciente(int nroDNIPac,int *pacientesDNI,int cantPac){
    for(int i=0;i<cantPac;i++)
        if(nroDNIPac==pacientesDNI[i]) return i;
    return NO_ENCONTRADO;
}
int buscarMedicina(int codMedic,int *medicinaCodigo,int cantMedi){
    for(int i=0;i<cantMedi;i++)
        if(codMedic==medicinaCodigo[i]) return i;
    return NO_ENCONTRADO;
}

void ordenarArreglosPacs(int *pacientesDNI,int *pacientesDist,double *pacientesDcto,
                         char *pacientesClasif,int *pacientesCantCit,
                         int *pacientesCantMeds,double *pacientesPago,int cantPac){
    for(int i=0;i<cantPac-1;i++){
        for(int k=i+1;k<cantPac;k++){
            if (pacientesClasif[i]>pacientesClasif[k] or
                (pacientesClasif[i]==pacientesClasif[k] and 
                pacientesDist[i]<pacientesDist[k])){
                cambiarInt(pacientesDNI[i],pacientesDNI[k]);
                cambiarInt(pacientesDist[i],pacientesDist[k]);
                cambiarDbl(pacientesDcto[i],pacientesDcto[k]);
                cambiarChr(pacientesClasif[i],pacientesClasif[k]);
                cambiarInt(pacientesCantCit[i],pacientesCantCit[k]);
                cambiarInt(pacientesCantMeds[i],pacientesCantMeds[k]);
                cambiarDbl(pacientesPago[i],pacientesPago[k]);
            }
        }
    }
}

void cambiarInt(int &datoI,int &datoK){
    int aux;
    aux = datoI;
    datoI = datoK;
    datoK = aux;
    
}
void cambiarDbl(double &datoI,double &datoK){
    double aux;
    aux = datoI;
    datoI = datoK;
    datoK = aux;
}
void cambiarChr(char &datoI,char &datoK){
    char aux;
    aux = datoI;
    datoI = datoK;
    datoK = aux;    
}

void emitirReportePacientes(const char *nombArch,int *pacientesDNI,int *pacientesDist,
                            double *pacientesDcto, char *pacientesClasif,
                            int *pacientesCantCit, int *pacientesCantMeds,
                            double *pacientesPago,int cantPac){
    double pagoTotal=0;
    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    imprimeEncabezado(arch);
    for(int i=0;i<cantPac;i++){
        arch<<right<<setw(6)<<pacientesClasif[i]<<setw(15)<<pacientesDist[i]
            <<setw(15)<<pacientesDNI[i]<<setw(12)<<pacientesDcto[i]<<'%'
            <<setw(10)<<pacientesCantCit[i]<<setw(17)<<pacientesCantMeds[i]
            <<setw(20)<<pacientesPago[i]<<endl;
        pagoTotal+=pacientesPago[i];
    }
    imprimeLinea(arch,'-');
    arch<<"RESUMEN:"<<endl;
    imprimeLinea(arch,'-');
    arch<<"PAGO TOTAL POR MEDICINAS: "<<pagoTotal<<endl;
    imprimeLinea(arch,'=');
}

void imprimeEncabezado(ofstream &arch){
    arch<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    imprimeLinea(arch,'=');
    arch<<setw((36+TAMLINEA)/2)<<"CONSOLIDADO DE ATENCIÓN POR PACIENTE"<<endl;
    imprimeLinea(arch,'=');
    arch<<left<<setw(15)<<"CLASIFICACION"<<setw(10)<<"DISTRITO"
        <<setw(15)<<"DNI PACIENTE"<<setw(13)<<"%DESCUENTO"<<setw(13)<<"CANT.CITAS"
        <<setw(17)<<"CANT.MEDICINAS"<<setw(14)<<"PAGO.MEDICINAS"<<endl;
}

void imprimeLinea(ofstream &arch,char c){
    for(int i=0;i<TAMLINEA;i++)
        arch.put(c);
    arch<<endl;
}