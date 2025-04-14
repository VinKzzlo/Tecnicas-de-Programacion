/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 12 de mayo de 2024, 21:47
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define NO_ENCONTRADO -1
#define TAMLINEA 132

void leeDatosMedicos(const char *nombArch,int *medicosCods,double *medicosTarifa,
                     int &numMedicos){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codigo;
    double tarifa;
    
    numMedicos=0;
    while(true){
        arch>>codigo;
        if(arch.eof()) break;
        arch>>ws;
        arch.get(); //Leo el primer '/'
        while(arch.get() != '/');
        arch>>ws;
        while(arch.get() != ' ');
        arch>>tarifa;
        medicosCods[numMedicos] = codigo;
        medicosTarifa[numMedicos] = tarifa;
        numMedicos++;
    }
}

void leeDatosMedicinas(const char *nombArch,int *medicinCods,
                       double *medicinPrecios, int &numMedicin){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codigo;
    double precio;
    
    numMedicin=0;
    while(true){
        arch>>codigo;
        if(arch.eof()) break;
        arch>>ws;
        while(arch.get() != ' ');
        arch>>precio;
        medicinCods[numMedicin] = codigo;
        medicinPrecios[numMedicin] = precio;
        numMedicin++;
    }
}

void reporteDePrueba(const char *nombArch,int *medicosCods,double *medicosTarifa,
                     int numMedicos,
                    int *medicinCods,double *medicinPrecios,int numMedicin){
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    
    arch<<"Archivo de Medicos"<<endl;
    arch<<setw(25)<<"Codigo del Medico"<<setw(15)<<"Tarifa"<<endl;
    for(int i=0; i<numMedicos;i++){
        arch<<setw(25)<<medicosCods[i]<<setw(15)<<medicosTarifa[i]<<endl;
    }
        
    arch<<endl<<endl;
    arch<<"Archivo de Medicinas"<<endl;
    arch<<setw(25)<<"Codigo de la Medicina"<<setw(15)<<"Precio"<<endl;
    for(int i=0; i<numMedicin;i++){
        arch<<setw(25)<<medicinCods[i]<<setw(15)<<medicinPrecios[i]<<endl;
    }
        
    
}
void actualizarTotales(const char *nombArch,int *medicosCods,double *medicosTarifa,
                      int *medicosPacRec,int *medicosPacNoRec,double *medicosIngCitas,
                      double *medicosIngMeds,int numMedicos,
                      int *medicinCods,double *medicinPrecios,int *medicinCantVend,
                      double *medicinIngSinD,double *medicinDctos,int numMedicin){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int dd,mm,aa,DNIPac,codMedico,horaI,horaF;
    int posMedico;
    double porcDcto, duracionEnH;
    char c;
    while(true){
        arch>>dd;
        if(arch.eof()) break;
        arch>>c>>mm>>c>>aa>>DNIPac>>porcDcto;
        horaI = leerObtenerHora(arch);
        horaF = leerObtenerHora(arch);
        duracionEnH = (horaF-horaI)/(double)3600;
        arch>>codMedico;
        posMedico = buscarPosicionMedico(codMedico,medicosCods,numMedicos);
        if(posMedico != NO_ENCONTRADO){
            actualizarIngresoCita(medicosIngCitas[posMedico],duracionEnH,
                                  medicosTarifa[posMedico],porcDcto);
            if(arch.get() != '\n'){
                medicosPacRec[posMedico]++;
                actualizarDatosMedici(arch,medicosIngMeds[posMedico],porcDcto,
                                      medicinCods,medicinPrecios,medicinCantVend,
                                      medicinIngSinD,medicinDctos,numMedicin);
            }
            else medicosPacNoRec[posMedico]++;
        }
        else while(arch.get() != '\n');
    }
}

void actualizarIngresoCita(double &medicosIngCitas,double duracionEnH,
                          double medicosTarifa,double porcDcto){
    medicosIngCitas += (duracionEnH*medicosTarifa)*(1-porcDcto/100);
}

