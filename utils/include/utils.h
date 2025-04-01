#ifndef UTILS_MAIN_H_
#define UTILS_MAIN_H_

//------------BIBLIOTECAS------------

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <commons/log.h>
#include <commons/config.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <commons/collections/queue.h>
#include <commons/collections/list.h>
#include <commons/collections/dictionary.h>
#include <commons/bitarray.h>
#include <commons/temporal.h>
#include <math.h>

//------------ENUMS------------

//Codigos de operacion
typedef enum
{
	//GENERICAS
	PCB,
	MENSAJE,

	//INTERFACES
	INTERFAZ,

	//KERNEL
	INTERRUPCION_QUANTUM,	//Interrupcion de quantum kernel->CPU
	INTERRUPCION_FINALIZAR,	//Interrupcion de finalizar proceso kernel->CPU

	//MEMORIA
	TEXTO_STDIN,  //IO manda a memoria dirFisica,tamanio del registro y texto
	HACER_RESIZE, //CPU le pide a memoria hacer un resize
	PEDIDO_MOV_IN, //Lo envia CPU a memoria para ejecutar un mov in
	PEDIDO_MOV_OUT, //Lo envia CPU a memoria para ejecutar un mov out
	PETICION_MARCO, //Me lo envía CPU cuando quiere un marco a partir de una pagina y un pid
	CONTENIDO_STDOUT, //Entrada salida le manda la direccion a memoria para recibir el texto
	PATH_INSTRUCCIONES,
	AVISO_FINALIZACION, //Lo envia kernel a memoria para avisarle de finalizar un proceso
	PETICION_INSTRUCCION, //CPU le manda a memoria pidiendole una instruccion
	PETICION_TAMANO_PAGINA, //Lo envia cpu a memoria para poder saber el tamano de una pagina

	//!A PARTIR DE ACA TODOS ESTOS SE PUEDEN MANDAR A ENUMS DIFERENTES

	//SE PUEDE CAMBIAR MEMORIA
	RESIZE_OK,
	ENVIO_DATO, //Memoria envia el dato leído a partir de una dirección física
	ENVIO_MARCO,
	OUT_OF_MEMORY, //No hubo espacio suficiente para hacer el resize
	ENCONTRO_PATH,
	DATO_ESCRITO_OK, //Lo envia memoria confirmando que el dato ha sido escrito en espacio usuario
	NO_ENCONTRO_PATH,
	PETICION_ACCESO_EU, //Se lo mandan a memoria para pedirle acceder a espacio usuario
	ENVIO_TAMANO_PAGINA, //Lo envia memoria a cpu como respuesta de la peticion del tamano de pagina

	//SE PUEDE CAMBIAR KERNEL
	FIN_DE_QUANTUM,	//Motivo de desalojo = fin de quantum CPU->kernel
	SOLICITUD_INTERFAZ,	//Motivo de desalojo = proceso a blocked CPU->kernel
	PROCESO_FINALIZADO,	//Motivo de desalojo = finalizo el proceso CPU->kernel
	ENVIO_INSTRUCCION_STDIN, //Lo envia cpu a kernel para realizar la instruccion IO_STDIN_READ
	ENVIO_INSTRUCCION_STDOUT, //Lo envia cpu a kernel para realizar la instruccion IO_STDOUT_WRITE

	//Se PUEDE CAMBIAR INTERFACES
	DORMIR_INTERFAZ,

	//Se PUEDE CAMBIAR CPU
	RECURSOS,	//CPU utilizo una funcion SIGNAL o WAIT
	INSTRUCCION,
	RECEPCION_INSTRUCCION,
	PROCESO_FINALIZADO_MANUAL, //Motivo de desalojo = finalizo el proceso manualmente

}op_code;

typedef enum
{
	PETICION_GENERICA,
	PETICION_STDIN,
	PETICION_STDOUT,
	CREAR_ARCHIVOFS,
	BORRAR_ARCHIVOFS,
	TRUNCAR_ARCHIVO,
	ESCRIBIR_ARCHIVO,
	LEER_ARCHIVO
}tipoDePeticion;

typedef enum
{
	NEW,
	READY,
	PRIORITARIA,
	BLOCKED
}colasEstado;

//Codigos de operacion
typedef enum
{
	SERVIDOR,
	CLIENTE,
	INTERFACES
}tipo_comunicacion;

//Tipos de interfaces
typedef enum
{
	GENERICA,
	STDIN,
	STDOUT,
	DIALFS
}tipo_interfaz;

//Tipos de instrucciones interfaces
typedef enum
{
	SLEEP,
	READ,
	WRITE,
	FS_CREATE,
	FS_DELETE,
	FS_TRUNCATE,
	FS_WRITE,
	FS_READ
}tipoInstruccionInterfaz;

typedef enum
{
	INTERRUPT_WAIT,
	INTERRUPT_SIGNAL
}tipoInstruccionesRecursos;

