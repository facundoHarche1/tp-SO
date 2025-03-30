#ifndef CPU_ESTRUCTURAS_H_
#define CPU_ESTRUCTURAS_H_

//Struct del config
typedef struct
{
    char* ipMemoria;
    char* puertoMemoria;
    char* puertoEscuchaDispatch;
    char* puertoEscuchaInterrupt;
    int cantidadEntradasTlb;
    char* algoritmoTlb;
}t_valores;

//Struct de la instruccion
typedef struct
{
    char* instruccion;
    char* operandos;
}t_instruccionEntera;  

//Struct de los operandos de una instruccion
typedef struct 
{
    char* operando1;
    char* operando2;
    char* operando3;
    char* operando4;
    char* operando5;
}t_operandos;

typedef enum
{
    SET,
    MOV_IN,
    MOV_OUT,
    SUM,
    SUB,
    JNZ,
    RESIZE,
    COPY_STRING,
    WAIT,
    SIGNAL,
    IO_GEN_SLEEP,
    IO_STDIN_READ,
    IO_STDOUT_WRITE,
    IO_FS_CREATE,
    IO_FS_DELETE,
    IO_FS_TRUNCATE,
    IO_FS_WRITE,
    IO_FS_READ,
    EXIT,
}t_enumInstrucciones;

typedef struct
{
    void* tlb;
    int numEntradasTlb;
    int pid;
    int numPag;
    int numMarco;
    
}t_argsHiloFIFO;

#endif