void actualizarDatosMedici(ifstream &arch,double &medicosIngMeds, double porcDcto,
                          int *medicinCods,double *medicinPrecios,int *medicinCantVend,
                          double *medicinIngSinD,double *medicinDctos,int numMedicin){
    int codMedicina, cantMedicina, posMedicina;
    double precio, montoMedicinas=0;
    while(true){
        if(arch.get() == '\n') break;
        arch>>codMedicina>>cantMedicina;
        posMedicina = buscarPosicionMedicina(codMedicina,medicinCods,numMedicin);
        if(posMedicina != NO_ENCONTRADO){
            medicinCantVend[posMedicina] += cantMedicina;
            precio = medicinPrecios[posMedicina];
            medicinIngSinD[posMedicina] += (precio*cantMedicina);
            medicinDctos[posMedicina] += (precio*cantMedicina)*(porcDcto/200);
            montoMedicinas += (precio*cantMedicina)*(1-porcDcto/200);
        }
        else while(arch.get() != '\n');
    }
    medicosIngMeds += montoMedicinas;
}

int buscarPosicionMedico(int codMedico,int *medicosCods,int numMedicos){
    for(int i=0;i<numMedicos;i++)
        if(codMedico == medicosCods[i]) return i;
    return NO_ENCONTRADO;
}
int buscarPosicionMedicina(int codMedicina,int *medicinCods,int numMedicin){
    for(int i=0;i<numMedicin;i++)
        if(codMedicina==medicinCods[i]) return i;
    return NO_ENCONTRADO;
}
int leerObtenerHora(ifstream &arch){
    int hor,min,seg;
    char c;
    arch>>hor>>c>>min>>c>>seg;
    return (hor*3600 + min*60 + seg);
}

void emitirReporte(const char *nombArch,int *medicosCods,double *medicosTarifa,
                   int *medicosPacRec,int *medicosPacNoRec,double *medicosIngCitas,
                   double *medicosIngMeds,int numMedicos,
                   int *medicinCods,double *medicinPrecios,int *medicinCantVend,
                   double *medicinIngSinD,double *medicinDctos,int numMedicin,
                   char seleccion, double &promedioIngresosTotales){
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    imprimirRegistroPorMedico(arch,medicosCods,medicosTarifa,medicosPacRec,
                              medicosPacNoRec,medicosIngCitas,medicosIngMeds,numMedicos,
                              promedioIngresosTotales);
    if(seleccion=='N'){
        arch<<endl<<endl;
        imprimirRegistroPorMedicamento(arch,medicinCods,medicinPrecios,
                                       medicinCantVend,medicinIngSinD,medicinDctos,
                                       numMedicin);
    }
}

void imprimirRegistroPorMedico(ofstream &arch,int *medicosCods,double *medicosTarifa,
                               int *medicosPacRec,int *medicosPacNoRec,
                               double *medicosIngCitas, double *medicosIngMeds,
                               int numMedicos,double &promedioIngresosTotales){
    int totalPacientesPorLinea;
    double totalIngresadoPorLinea;
    int totalPacConMedi=0, totalPacSinMed=0;
    double totalIngresosCitas=0, totalIngresosMedis=0, total=0;
    imprimeEncabezadoMedico(arch);
    for(int i=0;i<numMedicos;i++){
        totalPacientesPorLinea = medicosPacRec[i]+medicosPacNoRec[i];
        totalIngresadoPorLinea = medicosIngCitas[i]+medicosIngMeds[i];
        arch<<right<<setfill('0')<<setw(3)<<i+1<<setfill(' ')<<setw(9)<<medicosCods[i]
            <<setw(13)<<medicosTarifa[i]<<setw(13)<<medicosIngCitas[i]
            <<setw(16)<<medicosIngMeds[i]<<setw(15)<<totalIngresadoPorLinea
            <<setw(14)<<medicosPacRec[i]<<setw(23)<<medicosPacNoRec[i]
            <<setw(22)<<totalPacientesPorLinea<<endl;
        totalPacConMedi += medicosPacRec[i];
        totalPacSinMed += medicosPacNoRec[i];
        totalIngresosCitas += medicosIngCitas[i];
        totalIngresosMedis += medicosIngMeds[i];
        total += totalIngresadoPorLinea;
    }
    promedioIngresosTotales = (double)total/numMedicos;
    imprimeLinea(arch,'-');
    arch<<"Totales: "<<setw(30)<<totalIngresosCitas<<setw(18)<<totalIngresosMedis
        <<setw(15)<<total;
    arch<<setw(15)<<totalPacConMedi<<setw(15)<<totalPacSinMed
        <<setw(20)<<totalPacConMedi+totalPacSinMed<<endl;
    imprimeLinea(arch,'=');
}

