#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

//------------BIBLIOTECAS------------

#include <../include/inicioYFin.h>
#include <../include/estructuras.h>
#include <../../utils/include/utils.h>
#include <../../utils/include/comunicacion.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>

//------------ DECLARACION DE FUNCIONES ------------

void iniciarArchivos(char*, char*, t_log*);
void iniciarBloques(t_config *);
t_valores_bloques cargarValores(t_config* );
t_valores_bloques *crearBloque(char *);
void crearArchivoDeBloques(char*, uint32_t , uint32_t, t_log*);
t_list* bloquesLibres(int, t_bitarray*);
void ocuparBloques(t_list*, t_bitarray*);
int buscarPrimerBloque(void);
void iniciarBitmap(char*, uint32_t, t_log*);
t_metadata *crearMetadata(int);
bool esIgualBloque(void*);
void compactarBitMap(char*, char*, int, int, t_log*);
int compactarPrimerosArchivos(char*, char*, int);
void setearNBits(int, int);
bool verificarDisponibilidadBloques(int, int);

//----------- PETICIONES ---------------
void borrarArchivo(char*, char*, t_log*, int);
void truncarArchivo(char*, char*, int, uint32_t, int, t_log*);
void crearArchivo(char*, char*, t_log* );
void cargarTamanioMetadata(t_metadata*, uint32_t);
void actualizarMetadata(char*, t_metadata*);
void escribirArchivo(char*, char*, uint32_t, uint32_t, void*, int, t_log*);
void* leerArchivo(char*, char*, uint32_t, uint32_t, int, t_log*);

//VARIABLES GLOBALES
#endif