#ifndef CICLODEINSTRUCCION_H_
#define CICLODEINSTRUCCION_H_

//------------BIBLIOTECAS------------

#include <../../utils/include/comunicacion.h>
#include <../include/estructuras.h>
#include <../include/mmu.h>

//------------DECLARACION DE FUNCIONES------------

void* serializarIO_FS_WRITEoIO_FS_READ(t_operandos, uint32_t, uint32_t, uint32_t, tipoInstruccionInterfaz);
void enviarIO_FS_WRITEoIO_FS_READ(t_operandos, int, uint32_t, uint32_t, uint32_t, tipoInstruccionInterfaz);
void* serializarIO_FS_TRUNCATE(t_operandos, uint32_t);
void enviarIO_FS_TRUNCATE(t_operandos, int, uint32_t);
void* serializarIO_FS_CREATEoIO_FS_DELETE(t_operandos, tipoInstruccionInterfaz);
void enviarIO_FS_CREATEoIO_FS_DELETE(t_operandos, int, tipoInstruccionInterfaz);
void enviarCOPY_STRING(int, uint32_t, uint32_t, uint32_t, int, uint8_t, t_log*);
int calcularTamanoOPerando(char*);
void* serializarWAITOSIGNAL(char*, tipoInstruccionesRecursos, int);
void enviarWAITOSIGNAL(char*, int, tipoInstruccionesRecursos);
void* serializarMOV_OUT(uint8_t, int, int, uint32_t);
void enviarMOV_OUT(uint8_t, int, int, int, uint32_t);
void* serializarMOV_IN(uint8_t, int, uint32_t);
int enviarMOV_IN(uint8_t, int, int, uint32_t);
void* serializarRESIZE(uint32_t, int);
void enviarRESIZE(uint32_t, int, int );
int recibirRespuestaRESIZE(int, t_PCB*, int*);
void actualizarTLB(void*, int, int, int);
void* serializarSTDINOSTDOUT(tipo_interfaz, char*, uint32_t, uint32_t);
void enviarSTDINOSTDOUT(tipo_interfaz, char*, uint32_t, uint32_t, int); 
void* serializarIO_GEN_SLEEP(t_operandos, tipo_interfaz);
void enviarIO_GEN_SLEEP(t_operandos, tipo_interfaz, int);
void* serializarPCyPID(uint32_t, uint32_t);
void enviarPCyPID(t_PCB, int, t_log*);
t_instruccionEntera* separarInstruccion(char*);
char* recibirStreamInstruccion(int, t_log*);
t_operandos separarOperandos(char*);
void realizarInstruccion(t_instruccionEntera*, t_PCB*, t_dictionary*, int, void*, int, int, int, char*, int, t_log*, int*);
void realizarInstruccionSET(char*, t_dictionary*);
void realizarInstruccionMOV_IN(char*, t_dictionary*, void*, int, int, char*, int, int, t_log*);
void realizarInstruccionMOV_OUT(char*, t_dictionary*, void*, int, int, char*, int, int, t_log*);
void realizarInstruccionSUM(char*, t_dictionary*);
void realizarInstruccionSUB(char*, t_dictionary*);
void realizarInstruccionJNZ(char*, t_dictionary*);
void realizarInstruccionRESIZE(char*, t_dictionary*, t_PCB*, int, int*, void*, int);
void realizarInstruccionCOPY_STRING(char*, t_dictionary*, int, void*, int, int, char*, int, t_log*);
void realizarInstruccionWAIT(char*, int, t_PCB*, int*);
void realizarInstruccionSIGNAL(char*, int, t_PCB*, int*);
void realizarInstruccionIO_GEN_SLEEP(t_PCB*, char*, int, int*);
void realizarInstruccionIO_STDIN_READoIO_STDOUT_WRITE(t_PCB*, char*, t_dictionary*, void*, int, int, char*, int, int, t_log*, tipo_interfaz, int*);
void realizarInstruccionIO_FS_CREATEoIO_FS_DELETE(t_PCB*, char*, int, tipoInstruccionInterfaz, int*);
void realizarInstruccionIO_FS_TRUNCATE(t_PCB*, char*, int, t_dictionary*, int*);
void realizarInstruccionIO_FS_WRITEoIO_FS_READ(t_PCB*, t_dictionary*, char*, int, tipoInstruccionInterfaz, int*);
void realizarInstruccionEXIT(t_PCB*, int*);
char* etapaFetch(t_PCB*,int, t_log*);
t_instruccionEntera* etapaDecode(char*);
void etapaExecute(t_instruccionEntera*,t_PCB*, t_dictionary*, int, void*, int, int, int, char*, int, t_log*, int*);
void cargarDiccionarioRegistros(t_registrosDeCPU*, t_dictionary*);
void realizarCicloInstruccion(t_PCB*, t_dictionary*, int, int, t_log*, void*, int, int, int, char*, int*);
void manejarInterrupciones(t_PCB, int, int*, t_log*);
void enviarPCBConCodOp(t_PCB, op_code, int);
void* serializarPCBConCodOp(t_PCB, op_code);
#endif