
/*/ 
 * Projecto:  ArchivosDeTextoYModulacionLab03-2023-2
 * Nombre del Archivo:  funciones.cpp
 * Autor: El EnTrEvErAdO
/*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones.h"
#define MAXTEXTO 40
#define TAMLINEA 151

                  /*  - / > [ Funciones en main() ] < / -  */

// Modulo de Emision de Reporte
void emitirReporte(const char *nombArchRep,const char *nombArchTele,
                   const char *nombArchReg,const char *nombArchCanales){
    // Apertura de Archivos && Declaracion de Variables
    ofstream archRep = abrirArchivo_OFS(nombArchRep);
    ifstream archTele = abrirArchivo_IFS(nombArchTele);
    ifstream archReg = abrirArchivo_IFS(nombArchReg);
    ifstream archCanales = abrirArchivo_IFS(nombArchCanales);
    int numCanal;
    // Inicializacion de Elementos de Reporte
    archRep<<fixed; archRep.precision(2);
    // Proceso de Impresion de Reporte
    imprimirEncabezados(archRep,'A');
    while(1){
        archCanales>>numCanal;
        if(archCanales.eof()) break;                                            // Validacion de Fin de Archivo
        archRep<<setw(11)<<"CANAL: ";
        procesarNombreDeCanal(archRep,archCanales);
        archRep<<setw(12)<<"NUMERO: "<<numCanal<<endl;
        procesarRegistrosDeTelevidentes(archRep,archReg,archTele,numCanal);
        imprimirLinea(archRep,TAMLINEA,'=');
    }
}

              /*  - / > [ Funciones de Orden Principal ] < / -  */

// Modulo de Procesamiento de Texto [Version: Nombre de Canal]{Pasa todo a mayusculas}
void procesarNombreDeCanal(ofstream &archRep,ifstream &archCanales){
    // Declaracion de Variables
    int numCar = 0; char letra;
    // Posicionamiento Inicial Hacia Texto
    archCanales>>ws;
    archCanales.get();
    // Iterativa del Proceso de Lectura - Modificacion - Impresion del Texto [Caracter por Caracter]
    while(1){
        letra = archCanales.get();
        if(letra == '/') break;                                                 // Validacion de Fin de Proceso
        letra -= ((letra >= 'a' and letra <= 'z')? 'a' - 'A':0);                // Validacion de Moficiacion de Simbolo por ser 'Letra Minuscula'
        archRep.put(letra);
        numCar++;
    }
    // Impresion de Espacios Exactos para Alineamiento
    archRep<<setw(MAXTEXTO - numCar)<<' ';
}
// Modulo de Busqueda & Impresion de Datos de Televidentes de Un Cierto Canal
void procesarRegistrosDeTelevidentes(ofstream &archRep,ifstream &archReg,
                                     ifstream &archTele,int numCanal){
    // Declaracion & Inicializacion de Variables
    int dni_Reg,numCanal_Eval,hIni,hFin,numMenores = 0,numJovenes = 0;
    int numAdultos = 0,numPersonas = 0,tiempoTotal = 0;
    // Reinicio de Lectura por Futura Busqueda [De Numero de Canal]
    archReg.clear();
    archReg.seekg(0,ios::beg);
    // Proceso de Busqueda & Impresion de Datos de Televidente de Canal
    imprimirEncabezados(archRep,'B');
    while(1){
        archReg>>dni_Reg;
        if(archReg.eof()) break;                                                // Validacion de Fin de Archivo
        while(1){                                                               // Proceso de Lectura de Grupos de Registros de Canal Visto por Televidente
            if(archReg.get() == '\n') break;                                    // Validacion de Fin de Proceso
            archReg>>numCanal_Eval;
            hIni = obtenerHora(archReg);
            hFin = obtenerHora(archReg);
            if(numCanal_Eval == numCanal){                                      // Validacion de Hallazgo de Canal Buscado
                procesarDatosDeTelevidente(archRep,archTele,dni_Reg,hIni,hFin,
                                           numMenores,numJovenes,numAdultos,
                                           numPersonas,tiempoTotal);
            }
        }
    }
    // Impresion de Resumen Parcial de Datos de Canal [Esto se deberia hacer en emitirReporte(), pero dado que NO hay un 'resumenTotal', es más 'bonito' hacerlo aqui]
    emitirResumenParcial(archRep,numMenores,numJovenes,numAdultos,numPersonas,
                         tiempoTotal);
}

             /*  - / > [ Funciones de Orden Secundario ] < / -  */

