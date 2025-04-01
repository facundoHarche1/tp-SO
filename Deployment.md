# tp-scaffold

Esta es una plantilla de proyecto diseñada para generar un TP de Sistemas
Operativos de la UTN FRBA.

## Dependencias

Para poder compilar y ejecutar el proyecto, es necesario tener instalada la
biblioteca [so-commons-library] de la cátedra:

```bash
git clone https://github.com/sisoputnfrba/so-commons-library
cd so-commons-library
make debug
make install
```

## Compilación

Cada módulo del proyecto se compila de forma independiente a través de un
archivo `makefile`. Para compilar un módulo, es necesario ejecutar el comando
`make` desde la carpeta correspondiente.

El ejecutable resultante se guardará en la carpeta `bin` del módulo.

Sumado a esto, es necesario aclarar que arhicvo de configuracion se desea usar

Ejemplo:
```./cpu cpu1.0
./kernel kernel1.0
```

## Importar desde Visual Studio Code

Para importar el workspace, debemos abrir el archivo `tp.code-workspace` desde
la interfaz o ejecutando el siguiente comando desde la carpeta raíz del
repositorio:

```bash
code tp.code-workspace
```


