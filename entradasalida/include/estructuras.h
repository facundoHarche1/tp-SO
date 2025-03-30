#ifndef ENTRADASALIDA_ESTRUCTURAS_H_
#define ENTRADASALIDA_ESTRUCTURAS_H_

#include <../../utils/include/utils.h>
//------------ESTRUCTURAS DE CONFIGURACIONES------------

//Estructura para leer el config
typedef struct
{
	int blockCount;
	int blockSize;
	int tiempoUnidadTrabajo;
	int retrasoCompactacion;
    char* ipKernel;
    char* ipMemoria;
	char* puertoKernel;
	char* puertoMemoria;
	char* tipoInterfaz;
	char* pathDialfs;
}t_valores;

typedef struct 
{
	int blockCount;
	int blockSize;
	int retrasoCompactacion;
}t_valores_bloques;

typedef struct 
{
	char* posicion;
	int tamanio;
	t_bitarray* bitarray;
}t_bitmap;

typedef struct 
{
	uint32_t tamanioArchivo;
	uint32_t bloqueInicial;
}t_metadata;


#endif