// Modulo de Validacion de Existencia & Impresion de Datos de Televidente
void procesarDatosDeTelevidente(ofstream &archRep,ifstream &archTele,int dni,
                                int hIni,int hFin,int &numMenores,
                                int &numJovenes,int &numAdultos,
                                int &numPersonas,int &tiempoTotal){
    // Declaracion de Variables
    int dni_Eval; char sexo,empresa,categoria;
    // Reinicio de Lectura por Futura Busqueda [De Nombre de Televidente]
    archTele.clear();
    archTele.seekg(0,ios::beg);
    // Iterativa del Proceso de Validacion de Existencia de Televidente para Impresion de Datos de Registro
    while(1){
        archTele>>dni_Eval;
        if(archTele.eof()) break;                                               // Validacion de Fin de Archivo
        // Validacion de Hallazgo de Cliente
        if(dni_Eval == dni){
            // Proceso de Impresion de Datos Personales de Televidente [Dado que no podemos almacenar el nombre del televidente, debemos imprimirlo de frente, para poder leer los siguientes datos]
            archRep<<setw(12)<<dni<<setw(4)<<' ';
            procesarNombreDeTelevidente(archRep,archTele);
            archRep<<setw(4)<<' '<<left;
            // Continuacion del Proceso de Lectura de Datos de Televidente
            categoria = obtenerCategoria(archTele);
            archTele>>sexo>>empresa;
            // Proceso de Impresion de Datos de Registro de Televidente por Canal Visto
            imprimirRegistro(archRep,sexo,categoria,empresa,hIni,hFin,
                             numMenores,numJovenes,numAdultos,numPersonas,
                             tiempoTotal);
        } else while(archTele.get() != '\n');                                   // Descarte de Datos de Linea
    }
}
// Modulo de Emision de Resumen Parcial de Registros de Canal
void emitirResumenParcial(ofstream &archSalida,int numMenores,int numJovenes,
                          int numAdultos,int numPersonas,int tTotal){
    // Declaracion & Inicializacion de Variables
    int tPromedio = (tTotal/numPersonas);
    double perc_menores = 100*(((double)numMenores)/numPersonas);
    double perc_jovenes = 100*(((double)numJovenes)/numPersonas);
    double perc_adultos = 100*(((double)numAdultos)/numPersonas);
    // Proceso de Impresion de Resumen Parcial [Formato: PREDETERMINADO]
    imprimirLinea(archSalida,TAMLINEA,'-');
    archSalida<<setw(47)<<"PROMEDIO DE TIEMPO QUE VEN LOS TELEVIDENTES";
    archSalida<<"EL CANAL:"<<setw(4)<<' ';
    imprimirHora(archSalida,tPromedio);
    archSalida<<endl<<setw(30)<<"PORCENTAJES SEGUN SU EDAD:";
    archSalida<<endl<<setw(20)<<"MENORES:"<<setw(17)<<perc_menores<<'%'<<endl;
    archSalida<<setw(20)<<"JOVENES:"<<setw(17)<<perc_jovenes<<'%'<<endl;
    archSalida<<setw(20)<<"ADULTOS:"<<setw(17)<<perc_adultos<<'%'<<endl;
    archSalida<<setw(39)<<"TOTAL DE PERSONAS QUE VEN EL CANAL:";
    archSalida<<setw(4)<<numPersonas<<endl;
}

              /*  - / > [ Funciones de Orden Derivado ] < / -  */

