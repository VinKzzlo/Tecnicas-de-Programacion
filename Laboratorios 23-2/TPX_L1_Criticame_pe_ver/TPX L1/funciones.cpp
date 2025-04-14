
/*/ 
 * Projecto:  TPX_L1
 * Nombre del Archivo:  funciones.cpp
 * Autor: Critical Cyndx
/*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones.h"
#define TAMLINEA 162

                        /*  - / Funciones en Main / -  */

// Modulo Principal
void emitirReporte(void){
    // Declaracion de Variables
    int dni,fechaNac,tiempoP,tiempoA,canal_1,canal_2,canal_3,cantMujeres = 0;
    int cantHombres = 0,cantAdultos = 0,cantMenores = 0,cantRegistrados = 0;
    int cantDescripcion_1 = 0,cantDescripcion_2 = 0,cantDescripcion_3 = 0;
    int cantDescripcion_4 = 0,sumaTiempos_Desc5 = 0,cantDescripcion_6 = 0;
    int cantDescripcion_7 = 0,totalCanalesVistos = 0;;
    char sexo,compania;
    // Impresion de Encabezados
    imprimirEncabezado();
        // Iterativa del Proceso de Lectura, Procesamiento e Impresion de Datos
        while(1){
            cin>>dni;
            if(cin.eof()) break;
            cantRegistrados++;
            cin>>sexo;
            fechaNac = obtenerFecha_Hora('F');
            tiempoP = obtenerFecha_Hora('H');
            tiempoA = obtenerFecha_Hora('H');
            cin>>canal_1>>canal_2>>canal_3>>compania;
            procesarImprimirDatos(dni,fechaNac,tiempoP,tiempoA,canal_1,
              canal_2,canal_3,sexo,compania,cantDescripcion_1,cantDescripcion_2,
              cantDescripcion_3,cantDescripcion_4,sumaTiempos_Desc5,
              cantDescripcion_6,cantDescripcion_7,cantMujeres,cantHombres,
              cantAdultos,cantMenores,totalCanalesVistos);
        }
    // Impresion de Resumen
    imprimirResumen(cantRegistrados,cantDescripcion_1,cantDescripcion_2,
        cantDescripcion_3,cantDescripcion_4,sumaTiempos_Desc5,cantDescripcion_6,
        cantDescripcion_7,cantMujeres,cantHombres,cantAdultos,cantMenores,
        totalCanalesVistos);
}

                      /*  - / Funciones Principales / -  */

