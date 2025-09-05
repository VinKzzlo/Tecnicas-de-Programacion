/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "Palabra.h"
#include "Plato.h"
#include "Atencion.h"
#include "FuncionesAuxiliares.h"
#define NOT_FOUND -1

void cargaLexicon(const char *nombArch,struct Palabra *lexicon,
                    int &cantLexicon){
    ifstream archLex(nombArch,ios::in);
    if(not archLex.is_open()){
        cout<<nombArch <<" no se pudo abrir"<<endl;
        exit(1);
    }
    
    char *palabra;
    int polaridad;
    
    while(true){
        palabra = leerCadenaExactaDelim(archLex,',');
        if(archLex.eof())break;
        archLex>>polaridad;
        archLex.get();
        lexicon[cantLexicon].texto = palabra;
        lexicon[cantLexicon].polaridad = polaridad;
        cantLexicon++;
    }
    
}

void cargaPlatos(const char* nombArch, Plato* platos, int& cantPlatos){
    ifstream archPla(nombArch,ios::in);
    if(not archPla.is_open()){
        cout<< nombArch <<" no se pudo abrir"<<endl;
        exit(1);
    }
    
    char *codigo, *nombre;
    double precio;
    
    while(true){
        codigo = leerCadenaExactaDelim(archPla,',');
        if(archPla.eof())break;
        nombre = leerCadenaExactaDelim(archPla,',');
        archPla>>precio;
        archPla.get();
        
        platos[cantPlatos].codigo = codigo;
        platos[cantPlatos].nombre = nombre;
        platos[cantPlatos].precio = precio;
        
        cantPlatos++;
    }
    
}

void cargaAtenciones(const char *nombArch,struct Atencion *atenciones,
               int &cantAtenciones, struct Plato *platos, int cantPlatos){
    ifstream archAtn(nombArch,ios::in);
    if(not archAtn.is_open()){
        cout<< nombArch <<" no se pudo abrir"<<endl;
        exit(1);
    }
    
    int codAtencion, hh, mm, cantPlatPeds;
    char *codPlato;
    
    while(true){
        archAtn>>codAtencion;
        if(archAtn.eof())break;
        archAtn>>hh;
        archAtn.get();//Sacamos los :
        archAtn>>mm;
        atenciones[cantAtenciones].codigo = codAtencion;
        atenciones[cantAtenciones].hora = hh*100+mm;
        atenciones[cantAtenciones].platosAtendidos = new struct Plato[20]{};
        //Asignamos nuevo espacio de una vez, aprovechando que vamos leyendo de a uno
        atenciones[cantAtenciones].comentarios = new struct Comentario[20]{};
        //Inicio lectura de platos
        while(true){
            if(archAtn.get()=='\n')break;
            archAtn>>ws; //Testing
            codPlato = leerCadenaExactaDelim(archAtn,' ');
            archAtn>>cantPlatPeds;
            int posPlato = buscarPlato(codPlato,platos,cantPlatos);
            if(posPlato!=NOT_FOUND){
                double precio = platos[posPlato].precio;
                llenaPlato(atenciones[cantAtenciones],platos[posPlato],
                        codPlato,cantPlatPeds,precio);
            }
        }
        cantAtenciones++;
    }
}

void procesaComentarios(const char *nombArch,struct Atencion *atenciones,
                int cantAtenciones,struct Palabra *lexicon,int cantLexicon){
    ifstream archCom(nombArch,ios::in);
    if(not archCom.is_open()){
        cout<< nombArch <<" no se pudo abrir"<<endl;
        exit(1);
    }
    int codAtencion,posAtencion;
    char *comentario;
    while(true){
        archCom>>codAtencion;
        if(archCom.eof())break;
        posAtencion = buscaAtencion(atenciones,cantAtenciones,codAtencion);
        if(posAtencion!=NOT_FOUND){
            archCom.get();//Sacamos la coma
            comentario = leerCadenaExactaDelim(archCom,'\n');
            int nc = atenciones[posAtencion].cantidadComentarios; 
            atenciones[posAtencion].comentarios[nc].texto = comentario;
            preProcesoYSeparaPalabras(atenciones[posAtencion].comentarios[nc],
                    lexicon,cantLexicon);
            atenciones[posAtencion].cantidadComentarios++; 
        }
        else
            while(archCom.get()!='\n');
    }
    
}

void preProcesoYSeparaPalabras(struct Comentario &aProcesar,
        struct Palabra *lexicon, int cantLexicon){
    aProcesar.pre_procesado = new char[strlen(aProcesar.texto)+1];
    int cont=0;
    char c;
    for(int i=0;aProcesar.texto[i];i++){
        c = aProcesar.texto[i];
        if(isalpha(c) or c == ' '){
            aProcesar.pre_procesado[cont] = tolower(c);
            cont++;
        }
    }
    aProcesar.pre_procesado[cont] = 0; //caracter que marca fin del texto
    cout << aProcesar.pre_procesado<< endl;
    separaProcesaPalabras(aProcesar,aProcesar.pre_procesado,lexicon,cantLexicon);
    
    cout << "Las palabras son: "<<endl;
     for(int i=0;i<aProcesar.cantidad_palabras;i++){
        cout << aProcesar.palabras[i].texto << " - con polaridad: "
                << aProcesar.palabras[i].polaridad <<endl;
    }
    cout <<" La polaridad total es: " << aProcesar.polaridad_total <<endl;
    
    
    cout << endl;
    
}

