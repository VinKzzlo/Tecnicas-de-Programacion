/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
#include "funciones.h"


void cargardatosmedicos(int *arrmedicos, double *arrtarifa, int *arrpacmed, int *arrpac
, double *arringreso, double *arringresomed, int &cantmedicos){
    int codmedico;
    double tarifa;
    ifstream archMedicos("Medicos.txt", ios::in);
    if(not archMedicos.is_open())exit(1);
    while(true){
        archMedicos>>codmedico;
        if(archMedicos.eof())break;
        archMedicos>>ws;
        archMedicos.get();
        while(archMedicos.get()!='/');
        archMedicos>>ws;
        while(archMedicos.get()!=' ');
        archMedicos>>tarifa;
        arrmedicos[cantmedicos]=codmedico;
        arrtarifa[cantmedicos]=tarifa;
        arrpacmed[cantmedicos]=0;
        arrpac[cantmedicos]=0;
        arringreso[cantmedicos]=0;
        arringresomed[cantmedicos]=0;
        cantmedicos++;
    }
}

void cargardatosmedicinas(int *arrmedicinas, double *arrprecio, int* arrcant, 
        double *arringreso, double *arrdescuento, int &cantmedicinas){
    int codmed;
    double precio;
    ifstream archMed("Medicinas.txt", ios::in);
    if(not archMed.is_open())exit(1);
    while(true){
        archMed>>codmed;
        if(archMed.eof())break;
        archMed>>ws;
        while(archMed.get()!=' ');
        archMed>>precio;
        arrmedicinas[cantmedicinas]=codmed;
        arrprecio[cantmedicinas]=precio;
        arrcant[cantmedicinas]=0;
        arringreso[cantmedicinas]=0;
        arrdescuento[cantmedicinas]=0;
        cantmedicinas++;
    }
}

void cargarcitas(int *arrmedicos, double *arrtarifa, int *arrpacmed, int *arrpac
        , double *arringreso, double *arringresomed, int cantmedicos,
        int *arrmedicinas, double *arrprecio, int *arrcant, 
        double *arringresomedmed, double *arrdescuento, int cantmedicinas){
    int num, dni, hhi, mmi, medicina, ssi, hhf, mmf, ssf, medico, cant;
    double seguro, tiempohh;
    char c;
    ifstream archCitas("CitasMedicas.txt", ios::in);
    if(not archCitas.is_open())exit(1);
    while(true){
        archCitas>>num;
        if(archCitas.eof())break;
        archCitas>>c>>num>>c>>num>>dni>>seguro>>hhi>>c>>mmi>>c>>ssi>>hhf>>c>>mmf>>c>>ssf>>medico;
        tiempohh=((hhf*3600+mmf*60+ssf)-(hhi*3600+mmi*60+ssi))/3600;
        int posmedico=buscararrint(medico,arrmedicos,cantmedicos);
        arringreso[posmedico]+=(arrtarifa[posmedico]*tiempohh)-((arrtarifa[posmedico]*tiempohh)*seguro/100);
        if(archCitas.get()!='\n'){
            while(archCitas.get()!='\n'){
                archCitas>>medicina>>cant;
                int posmed=buscararrint(medicina, arrmedicinas, cantmedicinas);
                arringresomed[posmedico]+=(arrprecio[posmed]*cant)-((arrprecio[posmed]*cant)*seguro/200);
                arrpacmed[posmedico]+=1;
                arrcant[posmed]+=cant;
                arringresomedmed[posmed]+=arrprecio[posmed]*cant;
                arrdescuento[posmed]+=(arrprecio[posmed]*cant)*seguro/200;
            }
        }else{
            arrpac[posmedico]+=1;
        }
                
    }
}

int buscararrint(int cod, int *arrcod, int cant){
    int i;
    for(i=0;i<=cant;i++){
        if(arrcod[i]==cod)return i;
    }
}

void reportedeingreso(int *arrmedicos, double *arrtarifa, int *arrpacmed, int *arrpac
, double *arringreso, double *arringresomed, int &cantmedicos, ofstream &archReporte){
    int i;
    double totalcitas=0, totalmed=0, total=0;
    
    archReporte<<setfill('=')<<setw(119)<<"-"<<setfill(' ')<<endl<<setw(60)<<right<<"EMPRESA DE SALUD S. A."<<endl<<setw(65)<<right<<"REGISTRO DE INGRESOS POR MEDICO"<<endl<<setfill('=')<<setw(119)<<"="<<setfill(' ')<<endl;
    archReporte<<"Codigo del medico  Tarifa   Ingreso citas    Ingreso medicamentos   Total    Con medicinas  Sin medicinas  Total pac "<<endl<<setfill('-')<<setw(119)<<"-"<<setfill(' ')<<endl;
    for(i=0;i<=cantmedicos;i++){
        archReporte<<setfill('0')<<setw(3)<<right<<i<<setfill(' ')<<setw(7)<<right<<arrmedicos[i]<<
                "  "<<arrtarifa[i]<<"  "<<arringreso[i]<<"  "<<arringresomed[i]<<"  "<<
                arringreso[i]+arringresomed[i]<<"  "<<arrpacmed[i]<<"  "<<arrpac[i]<<"  "<<arrpac[i]+arrpacmed[i]<<endl;
        totalcitas+=arringreso[i];
        totalmed+=arringresomed[i];
        total+=arringreso[i]+arringresomed[i];
    }
    archReporte<<setfill('-')<<setw(119)<<"-"<<setfill(' ')<<endl<<"Totales: "<<setw(22)<<right<<totalcitas<<
            "   "<<totalmed<<"   "<<total<<endl<<setfill('=')<<setw(119)<<"="<<endl<<endl<<endl<<setw(119)<<"="<<setfill(' ')<<endl;
}