// Modulo de Procesamiento e Impresion de Datos
void procesarImprimirDatos(int dni,int fechaNac,int tiempoP,int tiempoA,
                    int canal_1,int canal_2,int canal_3,char sexo,char compania,
                    int &cantDescripcion_1,int &cantDescripcion_2,
                    int &cantDescripcion_3,int &cantDescripcion_4,
                    int &sumaTiempos_Desc5,int &cantDescripcion_6,
                    int &cantDescripcion_7,int &cantMujeres,int &cantHombres,
                    int &cantAdultos,int &cantMenores,int &totalCanalesVistos){
    // Declaracion de Variables
    bool mujer = false,hombre = false,adulto = false,menor = false,joven=false;
    int duracion = tiempoA-tiempoP;
    double horasDeDuracion = (double)duracion/3600;
    // Proceso de Impresion de Reporte por Partes
    cout<<fixed<<setw(12)<<dni<<left<<setw(8)<<' ';
    imprimirSexo(12,sexo,mujer,hombre,cantMujeres,cantHombres);
    cout<<setw(8)<<' ';
    imprimirCategoria(12,fechaNac,menor,joven,adulto,cantMenores,cantAdultos);
    cout<<right<<setw(8)<<' ';
    imprimirHora(tiempoP);
    cout<<setw(8)<<' ';
    imprimirHora(tiempoA);
    cout<<setw(8)<<' ';
    imprimirHora(duracion);
    cout<<setprecision(4)<<setw(18)<<horasDeDuracion<<setprecision(2);
    imprimirCanales(12,canal_1,canal_2,canal_3,totalCanalesVistos);
    cout<<left<<setw(8)<<' ';
    imprimirCompania(8,compania);
    cout<<right<<endl;
    // Validacion de Condiciones para Estadisticas
    validarCondiciones(mujer,hombre,adulto,menor,joven,tiempoA,tiempoP,
                duracion,canal_1,canal_2,canal_3,compania,cantDescripcion_1,
                cantDescripcion_2,cantDescripcion_3,cantDescripcion_4,
                sumaTiempos_Desc5,cantDescripcion_6,cantDescripcion_7);
}
// Modulo de Impresion de Estadisticas de Resumen
void imprimirResumen(int cantRegistrados,int cantDescripcion_1,
            int cantDescripcion_2,int cantDescripcion_3,int cantDescripcion_4,
            int sumaTiempos_Desc5,int cantDescripcion_6,int cantDescripcion_7,
            int cantMujeres,int cantHombres,int cantAdultos,int cantMenores,
            int totalCanalesVistos){
    // Declaracion de Variables
    int tiempoPromedio_C5 = sumaTiempos_Desc5/(cantMenores+cantAdultos);
    // Activar los comentados en caso las estadisticas de los porcentajes refieran al total de personas y no solo al conjunto por genero.
    double porcentajeC6 = (double)cantDescripcion_6/cantMujeres;
    double porcentajeC7 = (double)cantDescripcion_7/cantHombres;
//    double porcentajeC6 = (double)cantDescripcion_6/cantRegistrados;
//    double porcentajeC7 = (double)cantDescripcion_7/cantRegistrados;
    double porcentajeC8 = (double)cantAdultos/cantRegistrados;
    double promedioCanales = (double)totalCanalesVistos/cantRegistrados;
    // Impresion de Datos de Resumen
    imprimirLinea(TAMLINEA,'=');
    cout<<setw(8)<<' '<<"ESTADISTICAS OBTENIDAS:"<<endl<<setw(8)<<' ';
    cout<<"Cantidad de televidentes registrados"<<setw(67)<<cantRegistrados;
    cout<<endl<<setw(8)<<' '<<"Cantidad de menores que ven entre las 14:00:00 ";
    cout<<"y las 19:00:00"<<setw(42)<<cantDescripcion_1<<endl<<setw(8)<<' ';
    cout<<"Cantidad de mujeres que adultas que NO ven television entre las";
    cout<<" 9:30:00 y las 12:45"<<setw(20)<<cantDescripcion_2<<endl;
    cout<<setw(8)<<' '<<"Cantidad de Hombres jovenes que ven mas de 3 horas y ";
    cout<<"media"<<setw(45)<<cantDescripcion_3<<endl<<setw(8)<<' ';
    cout<<"Cantidad de personas que ven los canales 770, 312 o 577, ";
    cout<<"pero no 314 ni 555"<<setw(28)<<cantDescripcion_4<<endl<<setw(8)<<' ';
    cout<<"Tiempo promedio que ven los menores y adultos"<<setw(50)<<' ';
    imprimirHora(tiempoPromedio_C5);
    cout<<endl<<setw(8)<<' '<<"Porcentaje de mujeres que ve TVPUCP";
    cout<<setw(67)<<100*porcentajeC6<<'%'<<endl<<setw(8)<<' '<<"Porcentaje de ";
    cout<<"hombres jovenes que ve TPVision"<<setw(57)<<100*porcentajeC7<<'%';
    cout<<endl<<setw(8)<<' '<<"Porcentaje de adultos registrados";
    cout<<setw(69)<<100*porcentajeC8<<'%'<<endl<<setw(8)<<' '<<"Promedio de ";
    cout<<"canales que ven los televidentes"<<setw(59)<<promedioCanales<<endl;
    imprimirLinea(TAMLINEA,'=');
}

                      /*  - / Funciones Secundarias / -  */

