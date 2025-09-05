/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   FuncionesAuxiliares.h
 * Autor:  VinKzzlo
 *
 * Creado el 3 de julio de 2025, 22:18
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void cargaLexicon(const char *nombArch,struct Palabra *lexicon,
                    int &cantLexicon);
void cargaPlatos(const char *nombArch,struct Plato *platos,
                    int &cantPlatos);
void cargaAtenciones(const char *nombArch,struct Atencion *atenciones,
                    int &cantAtenciones,struct Plato *platos,int cantPlatos);
int buscarPlato(char *codPlato, struct Plato *platos, int cantPlatos);
void llenaPlato(struct Atencion &atencionSelec, struct Plato platoSelec,
                char *codPlato, int cantPedida,double precio);
void procesaComentarios(const char *nombArch,struct Atencion *atenciones,
                int cantAtenciones,struct Palabra *lexicon,int cantLexicon);
void preProcesoYSeparaPalabras(struct Comentario &aProcesar,
        struct Palabra *lexicon, int cantLexicon);
void separaProcesaPalabras(struct Comentario &aProcesar,
        char *comentPreP,struct Palabra *lexicon,int cantLexicon);
void agregaPalabra(struct Comentario &aProcesar, char *palabra,
        struct Palabra *lexicon,int cantLexicon);
void calculaPolaridad(struct Palabra &palabra, struct Palabra *lexicon, int cantLexicon);
int buscaPalabraRetornaPolaridad(char *palabra, struct Palabra *lexicon,
        int cantLexicon);
int buscaAtencion(struct Atencion *atenciones,int cantAtenciones, int codAtencion);
char *leerCadenaExactaDelim(ifstream &arch,char delim);

void imprimeReporte(const char *nombArch,struct Atencion *atenciones,
                    int cantAtenciones);
void imprimePlatosAtendidos(ofstream &archRep,struct Plato *plaAtendidos, int cantPlato);
int obtienePolaridadTotalAtencion(struct Comentario *comentarios,int cantCom);

#endif /* FUNCIONESAUXILIARES_H */

