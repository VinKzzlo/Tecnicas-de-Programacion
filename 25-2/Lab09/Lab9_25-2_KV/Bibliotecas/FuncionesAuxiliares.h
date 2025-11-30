/*
 *
 * Proyecto:    Lab9_25_2_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       25/11/2025
 *
 */

#ifndef LAB9_25_2_KV_FUNCIONESAUXILIARES_H
#define LAB9_25_2_KV_FUNCIONESAUXILIARES_H

void cargarCategorias(const char *nombArch,struct Nodo *&lista);
void leerCategoria(ifstream &archIn, struct Categoria &categoria);
void insertarOrdenado(struct Categoria &categoriaNueva, struct Nodo *&lista);

void actualizarCategoriasConReproducciones(const char *nombArch,struct Nodo *lista);
struct Nodo *buscarCategoria(const char *codigo,struct Nodo *lista);
void actualizarCategoria(ifstream &archIn,struct Categoria &categoria);

void calcularPromediosDeDropOff(struct Nodo *lista);
void promedioDropOff(struct Categoria &categoria);

void eliminarNodos(struct Nodo *&lista);

char *leeCadenaExacta(ifstream &archIn, int size, char delim='\n');
int leerDuracion(ifstream &archIn);

void emiteReportePorCategorias(const char *nombArch, struct Nodo *lista);
void imprimeCategoria(ofstream &archRep,const struct Categoria &categoria);
void imprimeDetalleReproducciones(ofstream &archRep,const struct Categoria &categoria);

void imprimeLinea(ofstream &archRep, char car);
void imprimeDuracion(ofstream &archRep, int duracion);
#endif //LAB9_25_2_KV_FUNCIONESAUXILIARES_H