// Modulo de Impresion de Datos de Columna [Sexo]
void imprimirSexo(int espaciado,char sexo,bool &mujer,bool &hombre,
            int &cantMujeres,int &cantHombres){
    // Validacion por Sexo
    if(sexo == 'F'){
        cout<<setw(espaciado)<<"Femenino";
        mujer = true;
        cantMujeres++;
    }else{
        cout<<setw(espaciado)<<"Masculino";
        hombre = true;
        cantHombres++;
    }
}
// Modulo de Impresion de Datos de Columna [Categoria]
void imprimirCategoria(int espaciado,int fechaNac,bool &menor,bool &joven,
                    bool &adulto,int &cantMenores,int &cantAdultos){
    // Validacion por Fecha de Nacimiento
    if(fechaNac > 20090000) {
        cout<<setw(espaciado)<<"Menor";
        menor = true;
        cantMenores++;
    }else if(fechaNac > 19880000){
        cout<<setw(espaciado)<<"Joven";
        joven = true;
    }else {
        cout<<setw(espaciado)<<"Adulto";
        adulto = true;
        cantAdultos++;
    }
}
// Modulo de Impresion de Datos de Columna [Canales]
void imprimirCanales(int espaciado,int canal_1,int canal_2,int canal_3,
                int &totalCanalesVistos){
    cout<<setw(espaciado)<<' ';
        // Validaciones por Posible Canal Nulo
        if(canal_1 != 0){
            cout<<setw(3)<<canal_1;
            totalCanalesVistos++;
                if(canal_2 != 0){
                    cout <<'/'<<setw(3)<<canal_2;
                    totalCanalesVistos++;
                        if(canal_3 != 0){
                            cout<<'/'<<setw(3)<<canal_3;
                            totalCanalesVistos++;
                        } else cout<<setw(4)<<' ';
                }else cout<<setw(8)<<' ';
        }else cout<<setw(12)<<' ';
}
// Modulo de Impresion de Datos de Columna [Categoria]
void imprimirCompania(int espaciado,char compania){
    // Validacion por Compania
    if(compania == 'A') cout<<setw(espaciado)<<"TVPUCP";
    else if(compania == 'B') cout<<setw(espaciado)<<"CableMas";
    else if(compania == 'C') cout<<setw(espaciado)<<"TPVision";
}
// Modulo de Validacion de Condiciones de Estadisticas
void validarCondiciones(bool mujer,bool hombre,bool adulto,bool menor,
                    bool joven,int tiempoA,int tiempoP,int duracion,
                    int canal_1,int canal_2,int canal_3,char compania,
                    int &cantDescripcion_1,int &cantDescripcion_2,
                    int &cantDescripcion_3,int &cantDescripcion_4,
                    int &sumaTiempos_Desc5,int &cantDescripcion_6,
                    int &cantDescripcion_7){
    // Validacion de Condicion 1
    if(menor and tiempoP > 14*3600 and tiempoA < 19*3600) 
        cantDescripcion_1++;
    // Validacion de Condicion 2
    if(mujer and adulto and (tiempoA <= 9.5*3600 or tiempoP >= 12.75*3600))
        cantDescripcion_2++;
    // Validacion de Condicion 3
    if(hombre and joven and duracion > 3.5*3600) 
        cantDescripcion_3++;
    // Validacion de Condicion 4
    cuartaCondicionValidada(canal_1,canal_2,canal_3,cantDescripcion_4);
    // Validacion de Condicion 5
    if(menor or adulto) sumaTiempos_Desc5 += duracion;
    // Validacion de Condicion 6
    if(mujer and compania == 'A') cantDescripcion_6++;
    // Validacion de Condicion 7
    if(hombre and joven and compania == 'C') cantDescripcion_7++;
}

                      /*  - / Funciones Derivadas / -  */

// Modulo Especifico de Validación de la Cuarta Condición
void cuartaCondicionValidada(int canal_1,int canal_2,int canal_3,int &cantidad){
    // Validacion de Condicion 4
    if(canal_1 != 314 and canal_1!= 555 and canal_2 != 314 and canal_2!= 555 
        and canal_3 != 314 and canal_3!= 555){
        if(canal_1 == 770 or canal_1 == 312 or canal_1 == 577 or
            canal_2 == 770 or canal_2 == 312 or canal_2 == 577 or
            canal_3 == 770 or canal_3 == 312 or canal_3 == 577) 
                cantidad++;
    }
}

                      /*  - / Funciones Auxiliares / -  */

void imprimirEncabezado(void){
    cout<<setw((35+TAMLINEA)/2)<<"EMPRESA DE OPINION DE MERCADO S. A."<<endl;
    imprimirLinea(TAMLINEA,'=');
    cout<<setw((44+TAMLINEA)/3)<<"REGISTRO DE PREFERENCIAS DE LOS TELEVIDENTES";
    cout<<endl;
    imprimirLinea(TAMLINEA,'=');
    cout<<setw(11)<<"DNI No."<<setw(15)<<"Sexo"<<setw(22)<<"Categoria";
    cout<<setw(19)<<"Hora(P)"<<setw(16)<<"Hora(A)"<<setw(21)<<"Duracion(H:M:S)";
    cout<<setw(18)<<"Duracion(H)"<<setw(15)<<"Canales"<<setw(20)<<"Compania";
    cout<<endl;
    imprimirLinea(TAMLINEA,'-');
}
// Modulo de Impresion de Datos en Linea
void imprimirLinea(int medida,char simbolo){
    for(int i=0;i<medida;i++) cout.put(simbolo);
    cout<<endl;
}
// Modulo de Lectura, Calculo y Asignación de Hora en formato HH:MM:SS en Segundos
int obtenerFecha_Hora(char seleccion){
    int dd_hor,mm_min,aa_seg;
    char simbolo;
    cin>>dd_hor>>simbolo>>mm_min>>simbolo>>aa_seg;
    if(seleccion == 'F')return aa_seg*10000+100*mm_min+dd_hor;
    else return aa_seg+mm_min*60+dd_hor*3600;
}
// Modulo de Descompactación e Impresion de Dato Temporal en formato HH:MM:SS
void imprimirHora(int valor){
    int hor,min,seg;
    hor = valor/3600;
    min = (valor-hor*3600)/60;
    seg = (valor-hor*3600-min*60);
    cout.fill('0');
    cout<<setw(2)<<hor<<':'<<setw(2)<<min<<':'<<setw(2)<<seg;
    cout.fill(' ');
}
