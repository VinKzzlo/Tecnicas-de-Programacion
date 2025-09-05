/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "funciones.h"
#define NO_ENCONTRADO -1

void cargarLexicon(struct Palabra *arrPalabra,int &cantPalabras){
    ifstream archLexi("lexicon.csv",ios::in);
    if(not archLexi.is_open()){
        cout<<"lexicon.csv no se pudo abrir"<<endl;
        exit(1);
    }
    cantPalabras = 0;
    char *ptrNombre;
    double polaridad;
    while(true){
        ptrNombre = leerCadenaExactaDelim(archLexi,',');
        if(archLexi.eof()) break;
        archLexi>>polaridad;
        archLexi.get();
        arrPalabra[cantPalabras].texto = ptrNombre;
        arrPalabra[cantPalabras].polaridad = polaridad;
        cantPalabras++;
    }
//    for(int i=0 ; i<cantPalabras ; i++)
//        cout<<arrPalabra[i].texto<<"    "<<arrPalabra[i].polaridad<<endl;
}

char *leerCadenaExactaDelim(ifstream &arch,char delim){
    char *ptrCadena,cadena[200];
    arch.getline(cadena,200,delim);
    if(arch.eof()) return nullptr;
    ptrCadena = new char [strlen(cadena)+1];
    strcpy(ptrCadena,cadena);
    return ptrCadena;
}


void cargarPlatos(struct Plato *arrPlatos,int &cantPlatos){
    ifstream archPlatos("platos.csv",ios::in);
    if(not archPlatos.is_open()){
        cout<<"platos.csv no se pudo abrir"<<endl;
        exit(1);
    }
    cantPlatos = 0;
    char *ptrNombre, *ptrDescripcion;
    double precio;
    while(true){
        ptrNombre = leerCadenaExactaDelim(archPlatos,',');
        if(archPlatos.eof()) break;
        ptrDescripcion = leerCadenaExactaDelim(archPlatos,',');
        archPlatos>>precio;
        archPlatos.get();
        arrPlatos[cantPlatos].codigo = ptrNombre;
        arrPlatos[cantPlatos].nombre = ptrDescripcion;
        arrPlatos[cantPlatos].precio = precio;
        cantPlatos++;
    }
//        for(int i=0 ; i<cantPlatos ; i++)
//            cout<<arrPlatos[i].codigo<<"   "<<arrPlatos[i].nombre<<"    "<<arrPlatos[i].precio<<endl;
}

void procesarAtenciones(struct Atencion *arrAtenciones,struct Plato *arrPlatos,
                        int cantPlatos,int &cantAtenciones){
    ifstream archAtenciones("atenciones.txt",ios::in);
    if(not archAtenciones.is_open()){
        cout<<"atenciones.txt no se pudo abrir"<<endl;
        exit(1);
    }
    cantAtenciones = 0;
    int hora,min, codPedido,cantidadPedida;
    char plato[7], car;
    while(true){
        archAtenciones>>codPedido;
        if(archAtenciones.eof()) break;
        archAtenciones>>hora>>car>>min;
        arrAtenciones[cantAtenciones].platosAtendidos = new struct Plato [20]{};        
        arrAtenciones[cantAtenciones].comentarios = new struct Comentario [20]{};
        while(true){
            archAtenciones>>plato>>cantidadPedida;
            int posArrPlatos = arrAtenciones[cantAtenciones].cantidad_platos;
            arrAtenciones[cantAtenciones].cantidad_platos++;
            int posPlato = buscarPlato(plato,arrPlatos,cantPlatos);
            double precio = arrPlatos[posPlato].precio;
            arrAtenciones[cantAtenciones].codigo = codPedido;
            arrAtenciones[cantAtenciones].platosAtendidos[posArrPlatos].codigo = asignarCadena(arrPlatos[posPlato].codigo);
            arrAtenciones[cantAtenciones].platosAtendidos[posArrPlatos].nombre = asignarCadena(arrPlatos[posPlato].nombre);
            arrAtenciones[cantAtenciones].platosAtendidos[posArrPlatos].precio = arrPlatos[posPlato].precio;
            arrAtenciones[cantAtenciones].platosAtendidos[posArrPlatos].cantidad += cantidadPedida;
            arrAtenciones[cantAtenciones].total_Venta += precio*cantidadPedida;
            arrAtenciones[cantAtenciones].hora = hora*100+min;
            if(archAtenciones.get()=='\n') break;
        }
        cantAtenciones++;
    }
}

