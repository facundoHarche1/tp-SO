//------------BIBLIOTECAS------------

#include <../include/estructuras.h>
#include <../include/inicioYFin.h>
#include <../include/cicloDeInstruccion.h>
#include <../include/tlb.h>
#include <../include/mmu.h>

//------------CODIGO MAIN CPU------------

int main(int argc, char** argv) 
{
    //Inicio el log
    t_log* logger = iniciarLogger();
    log_info(logger, "Arranco el programa");

    //Creo un config y le cargo los valores
    t_config* config = iniciarConfig(argv[1]);
    t_valores valores = cargarConfig(config);

    //Creo la estructura de argumentos para hacer los hilos
    argsEsperarMensaje* argumentosInterrupt = malloc(sizeof(argsEsperarMensaje));
    argsEsperarMensaje* argumentosDispatch = malloc(sizeof(argsEsperarMensaje));

    //creo el pcb
    t_PCB pcb;
    pcb.PC = -1;

    //Creo el flag de las interrupciones
    int* interrupciones = malloc(sizeof(int));
    *interrupciones = 0;

    //Creo y cargo el diccionario de los registros con sus respectivas posiciones de memoria
    t_dictionary* diccionarioRegistros = dictionary_create();

    cargarDiccionarioRegistros(&(pcb.registrosDeCPU), diccionarioRegistros);
    
    //Creo las conexiones
    int conexionKernelDispatch = iniciarServidor(valores.puertoEscuchaDispatch, logger);
    int conexionKernelInterrupt = iniciarServidor(valores.puertoEscuchaInterrupt, logger);
    int conexionMemoria = crearConexion(valores.ipMemoria, valores.puertoMemoria, logger);

    //------------CREO LOS HILOS------------

    //Cargo los argumentos para Dispatch
    argumentosDispatch->cliente = conexionKernelDispatch;
    argumentosDispatch->rol = SERVIDOR;
    argumentosDispatch->logger = logger;
    argumentosDispatch->pcb = &pcb;
    argumentosDispatch->interrupciones = interrupciones;
    sem_init(&(argumentosDispatch->mutexCpu), 0, 1);
    sem_init(&(argumentosDispatch->semRecibirPCB), 0, 1);

    //Creo el hilo Dispatch
    crearHiloEscucha(argumentosDispatch);
    
    //Cargo los argumentos para Interrupt
    argumentosInterrupt->cliente = conexionKernelInterrupt;
    argumentosInterrupt->rol = SERVIDOR;
    argumentosInterrupt->logger = logger;
    argumentosInterrupt->pcb = &pcb;
    argumentosInterrupt->interrupciones = interrupciones;

    //Creo el hilo Interrupt
    crearHiloEscucha(argumentosInterrupt);

    //Le pido el valor de pagina a memoria 
    int tamPagina = pedirTamPag(conexionMemoria);
    
    //------------TLB------------

    //Creo una variable para la tlb
    void* tlb;

    if(valores.cantidadEntradasTlb != 0)
    {
        //Creo la tlb
        tlb = crearTlb(valores.cantidadEntradasTlb);
    }else{

        //Apunta a NULL
        tlb = NULL;
    }
    

    //------------CICLO DE INSTRUCCIONES------------
    while(1)
        {   
            sem_wait(&(argumentosDispatch->semRecibirPCB));
            while(*interrupciones > 0)
            {   
                //Realiza el ciclo de instruccion sin la etapa check interrupt
                realizarCicloInstruccion(&pcb, diccionarioRegistros, conexionMemoria, argumentosDispatch->cliente, logger, tlb, tamPagina, pcb.PID, valores.cantidadEntradasTlb, valores.algoritmoTlb, interrupciones);
                if(*interrupciones < 0)
                {   
                    //Este PC se modifica cuando llega una interrupcion o un proceso termina, por lo que le envia el PCB a kernel y se queda esperando el proximo
                    manejarInterrupciones(pcb, argumentosDispatch->cliente, interrupciones, logger);
                    sem_post(&(argumentosDispatch->mutexCpu));
                }
            }
            
        }

    //Libero recursos
    terminarPrograma(conexionKernelDispatch, conexionKernelInterrupt, conexionMemoria, logger, config, diccionarioRegistros, tlb);

    return 0;
}