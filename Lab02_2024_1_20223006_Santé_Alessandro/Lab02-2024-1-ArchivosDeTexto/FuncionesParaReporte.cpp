/* 
 * Autor:  Alessandro Salvador Santé Vega - 20223006
 * Created on 15 de abril de 2024, 07:16 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesParaReporte.h"
#define TAMLINEA 111

//Cabecera para analizar correctamente el orden de lectura de los datos
//9/09/2023   94683380   2.60   11:17:52   12:48:30   124.34   C   S   317.86

//Función en el main que se encarga de todo el proceso
void generarReporte(const char *nombArchDatos,const char *nombArchRep){
    int dd,mm,aa, nroDNI, horaI, horaF, duracionEnS,nroRegistros=0,nroRegProc=0;
    double porcentDcto, tarifPorH, pagoMedicinas, totalIngresos=0.0;
    char car, especialidad, fueRecetado;
    
    ifstream archDat(nombArchDatos, ios::in);
    if (not archDat.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo"<<endl;
        exit(1);
    }
    ofstream archRep(nombArchRep, ios::out);
    if (not archRep.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo"<<endl;
        exit(1);
    }
    
    imprimirEncabezado(archRep);
    
    while(true){
        archDat>>dd;
        if(archDat.eof()) break;
        nroRegistros++;
        archDat>>car>>mm>>car>>aa>>nroDNI>>porcentDcto;
        horaI = convertirHora(archDat);
        horaF = convertirHora(archDat);
        duracionEnS = horaF-horaI;
        archDat>>tarifPorH>>especialidad>>fueRecetado;
        if(fueRecetado=='S')
            archDat>>pagoMedicinas;
        else
            pagoMedicinas=0.0;
//        Selectiva que verifica que se procesen solo las citas que cumplan
//        con tener la duración pedida por el enunciado
//        1:15:30 = 4530 segundos, 2:30:25 = 9025 segundos
        if(especialidad == 'P' and duracionEnS>=4530 and duracionEnS<=9025){
            nroRegProc++;
            imprimeYProcesaDatos(archRep,dd,mm,aa,nroDNI,horaI,horaF,duracionEnS,
                    porcentDcto, tarifPorH, pagoMedicinas, totalIngresos);
        }
    }
    imprimeLinea(archRep,'=');
    archRep<<left<<"Total de ingresos : "<<totalIngresos<<endl;
    imprimeLinea(archRep,'=');
    imprimirEstadisticas(archRep, nroRegistros,nroRegProc);
}

/*Funciones encargadas de Imprimir y Procesar los datos para mostrar luego
tanto el reporte como las estadísticas pedidas*/

void imprimeYProcesaDatos(ofstream &archRep,int dd,int mm,int aa,int nroDNI,
                          int horaI, int horaF, int duracionEnS, 
                          double porcentDcto, double tarifPorH,
                          double pagoMedicinas, double &totalIngresos){
    double duracionEnH = (double)duracionEnS/3600;
    archRep.precision(4);
    archRep<<fixed;
    archRep<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'
           <<setw(4)<<aa<<setfill(' ')<<"  "<<setw(8)<<nroDNI<<"  ";
    imprimeHora(archRep,horaI);
    archRep<<"  ";
    imprimeHora(archRep,horaF);
    archRep<<setw(4)<<' ';
    imprimeHora(archRep,duracionEnS);
    archRep<<setw(7)<<' '<<setw(8)<<duracionEnH<<setw(7)<<' ';
    archRep.precision(2);
    archRep<<setw(6)<<porcentDcto<<'%'<<setw(10)<<' ';
    imprimePagoYSumaIngresos(archRep,tarifPorH,duracionEnH, 
                             pagoMedicinas, totalIngresos);
    archRep<<endl;
}

void imprimePagoYSumaIngresos(ofstream &archRep,double tarifPorH,double duracionEnH,
                              double pagoMedicinas, double &totalIngresos){
    double monto;
    monto = tarifPorH*duracionEnH + pagoMedicinas;
    totalIngresos += monto;
    archRep<<setw(8)<<monto;
}
void imprimirEstadisticas(ofstream &archRep,int nroRegistros,int nroRegProc){
    double porcRegProc = ((double)nroRegProc/nroRegistros)*100;
    archRep<<"ESTADISTICAS OBTENIDAS:"<<endl;
    archRep<<"Cantidad de registros del archivo:"<<setw(23)<<' '
           <<right<<setw(3)<<nroRegistros<<endl;
    archRep<<"Cantidad de registros procesados:"<<setw(24)<<' '
           <<setw(3)<<nroRegProc<<endl;
    archRep<<"Porcentaje de registros procesados:"<<setw(23)<<' '
           <<setw(5)<<porcRegProc<<'%'<<endl;
}

//Funciones Auxiliares
void imprimeHora(ofstream &archRep,int tiempoEnS){
    int hor, min, seg;
    hor = tiempoEnS/3600;
    min = (tiempoEnS - hor*3600)/60;
    seg = tiempoEnS - hor*3600 - min*60;
    archRep<<setfill('0')<<setw(2)<<hor<<':'<<setw(2)<<min<<':'<<setw(2)<<seg
           <<setfill(' ');
}

int convertirHora(ifstream &archDat){
    int hor, min, seg;
    char car;
    archDat>>hor>>car>>min>>car>>seg;
    return (hor*3600 + min*60 + seg);
}

//Funciones para el formato del reporte
void imprimirEncabezado(ofstream &archRep){
    archRep<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    imprimeLinea(archRep,'=');
    archRep<<setw(7)<<' '<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS"
            " EN PEDIATRIA"<<endl;;
    archRep<<setw(7)<<' '<<"ENTRE 1 HORA CON 15 MINUTOS Y 30 SEGUNDOS Y 2 HORAS "
            "30 MINUTOS Y 25 SEGUNDOS DE DURACION"<<endl;
    imprimeLinea(archRep,'=');
    archRep<<left<<setw(12)<<"Fecha"<<setw(11)<<"Paciente"<<setw(11)<<"Inicio"
           <<setw(8)<<"Fin"<<setw(17)<<"Duracion(H:M:S)"<<setw(13)<<"Duracion(H)"
           <<setw(15)<<"% por Seguro"<<setw(24)<<"Pago (cita+medicinas)"<<endl;
    imprimeLinea(archRep,'-');
}

void imprimeLinea(ofstream &archRep,char caracter){
    for(int i=0; i<TAMLINEA; i++)
        archRep<<caracter;
    archRep<<endl;
}