void leerComentarios(struct Atencion *arrAtenciones,int cantAtenciones,
                    struct Palabra *arrPalabra,int cantPalabras){
    ifstream archComentarios("comentarios.csv",ios::in);
    if(not archComentarios.is_open()){
        cout<<"comentarios.csv no se pudo abrir"<<endl;
        exit(1);
    }
    int codigoPedido,palabrasSeparadas=0,polaridadAcumulada=0;
    char *ptrCadena,*cadenaPre;
    while(true){
//        cout<<"aaa"<<endl;
        archComentarios>>codigoPedido;
        if(archComentarios.eof()) break;
        int posPedido = buscarPedido(codigoPedido,arrAtenciones,cantAtenciones);
//                cout<<"aaa"<<endl;
//        cout<<posPedido<<endl;
        if(posPedido!=NO_ENCONTRADO){
            archComentarios.get();
//            cout<<"aaa"<<endl;
            ptrCadena = leerCadenaExactaDelim(archComentarios,'\n');
            preprocesarCadena(ptrCadena,cadenaPre); ///////////
//            cout<<cadenaPre<<endl;
            int posArrComentario = arrAtenciones[posPedido].cantidadComentarios;
            arrAtenciones[posPedido].comentarios[posArrComentario].texto = asignarCadena(ptrCadena);
            arrAtenciones[posPedido].comentarios[posArrComentario].pre_procesado = asignarCadena(cadenaPre);
            procesarComentario(cadenaPre,palabrasSeparadas,polaridadAcumulada,arrPalabra,cantPalabras);
            arrAtenciones[posPedido].comentarios[posArrComentario].polaridad_total += polaridadAcumulada;
            arrAtenciones[posPedido].comentarios[posArrComentario].cantidad_palabras += cantPalabras;
            arrAtenciones[posPedido].cantidadComentarios++;
        }else{
            while(archComentarios.get()!='\n');
        }
        
    }
}

void procesarComentario(char *cadenaPre,int &palabrasSeparadas,
        int &polaridadAcumulada,struct Palabra *arrPalabra,int cantPalabras){
    char cadenaAUX[20];
    int pos, polaridad;
    int cantidad = strlen(cadenaPre);
    while(true){
        
        pos = buscarEspacio(cadenaPre);
        cadenaPre[pos]=0;
        strcpy(cadenaAUX,cadenaPre+1+pos);
//        cout<<cadenaAUX<<endl;
        polaridad = buscarLexiCom(cadenaAUX,arrPalabra,cantPalabras);
        polaridadAcumulada+=polaridad;
        cantPalabras++;
        cantidad = cantidad - strlen(cadenaPre);
        if(cantidad==0) break;
    }
            
//            int polaridad = buscarLexiCom(cadenaPre[cant],arrPalabra,cantPalabras);
//            cantPalabras++;
//            polaridadAcumulada += polaridad;
}

void emitirReporte(struct Atencion *arrAtenciones,int cantAtenciones){
    ofstream archReporte("Reporte.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"Reporte.txt no se pudo abrir"<<endl;
        exit(1);
    }
    int acumular = 0;
    for(int i=0 ;i<cantAtenciones ; i++){
        archReporte<<arrAtenciones[i].codigo<<endl;
        imprimirLinea(archReporte,'-');
        for(int k = 0 ; k<arrAtenciones[i].cantidad_platos ; k++){
            archReporte<<arrAtenciones[i].platosAtendidos[k].codigo<<setw(4)<<" ";
            archReporte<<left<<setw(50)<<arrAtenciones[i].platosAtendidos[k].nombre;
            archReporte<<right<<setw(10)<<arrAtenciones[i].platosAtendidos[k].precio<<endl;
//            archReporte<<arrAtenciones[i].comentarios[k].polaridad_total<<endl;
            acumular += arrAtenciones[i].comentarios[k].polaridad_total ;
        }
        archReporte<<"POLARIDAD TOTAL DE LOS COMENTARIOS : "<<acumular<<endl;
        imprimirLinea(archReporte,'=');
        //archReporte<<arrAtenciones[i].
    }
}

void imprimirLinea(ofstream &arch,char car){
    for(int i=0 ; i<140 ; i++)
        arch<<car;
    arch<<endl;
}


int buscarEspacio(const char *cadena){
    int cant = strlen(cadena), i;
    while(true){
        if(cadena[cant]==' '){
            return cant;
        }
        cant--;
    }
}

int buscarLexiCom(char *palabraSeparada,struct Palabra *arrPalabra,int cantPalabras){
    for(int i=0 ; i<cantPalabras ; i++){
        if(strcmp(palabraSeparada,arrPalabra[i].texto)==0){
            return arrPalabra[i].polaridad;
        }
    }
    return 0; //no encuentra la palabra
}


int buscarPedido(int codigoPedido,struct Atencion *arrAtenciones,int cantAtenciones){
    for(int i=0 ; i<cantAtenciones ; i++){
        if(codigoPedido==arrAtenciones[i].codigo){
            return i;
        }
    }
    return NO_ENCONTRADO;
}


void preprocesarCadena(char *cadena, char *&linea_pre_procesada){
    char car, lineaPreProcesada[100];
    int k = 0;
    for(int i=0 ; cadena[i] ; i++){
        car = cadena[i];
        if(isalpha(car) or car ==' '){
            lineaPreProcesada[k] = tolower(car);
            k++;
        }
    }
    lineaPreProcesada [k] = 0;
    linea_pre_procesada = new char [strlen(lineaPreProcesada)+1];
    strcpy (linea_pre_procesada,lineaPreProcesada);
}

char *asignarCadena(const char *cadena){
    char *ptrRetorno;
    ptrRetorno = new char [strlen(cadena)+1];
    strcpy(ptrRetorno,cadena);
    return ptrRetorno;
}

int buscarPlato(char *plato,struct Plato *arrPlatos,int cantPlatos){
    for(int i=0 ; i<cantPlatos ; i++){
        if(strcmp (plato,arrPlatos[i].codigo)==0){
            return i;
        }
    }
    return NO_ENCONTRADO;
}