typedef enum
{
	KERNEL,
	MEMORIA
}quienEscucha;

//------------ESTRUCTURAS------------

//Estructura para las colas
typedef struct {
    t_queue* cola;
    pthread_mutex_t mutex;
	sem_t elementos;
}t_cola;

//Estructura para las listas
typedef struct {
    t_list* lista;
    pthread_mutex_t mutex;
}t_lista;

//Estructura para las instrucciones
typedef struct
{
	char* instruccion;
	int largoInstruccion;
}t_instruccion;

typedef struct //Estructura que envia CPU a memoria pidiendo una instruccion
{
	uint32_t PID;
	uint32_t PC;
}t_peticionInstruccion; 

typedef struct // Nodo de lista de procesos
{
	uint32_t PID;
	t_list* instrucciones;
}t_direccionProceso;

typedef struct // Estructura que envia Kernell a memoria pidiendo hacer decode de un archivo de pseudoCodigo
{
	uint32_t PID;
	uint8_t largoCadena;
	char* path;
}t_identificadorDePseudocodigo;

//Estructura de los registros de la CPU
typedef struct
{
	uint32_t PC;	//Program Counter
	uint32_t EAX;	//Registros numeros de 32 bits
	uint32_t EBX;
	uint32_t ECX;
	uint32_t EDX;
	uint32_t SI;	//Direccion logica de memoria de origen donde se va a copiar un string
	uint32_t DI;	//Direccion logica de memoria de destino donde se va a copiar un string
	uint8_t AX;		//Registros numeros de 8 bits
	uint8_t BX;
	uint8_t CX;
	uint8_t DX;
}t_registrosDeCPU;

//Estructura de las program control board (PCB para los amigos)
typedef struct
{
	uint32_t PID;		//Identificador del proceso
	uint32_t PC;		//Program Counter, numero de la prox instruccion a ejecutar
	uint32_t quantum;	//Unidad de tiempo de RR (y VRR)
	t_registrosDeCPU registrosDeCPU;
}t_PCB;

//Estructura del buffer
typedef struct
{
	int size;
	void* stream;
}t_buffer;

//Estructura de los paquetes
typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
}t_paquete;

typedef struct
{
	op_code codigo_operacion;
	u_int32_t direccionFisica;
	t_buffer* buffer;
}t_paquete_stdin;

typedef struct
{
	uint32_t direccionFisica;
	int largoCadena;
	char* cadena;
}t_info_stdin;

//Estructura que se envia a memoria para acceder a espacio usuario
typedef struct
{
    uint32_t PID;
    uint32_t dirFisica;
    uint8_t tamanio;
}t_peticion_acceso_eu;

typedef struct 
{
	uint32_t direcFisica;
	uint8_t tamanio;
	uint32_t PID;
	char* cadena;
}t_peticion_std;


typedef struct 
{
	
	uint32_t largoNombre;
	uint8_t direcLogica;
	uint32_t nuevoTamanio;
	uint32_t regPuntero;
	uint32_t PID;
	char* nombrArchivo;
}t_peticion_fs;

//Estructura que envia memoria con el dato leído
typedef struct
{
	int tamanio;
	void* dato;
}t_dato_leido;

//Estructura para los argumentos de los hilos escucha
typedef struct 
{
	int codOp;
	int cliente;
	int tamanioPagina;
	int retardoRespuesta;
	int* fd;
	int* interrupciones;
	char* path;
	void* memoria;
	op_code interfaz;
	quienEscucha escucha;
	tipo_comunicacion rol;
	t_PCB* pcb;
    t_log* logger;
	t_list* directorio;
	t_list* listaProcesos;
	t_lista* interfacesSTDIN;
	t_lista* interfacesSTDOUT;
	t_lista* interfacesDIALFS;
	t_lista* interfacesGenericas;
	t_bitarray* framesMemoria;
	sem_t mutexCpu;
	sem_t semRecibirPCB;
}argsEsperarMensaje;

typedef struct
{
	pthread_mutex_t mutex;
	sem_t continua;
	char* nombre;
	int socket;
}t_elemento_interfaces;

typedef struct 
{
    int PID;
    t_list* paginas;
}t_tabla_paginas;

typedef struct
{
    int numeroPagina;
    int marco;
}t_pagina;

typedef struct
{
	int retardoRespuesta;
    int tamanoPagina;
	int tamanoMemoria;
	char* puertoEscucha;
	char* pathPruebas;
}t_valoresM;

//Estructura de los archivos FS
typedef struct
{
	char* nombre;
	uint32_t tamanio;
	int cantidadDeBloques;
	int tamanioDeBloques;
}t_archivo_dialfs;

//------------FUNCIONES------------

t_cola* inicializarColasYSemaforos();
t_lista* inicializarListasYSemaforos();

#endif