void imprimirRegistroPorMedicamento(ofstream &arch,int *medicinCods,
                                    double *medicinPrecios,int *medicinCantVend,
                                    double *medicinIngSinD,double *medicinDctos,
                                    int numMedicin){
    int totalCantVendidas=0;
    double totalIngresadoPorLinea, totalIngSinD=0,totalDctos=0;
    imprimeEncabezadoMedicina(arch);
    for(int i=0; i<numMedicin;i++){
        totalIngresadoPorLinea = medicinIngSinD[i]-medicinDctos[i];
        arch<<right<<setfill('0')<<setw(3)<<i+1<<setfill(' ')<<setw(9)<<medicinCods[i]
            <<setw(16)<<medicinPrecios[i]<<setw(12)<<medicinCantVend[i]
            <<setw(20)<<medicinIngSinD[i]<<setw(15)<<medicinDctos[i]
            <<setw(15)<<totalIngresadoPorLinea<<endl;
        totalCantVendidas += medicinCantVend[i];
        totalIngSinD += medicinIngSinD[i];
        totalDctos += medicinDctos[i];
    }
    imprimeLinea(arch,'-');
    arch<<"Totales: "<<setw(30)<<totalCantVendidas<<setw(18)<<totalIngSinD
        <<setw(15)<<totalDctos<<setw(20)<<totalIngSinD-totalDctos<<endl;
    imprimeLinea(arch,'=');
}

 void eliminarMeds(double promedioIngresosTotales,int *medicosCods,double *medicosTarifa,
                   int *medicosPacRec,int *medicosPacNoRec,double *medicosIngCitas,
                   double *medicosIngMeds,int &numMedicos){
     for(int i=0;i<numMedicos-1;i++){
         if((medicosIngCitas[i]+medicosIngMeds[i])<promedioIngresosTotales){
             for(int k=i; k<numMedicos-1;k++){
                 medicosCods[i] = medicosCods[k+1];
                 medicosTarifa[i] = medicosTarifa[k+1];
                 medicosPacRec[i] = medicosPacRec[k+1];
                 medicosPacNoRec[i] = medicosPacNoRec[k+1];
                 medicosIngCitas[i] = medicosIngCitas[k+1];
                 medicosIngMeds[i] = medicosIngMeds[k+1];
             }
             numMedicos--;
         }
     }
     
 }
void imprimeEncabezadoMedico(ofstream &arch){
    imprimeLinea(arch,'=');
    arch<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    arch<<setw((31+TAMLINEA)/2)<<"REGISTRO DE INGRESOS POR MEDICO"<<endl;
    imprimeLinea(arch,'=');
    arch<<left<<setw(5)<<"No."<<setw(14)<<"Codigo del"<<setw(9)<<"Tarifa"
        <<setw(16)<<"Ingresos por"<<setw(19)<<"Ingresos por"<<setw(12)<<"Total"
        <<setw(22)<<"Pacientes atendidos"<<setw(25)<<"Pacientes atendidos"
        <<setw(11)<<"Total de"<<endl;
    arch<<setw(7)<<' '<<setw(22)<<"Medico"<<setw(15)<<"las citas"
        <<setw(17)<<"medicamentos"<<setw(17)<<"ingresado"<<setw(22)<<"con medicinas"
        <<setw(22)<<"sin medicinas"<<setw(11)<<"pacientes"<<endl;
    imprimeLinea(arch,'-');
}
void imprimeEncabezadoMedicina(ofstream &arch){
    imprimeLinea(arch,'=');
    arch<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    arch<<setw((36+TAMLINEA)/2)<<"REGISTRO DE INGRESOS POR MEDICAMENTO"<<endl;
    imprimeLinea(arch,'=');
    arch<<left<<setw(5)<<"No."<<setw(14)<<"Codigo del"<<setw(9)<<"Precio"
        <<setw(25)<<"Cantidad de unidades"<<setw(19)<<"Ingresos sin"
        <<setw(22)<<"Descuentos por"<<setw(25)<<"Total"<<endl;
    arch<<setw(4)<<' '<<setw(30)<<"Medicamento"<<setw(20)<<"vendidas"
        <<setw(20)<<"descuentos"<<setw(18)<<"los seguros"<<setw(22)<<"ingresado"
        <<endl;
    imprimeLinea(arch,'-');
}
void imprimeLinea(ofstream &arch,char caracter){
    for(int i=0;i<TAMLINEA;i++)
        arch.put(caracter);
    arch<<endl;
}