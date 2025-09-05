/* 
 * File:   main.cpp
 * Author:  Vicente Jorge
 * Código: 20222159
 * Created on 9 de octubre de 2023, 06:35 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "funcionesAuxiliares.h"

#define NO_ENCONTRADO -1

void leerAlum(const char *nombArch,int *arrCodeAlu,char *arrEscAlu,
        int &cantAlu){
    int code;
    char escala;
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit (1);
    }
    while(true){
        arch>>code;
        if(arch.eof()) break;
        arch>>ws;
        while(arch.get()!=' ');
        arch>>escala;
        arrCodeAlu[cantAlu]=code;
        arrEscAlu[cantAlu]=escala;
        cantAlu ++;
    }
}

void leerCur(const char *nombArch,int *arrCodeCur,double *arrCredCur,
        int &cantCur){
    int code;
    double cred;
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit (1);
    }
    while(true){
        arch>>code;
        if(arch.eof()) break;
        arch>>ws;
        while(arch.get()!=' ');
        arch>>cred;
        arrCodeCur[cantCur]=code;
        arrCredCur[cantCur]=cred;
        cantCur ++;
    }
}

void leerEsc(const char *nombArch,int *arrAnioEsc,int *arrCicloEsc,
        char *arrTipoEsc,double *arrValorEsc,int &numEsc){
    int anio,ciclo;
    double valor;
    char c,tipo;
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit (1);
    }
    while(true){
        arch>>anio;
        if(arch.eof()) break;
        arch>>c>>ciclo>>tipo>>valor;
        arrAnioEsc[numEsc]=anio;
        arrCicloEsc[numEsc]=ciclo;
        arrTipoEsc[numEsc]=tipo;
        arrValorEsc[numEsc]=valor;
        numEsc ++;
    }
}

void emitirRepDeEscalas(const char *nombArch,int *arrAnioEsc,char *arrTipoEsc,
        int *arrCicloEsc,double *arrValorEsc,int numEsc){
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit (1);
    }
    arch<<setw(25)<<"INFORMACION DE ESCALAS"<<endl;
    imprimirSalto(arch,'=');
    arch<<"AÑO-CICLO"<<setw(10)<<"TIPO"<<setw(10)<<"VALOR"<<endl;
    imprimirSalto(arch,'-');
    for(int i=0;i<numEsc;i++){
        arch<<setw(5)<<arrAnioEsc[i]<<"-"<<arrCicloEsc[i]<<setw(10)
                <<arrTipoEsc[i]<<setw(13)<<arrValorEsc[i]<<endl;
    }
}

void actualizacionMatricula(const char *nombArch,int *arrAnioEsc,
        int *arrCicloEsc,char *arrTipoEsc,int *cantAluEsc,double *cantCredEsc,
        double *totalIngresosEsc,int numEsc,int *arrCodeAlu,char *arrEscAlu,
        int *arrCodeCur,double *arrCredCur,int cantAlu,int cantCur,
        double *arrValorEsc){
    int anio,ciclo,codeAlu,posAlu,posEsc;
    char c;
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit (1);
    }
    while(true){
        arch>>anio;
        if(arch.eof()) break;
        arch>>c>>ciclo>>codeAlu;
        posAlu=buscaPosAlu(arrCodeAlu,codeAlu,cantAlu);
        if(posAlu!=NO_ENCONTRADO){
            posEsc=buscarPosEsc(arrEscAlu[posAlu],arrAnioEsc,arrCicloEsc,
                arrTipoEsc,numEsc,anio,ciclo);
            procesarCursos(arch,posEsc,arrCodeCur,arrCredCur,cantCredEsc,
                    totalIngresosEsc,cantCur,arrValorEsc);
            cantAluEsc[posEsc] ++;
        }
        else{
            while(arch.get()!='\n');
        }
    }
}

void procesarCursos(ifstream &arch,int posEsc,int *arrCodeCur,
        double *arrCredCur,double *cantCredEsc,double *totalIngresosEsc,
        int cantCur,double *arrValorEsc){
    int curso;
    double monto;
    int posCur;
    while(true){
        arch>>curso;
        posCur=buscarPosCur(curso,arrCodeCur,cantCur);
        cantCredEsc[posEsc]+=arrCredCur[posCur];
        monto=arrCredCur[posCur]*arrValorEsc[posEsc];
        totalIngresosEsc[posEsc]+=monto;
        if(arch.get()=='\n') break;
    }
}

void ordenarArrays(int *arrAnioEsc,int *arrCicloEsc,char *arrTipoEsc,
        double  *arrValorEsc,int *cantAluEsc,double *cantCredEsc,
        double *totalIngresosEsc,int numEsc){
    for(int i=0;i<numEsc-1;i++)
        for(int k=i+1;k<numEsc;k++)
            if(cantAluEsc[i]<cantAluEsc[k] or
                    (cantAluEsc[i]==cantAluEsc[k]) and
                    totalIngresosEsc[i]>totalIngresosEsc[k]){
                cambiarInt(arrAnioEsc[i],arrAnioEsc[k]);
                cambiarInt(arrCicloEsc[i],arrCicloEsc[k]);
                cambiarInt(cantAluEsc[i],cantAluEsc[k]);
                cambiarChar(arrTipoEsc[i],arrTipoEsc[k]);
                cambiarDouble(arrValorEsc[i],arrValorEsc[k]);
                cambiarDouble(cantCredEsc[i],cantCredEsc[k]);
                cambiarDouble(totalIngresosEsc[i],totalIngresosEsc[k]);
            }
}

void emitirReporte(const char *nombArch,int *arrAnioEsc,int *arrCicloEsc,
        char *arrTipoEsc,double *arrValorEsc,int *cantAluEsc,
        double *cantCredEsc,double *totalIngresosEsc,int numEsc){
    int num;
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit (1);
    }
    arch.precision(2);
    arch<<fixed;
    imprimirEncabezado(arch);
    for(int i=0;i<numEsc;i++){
        num=i+1;
        arch<<setfill('0')<<setw(2)<<num<<")"<<setfill(' ')<<setw(5)
                <<arrAnioEsc[i]<<"-"<<arrCicloEsc[i]<<setw(12)
                <<arrTipoEsc[i]<<setw(20)<<cantAluEsc[i]<<setw(28)
                <<arrValorEsc[i]<<setw(20)<<cantCredEsc[i]<<setw(28)
                <<totalIngresosEsc[i]<<endl;
    }
    imprimirSalto(arch,'=');
}

void imprimirEncabezado(ofstream &arch){
    arch<<setw(60)<<"INSTITUCION EDUCATIVA_TP"<<endl<<endl;
    arch<<setw(70)<<"RELACION DE INGRESOS POR CICLO Y ESCALAS"<<endl<<endl;
    imprimirSalto(arch,'=');
    arch<<"     CICLO "<<setw(14)<<"ESCALA"<<setw(23)<<"CANT. ALUMNOS"
            <<setw(25)<<"VALOR CREDITO"<<setw(20)<<"CANT. CREDITOS"
            <<setw(30)<<"TOTAL DE INGRESOS"<<endl;
    imprimirSalto(arch,'-');
}

void cambiarInt(int &datoI,int &datoK){
    int aux;
    aux=datoI;
    datoI=datoK;
    datoK=aux;
}

void cambiarDouble(double &datoI,double &datoK){
    double aux;
    aux=datoI;
    datoI=datoK;
    datoK=aux;
}

void cambiarChar(char &datoI,char &datoK){
    char aux;
    aux=datoI;
    datoI=datoK;
    datoK=aux;
}

int buscarPosCur(int curso,int *arrCodeCur,int cantCur){
    for(int i=0;i<cantCur;i++)
        if(arrCodeCur[i]==curso) return i;
    return NO_ENCONTRADO;
}

int buscarPosEsc(char escalaAlu,int *arrAnioEsc,int *arrCicloEsc,
        char *arrTipoEsc,int numEsc,int anio,int ciclo){
    for(int i=0;i<numEsc;i++)
        if(escalaAlu==arrTipoEsc[i] and arrAnioEsc[i]==anio and
                arrCicloEsc[i]==ciclo) return i;
    return NO_ENCONTRADO;
}

int buscaPosAlu(int *arrCodeAlu,int codeAlu,int cantAlu){
    for(int i=0;i<cantAlu;i++)
        if(arrCodeAlu[i]==codeAlu) return i;
    return NO_ENCONTRADO;
}

void imprimirSalto(ofstream &arch,char c){
    for(int i=0;i<150;i++)
        arch<<c;
    arch<<endl;
}