// Modulo de Procesamiento de Texto [Version: Nombre de Televidente]{Itera entre Mayusculas y Minusculas sin contar los espacios}
void procesarNombreDeTelevidente(ofstream &archRep,ifstream &archTele){
    // Declaracion de Variables
    bool switchear = true; int numCar = 0; char letra;
    // Posicionamiento Inicial Hacia Texto
    archTele>>ws;
    // Iterativa del Proceso de Lectura - Modificacion - Impresion del Texto [Caracter por Caracter]
    while(1){
        letra = archTele.get();
        if(letra == ' ') break;                                                 // Validacion de Fin de Proceso
        // Validaciones del Proceso de Modificacion de 'Simbolo'
        if(letra == '_') letra = ' ';
        else if(switchear){
            letra -= ((letra >= 'a' and letra <= 'z')?'a'-'A':0);               // Validacion de Moficiacion de Simbolo por ser 'Letra Minuscula'
            switchear = false;
        } else {
            letra += ((letra >= 'A' and letra <= 'Z')?'a'-'A':0);               // Validacion de Moficiacion de Simbolo por ser 'Letra Mayuscula'
            switchear = true;
        }
        archRep.put(letra);
        numCar++;
    }
    // Impresion de Espacios Exactos para Alineamiento
    archRep<<setw(MAXTEXTO - numCar)<<' ';
}
// Modulo de Lectura & Seleccion de Categoria de Retorno por Fecha de Nacimiento [Esto lo hago porque en el reporte primero se imprime el 'sexo' de la persona, y ps esto se lee despues, hmm yo creo q es mas facil de hacer asi]
char obtenerCategoria(ifstream &archTele){
    // Declaracion de Variables
    int dd,mm,aa,fecha; char simbolo;
    // Lectura & Compactacion de Fecha
    archTele>>dd>>simbolo>>mm>>simbolo>>aa;
    fecha = 10000*aa+100*mm+dd;
    // Validacion de Retorno Categoria por Fecha
    if(fecha > 20090000) return 'M';
    if(fecha > 19880000) return 'J';
    return 'A';
}
// Modulo de Impresion de Datos de Registro de Televidente por Canal Visto
void imprimirRegistro(ofstream &archRep,char sexo,char categoria,char empresa,
                      int hIni,int hFin,int &numMenores,int &numJovenes,
                      int &numAdultos,int &numPersonas,int &tiempoTotal){
    // Declaracion de Variables
    int duracion = hFin - hIni;
    // Impresion de Datos de Registro && Actualizacion de Datos por Registro
    if(sexo == 'F') archRep<<setw(16)<<"Femenino";                              // Validacion de Impresion por Sexo
    else archRep<<setw(16)<<"Masculino";                                        // 'else if(sexo == 'M')' tambien puede ser.. pero como en este caso solo hay 2..
    if(categoria == 'M'){                                                       // Validacion de Impresion de Categoria de Edad [Menor]
        archRep<<setw(16)<<"Menor";
        numMenores++;
    } else if(categoria == 'J'){                                                // Validacion de Impresion de Categoria de Edad [Joven]
        archRep<<setw(16)<<"Joven";
        numJovenes++;
    } else if(categoria == 'A'){                                                // Validacion de Impresion de Categoria de Edad [Adulto]
        archRep<<setw(16)<<"Adulto";
        numAdultos++;
    }
    if(empresa == 'A') archRep<<setw(20)<<"TVPUCP";                             // Validacion de Impresion por Empresa Emisora [A]
    else if(empresa == 'B') archRep<<setw(20)<<"CableMas";                      // Validacion de Impresion por Empresa Emisora [B]
    else archRep<<setw(20)<<"TPVision";                                         // 'else if(empresa == 'C')' tambien puede ser.. pero como en este caso solo hay 3..
    archRep<<right;
    imprimirHora(archRep,hIni);
    archRep<<" - ";
    imprimirHora(archRep,hFin);
    archRep<<setw(8)<<' ';
    imprimirHora(archRep,duracion);
    archRep<<endl;
    tiempoTotal += duracion;
    numPersonas++;
}

                  /*  - / > [ Funciones Auxiliares ] < / -  */

