#ifndef CONSOLA_H_
#define CONSOLA_H_

//------------BIBLIOTECAS------------

#include <../../utils/include/utils.h>
#include <../../utils/include/comunicacion.h>
#include <../../kernel/include/estructuras.h>
#include <../../kernel/include/planificador.h>

//------------DECLARACION DE FUNCIONES------------

void consola(argsPlanificacion*);
void ejecutarInstrucciones(argsPlanificacion*, char*, int*);
void leerScript(argsPlanificacion*, char*, char*, int*);
void iniciarProceso(argsPlanificacion*, char*, int*);
void finalizarProcesoEspecifico(argsPlanificacion*, char*);
void hallarProcesoEnColas(argsPlanificacion*, int);
void finalizarProcesoSegunEstado(argsPlanificacion*, t_lista*, t_PCB*, colasEstado);
void procesoEstado(argsPlanificacion*);
void mostrarProcesos(t_log*, t_lista*);
bool recorrerLaCola(argsPlanificacion*, t_lista*, int, colasEstado);
t_PCB* inicializarPCB(int*, t_valores);
instrucciones procesarInstrucciones(char*);
void modificarMultiprogramacion(argsPlanificacion*, int);
void aumentarGrado(argsPlanificacion*, int);
void disminuirGrado(argsPlanificacion*, int);

#endif