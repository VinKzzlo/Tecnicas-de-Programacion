/*
 *
 * Proyecto:    Ex1P1_25_2_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       19/10/2025
 *
 */

#ifndef EX1P1_25_2_KV_FUNCIONESAUXILIARES_H
#define EX1P1_25_2_KV_FUNCIONESAUXILIARES_H

void procesarReproduccionesDeStreams(const char *nombArchStreams,const char *nombArchCategorias,
        const char *nombArchIdiomas,const char *nombArchCanales, const char *nombArchReporte);

int leerHoraOFecha(ifstream &archIn, bool esHora);
void imprimeHora(ofstream &archRep, int tiempoSegundos);
void imprimeFecha(ofstream &archRep, int AAAAMMDD);

void imprimeInformacionStream(ofstream &archRep, ifstream &archCategorias, ifstream &archIdiomas,
    int codStream, char letraCategoria, int numCategoria, int numIdioma, int duracionStream);
void imprimeCategoria(ofstream &archRep,ifstream &archCategorias,char letraCategoria,int numCategoria);
void imprimeIdioma(ofstream &archRep, ifstream &archIdiomas,int numIdioma);

void imprimeStreamEnCanales(ofstream &archReporte,ifstream &archCanales,int codStream,int duracionStream,
    int &vecesReproducidas,int &tiempoTotalReprod,double &dropOffMenor,double &dropOffMayor,
            char &letraDOMenor,int &numDOMenor,char &letraDOMayor,int &numDOMayor);

void imprimeEncabezadoCanal(ofstream &archReporte,char codLetCanal,int codNumCanal,int &contCanales,bool &encabezadoImpreso);
void imprimeReproduccion(ofstream &archReporte, int fechaReprod, int horaInicio, int duracionStream,
    double ratingCalidad, double dropOff, int &cantReproducciones,int &tiempoTotalXCanal,double &sumaRating,double &sumaDropOff);

void actualizarMenorMayorDropOff(double dropOff,char codLetCanal,int codNumCanal,double &dropOffMenor,double &dropOffMayor,
    char &letraDOMenor,int &numDOMenor,char &letraDOMayor,int &numDOMayor);

void imprimeResumenXCanal(ofstream &archReporte,int cantReproduccionesCanal,
    int tiempoTotalXCanal,double sumaRatingCanal,double sumaDropOffCanal);

void imprimeResumenStream(ofstream &archReporte,int vecesReproducidas,int tiempoTotalReprod,double dropOffMenor,double dropOffMayor,
            char letraDOMenor,int numDOMenor,char letraDOMayor,int numDOMayor);
void imprimeResumenTotal(ofstream &archReporte,int cantStreams,int duracionTotalReproduccion);

void imprimeCadena(ofstream &archRep,ifstream &archIn, bool enMayus);
void saltarCadena(ifstream &archIn,char delim);

void imprimeEncabezado(ofstream &archReporte);
void imprimeLinea(ofstream &archReporte, char car);



#endif //EX1P1_25_2_KV_FUNCIONESAUXILIARES_H