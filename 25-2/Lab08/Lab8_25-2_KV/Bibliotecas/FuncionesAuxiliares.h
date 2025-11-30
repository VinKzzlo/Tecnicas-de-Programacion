/*
 *
 * Proyecto:    Lab8_25_2_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       18/11/2025
 *
 */

#ifndef LAB8_25_2_KV_FUNCIONESAUXILIARES_H
#define LAB8_25_2_KV_FUNCIONESAUXILIARES_H


void cargarCategorias(const char *nombArch, struct Categoria *arrCategorias, int &cantidadCategorias);
void cargarReproduccionesEnCats(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias);
void cargarComentarios(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias);

void ordenarArreglosPorNombreCategoria(struct Categoria *arrCategorias,int cantidadCategorias);
void cambiarCategorias(struct Categoria &catI, struct Categoria &catJ);

char *leerCadenaExacta(ifstream &archIn, char delim='\n');
int leerHora(ifstream &archIn);

int buscarCategoria(char *codCategoria,struct Categoria *arrCategorias,int cantidadCategorias);

void imprimeReportePorCategorias(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias);
void imprimeReproduccion(ofstream &archRep, struct Reproduccion reproduccion);
void imprimeComentarios(ofstream &archRep,char **comentarios, int numComentarios);
void imprimeLinea(ofstream &archOut, int size, char car);
void imprimeHora(ofstream &archOut, int tiempoSegundos);

#endif //LAB8_25_2_KV_FUNCIONESAUXILIARES_H