// Modulo Auxiliar de Apertura de Archivos IFSTREAM
ifstream abrirArchivo_IFS(const char *nombArch){
    ifstream arch(nombArch,ios::in);
    if(arch.is_open()) return arch;
    cout<<"ERROR DE APERTURA: Archivo "<<nombArch<<endl;
    exit(1);
}
// Modulo Auxiliar de Apertura de Archivos OFSTREAM
ofstream abrirArchivo_OFS(const char *nombArch){
    ofstream arch(nombArch,ios::out);
    if(arch.is_open()) return arch;
    cout<<"ERROR DE APERTURA: Archivo "<<nombArch<<endl;
    exit(1);
}
// Modulo Auxiliar de Lectura & Compactacion de Dato en Formato de Hora
int obtenerHora(ifstream &archEntrada){
    int hor,min,seg; char simbolo;
    archEntrada>>hor>>simbolo>>min>>simbolo>>seg;
    return 3600*hor+60*min+seg;
}
// Modulo Auxiliar de Impresion & Descompactacion de Dato en Formato de Hora
void imprimirHora(ofstream &archSalida,int tiempo){
    int hor = tiempo/3600;
    int min = (tiempo - hor*3600)/60;
    int seg = tiempo - hor*3600 - min*60;
    archSalida.fill('0');
    archSalida<<setw(2)<<hor<<':'<<setw(2)<<min<<':'<<setw(2)<<seg;
    archSalida.fill(' ');
}

                 /*  - / > [ Funciones Decorativas ] < / -  */

// Modulo Decorativo de Impresion de Encabezados de Reporte [Formato: PREDETERMINADO]
void imprimirEncabezados(ofstream &archSalida,char seleccion){
    if(seleccion == 'A'){
        imprimirLinea(archSalida,TAMLINEA,'=');
        archSalida<<setw((TAMLINEA+25)/2)<<"EMPRESA DE OPINION DE MECARDO TP";  // +25 == +32  -7
        archSalida<<" S.  A."<<endl;
        archSalida<<setw((TAMLINEA+15)/2)<<"AVENIDA UNIVERSITARIA 1234";        // +15 == +26 -11
        archSalida<<" San Miguel"<<endl;
        archSalida<<setw((TAMLINEA+11)/2)<<"LIMA - PERU"<<endl;                 // +11
        imprimirLinea(archSalida,TAMLINEA,'=');
        archSalida<<setw((TAMLINEA-6)/2)<<"REGISTRO DE PREFERENCIAS DE LOS";    //  -6 == +31 -37
        archSalida<<"TELEVIDENTES POR CANAL DE PREFERENCIA"<<endl;
        imprimirLinea(archSalida,TAMLINEA,'=');
    } else{
        archSalida<<setw(44)<<"LISTADO DE TELEVIDENTES QUE VEN EL CANAL"<<endl;
        imprimirLinea(archSalida,TAMLINEA,'-');
        archSalida<<setw(11)<<"DNI No."<<setw(5)<<' '<<left;
        archSalida<<setw(MAXTEXTO)<<"NOMBRE"<<setw(4)<<' ';
        archSalida<<setw(16)<<"SEXO"<<setw(16)<<"CATEGORIA";
        archSalida<<setw(20)<<"COMPANIA"<<right;
        archSalida<<setw(12)<<"RANGO"<<setw(23)<<"DURACION"<<endl;
        imprimirLinea(archSalida,TAMLINEA,'-');
    }
}
// Modulo Decorativo de Impresion de Simbolo por Linea
void imprimirLinea(ofstream &archSalida,int medida,char simbolo){
    for(int i = 0;i < medida;i++) archSalida.put(simbolo);
    archSalida<<endl;
}
