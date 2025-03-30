#ifndef KERNEL_ESTRUCTURAS_H_
#define KERNEL_ESTRUCTURAS_H_

//Estructura para almacenar los valores del config
typedef struct
{
	char* valor;
	char* ipMemoria;
	char* puertoMemoria;
    char* ipCpu;
	char* puertoCpuInterrupt;
	char* puertoCpuDispatch;
	char* puertoEscucha;
	int gradoMultiProgramacion;
	char* algoritmoPlanificacion;
	int quantum;
	char* pathCarpeta;
	char** recursos;
	char** instanciasRecursos;
}t_valores;

//Estructura para almacenar los valores de las conexiones
typedef struct
{
	int conexionDispatch;
	int conexionInterrupt;
	int conexionMemoria;
	int conexionInterfazIO;
}t_conexiones;

//Enum de instrucciones consola kernel
typedef enum
{
	EJECUTAR_SCRIPT,
	INICIAR_PROCESO,
	FINALIZAR_PROCESO,
	DETENER_PLANIFICACION,
	INICIAR_PLANIFICACION,
	MULTIPROGRAMACION,
	PROCESO_ESTADO,
	ERROR
}instrucciones;

#endif