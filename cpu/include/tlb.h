#ifndef CPU_TLB_H_
#define CPU_TLB_H_

//------------BIBLIOTECAS------------

#include <../../utils/include/utils.h>
#include <../include/estructuras.h>
#include <../../utils/include/comunicacion.h>
#include <../include/estructuras.h>

//------------DECLARACION DE FUNCIONES------------

void reiniciarAgingUsado(int, void*);
void sumarAging(void*, int);
int obtenerEntradaMasVieja(void*,int);
void* serailizarPIDYNumPag(int, int);
void enviarPIDYNumPag(int, int, int);
void* crearTlb(int);
int pedirMarcoMemoria(int, int, int);
int calcularNumMarco(int, void*, int, int, char*, int, t_log*);
void correrAlgoritmoTlb(void*, char*, int, int, int, int, int);
void algoritmoFIFO(void*, int, int, int, int);

#endif