void separaProcesaPalabras(struct Comentario &aProcesar,
        char *comentPreP,struct Palabra *lexicon,int cantLexicon){
    
    int contLetras=0;
    bool nuevaPalabra=true;
    char *palabra;
    
    for(int i=0;comentPreP[i];i++){ //Para cuando llega a '\0'
        if(nuevaPalabra){
            palabra = new char[30]{};
            contLetras=0;
        }
        if(comentPreP[i]==' '){
            nuevaPalabra = true;
            agregaPalabra(aProcesar,palabra,lexicon,cantLexicon);
        }
        else{//Carga hasta ultima palabra pero no agrega porque termina bucle 
            nuevaPalabra = false;
            palabra[contLetras] = comentPreP[i];
            contLetras++;
        }
    }
     if (contLetras > 0) { //Verifica que falta agregar una palabra
         agregaPalabra(aProcesar,palabra,lexicon,cantLexicon);
    }
}

void agregaPalabra(struct Comentario &aProcesar, char *palabra,
        struct Palabra *lexicon,int cantLexicon){
    int cp = aProcesar.cantidad_palabras;
    aProcesar.palabras[cp].texto = new char[strlen(palabra) + 1]{};
    strcpy(aProcesar.palabras[cp].texto, palabra);
    calculaPolaridad(aProcesar.palabras[cp],lexicon,cantLexicon);
    aProcesar.polaridad_total += aProcesar.palabras[cp].polaridad;
    aProcesar.cantidad_palabras++;
}

void calculaPolaridad(struct Palabra &palabra, struct Palabra *lexicon, int cantLexicon){
    palabra.polaridad = buscaPalabraRetornaPolaridad(palabra.texto,lexicon,cantLexicon);
}

int buscaPalabraRetornaPolaridad(char *palabra, struct Palabra *lexicon, int cantLexicon){
    for(int i=0;i<cantLexicon;i++){
        if(strcmp(palabra,lexicon[i].texto)==0)
            return lexicon[i].polaridad;
    }
    return 0;
}

int buscarPlato(char *codPlato, struct Plato *platos, int cantPlatos){
    for(int i=0;i<cantPlatos;i++){
        if(strcmp(codPlato,platos[i].codigo)==0)
            return i;
    }
    return NOT_FOUND;
}

int buscaAtencion(struct Atencion *atenciones,int cantAtenciones, int codAtencion){
    for(int i=0;i<cantAtenciones;i++){
        if(atenciones[i].codigo == codAtencion)
            return i;
    }
    return NOT_FOUND;
}



void llenaPlato(struct Atencion &atencionSelec, struct Plato platoSelec,
                char *codPlato, int cantPedida,double precio){
    //Vamos llenando el arreglo de platos Atendidos
    int indPla = atencionSelec.cantidadPlatos;
    
    //Copiamos el codigo
    atencionSelec.platosAtendidos[indPla].codigo = new char[strlen(codPlato)+1];
    strcpy(atencionSelec.platosAtendidos[indPla].codigo,codPlato);
    
    //Copiamos el nombre
    atencionSelec.platosAtendidos[indPla].nombre = new char[strlen(platoSelec.nombre)+1];
    strcpy(atencionSelec.platosAtendidos[indPla].nombre,platoSelec.nombre);
    
    //Asignamos la cantidad
    atencionSelec.platosAtendidos[indPla].cantidad = cantPedida;
    
    //Copiamos el precio
    atencionSelec.platosAtendidos[indPla].precio = precio;
    
    atencionSelec.totalVenta += cantPedida*precio;
    atencionSelec.cantidadPlatos++;
}

char *leerCadenaExactaDelim(ifstream &archLex,char delim){
    char *ptrCadena,cadena[200];
    archLex.getline(cadena,200,delim);
    if(archLex.eof()) return nullptr;
    ptrCadena = new char [strlen(cadena)+1];
    strcpy(ptrCadena,cadena);
    return ptrCadena;
}


void imprimeReporte(const char *nombArch,struct Atencion *atenciones,
                    int cantAtenciones){
    ofstream archRep(nombArch,ios::out);
    if(not archRep.is_open()){
        cout<<nombArch <<" no se pudo abrir"<<endl;
        exit(1);
    }
    
    for(int i=0;i<cantAtenciones;i++){
        archRep << "No.  ATENCION  " << atenciones[i].codigo << setw(30) << " "
                << "Atendido a las: " << atenciones[i].hora/100 << ':' << atenciones[i].hora%100<<endl;
        imprimePlatosAtendidos(archRep,
                atenciones[i].platosAtendidos,atenciones[i].cantidadPlatos);
        int polaridadTotal = obtienePolaridadTotalAtencion(atenciones[i].comentarios,
                atenciones[i].cantidadComentarios);
        archRep << "Monto total de la atencion:  " << atenciones[i].totalVenta << endl;
        archRep << "Polaridad total de los comentarios:  " << polaridadTotal << endl;
        archRep<<endl;
    }
    
    
    
}

void imprimePlatosAtendidos(ofstream &archRep,struct Plato *plaAtendidos, int cantPlatos){
    for(int i=0;i<cantPlatos;i++){
        archRep << plaAtendidos[i].codigo << ")  "<< plaAtendidos[i].nombre << "        "
                << plaAtendidos[i].precio << "    "  << plaAtendidos[i].cantidad << "   "
                << plaAtendidos[i].precio*plaAtendidos[i].cantidad<<endl;
    }
}

int obtienePolaridadTotalAtencion(struct Comentario *comentarios,int cantCom){
    int total=0;
    for(int i=0; i<cantCom;i++){
        total += comentarios[i].polaridad_total;
    }
    return total;
}