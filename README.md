# Listado de Directorios en C

Este sencillo programa en C te permite listar el contenido de un directorio, incluyendo subdirectorios y categorizando archivos según sus extensiones.

## Características

- Lista directorios y archivos en una estructura de árbol.
- Categoriza archivos según extensiones predefinidas.

## Inicio Rápido

### Requisitos

- Compilador de C (por ejemplo, GCC para Linux, MinGW para Windows)

### Compilación

Compila el programa con el siguiente comando:

```bash
gcc directory_listing.c -o directory_listing
```
### Uso
Ejecuta el ejecutable compilado e ingresa la ruta del directorio que deseas listar cuando se te solicite.

### Extensiones de Archivos
El programa categoriza los archivos según las siguientes extensiones:
```
.txt: TEXT
.exe: EXE
.pdf: PDF
.dll: DLL
.c: C
.py: PY
.h: H
.rar: RAR
```
Siéntete libre de personalizar el arreglo extensiones en el código para agregar o eliminar extensiones según sea necesario.

### Soporte de Plataforma
El programa es compatible tanto con Windows como con sistemas tipo Unix.

En Windows, utiliza la biblioteca windows.h para el manejo de directorios.

En sistemas tipo Unix, utiliza la biblioteca dirent.h.
### Contribuciones
¡Las contribuciones son bienvenidas! Si encuentras algún problema o tienes sugerencias de mejora, por favor, abre un problema o crea una solicitud de extracción.
