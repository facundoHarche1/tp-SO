#ifndef SERIALIZACION_MAIN_H_
#define SERIALIZACION_MAIN_H_

//------------BIBLIOTECAS------------

#include "utils.h"

//------------FUNCIONES------------

void deserializarPCB(void*, t_PCB*);
void deserializarSleep(void*, u_int8_t*);
void deserializarDireccionFisica(void*,u_int32_t*);
void deserealizarInterfaz(void*, int, char*, tipo_interfaz*);
void* serializarPCB(t_PCB);
void* serializarSleep(u_int32_t, u_int8_t);
void* serializarSTDIN(t_peticion_std);
void* serializarSTDOUT(t_peticion_std);
void* serializarPaquete(t_paquete*, int);
void* serializarDireccionFisica(u_int32_t);
void* serializarPaqueteStdin(t_paquete_stdin*,int);
void* serializarInterfaz(int, char*, tipo_interfaz);
t_peticionInstruccion deserializarPeticionInstruccion(void*);
t_identificadorDePseudocodigo deserializarIdentificador(void*);

#endif