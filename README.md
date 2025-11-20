# get_next_line (GNL)

Función para leer línea por línea de un file descriptor.

## Descripción

Get_next_line es un proyecto de 42 que consiste en crear una función que lee y retorna una línea de un file descriptor. Este proyecto enseña sobre gestión de memoria estática, manejo de buffers y lectura de archivos.

## Prototipo

```c
char *get_next_line(int fd);
```

## Parámetros

- `fd`: File descriptor desde el cual leer

## Retorno

- La línea leída (incluyendo el `\n` final si existe)
- `NULL` si no hay más líneas que leer o si ocurre un error

## Compilación

La función está diseñada para ser compilada con un tamaño de buffer definido:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Puedes ajustar `BUFFER_SIZE` según tus necesidades.

## Uso

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("archivo.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Archivos

### Parte Obligatoria
- `get_next_line.c`: Función principal
- `get_next_line.h`: Header con definiciones
- `get_next_line_utils.c`: Funciones auxiliares

### Parte Bonus
- `get_next_line_bonus.c`: Versión que soporta múltiples file descriptors
- `get_next_line_bonus.h`: Header de la versión bonus
- `get_next_line_utils_bonus.c`: Utilidades para la versión bonus

## Funciones Auxiliares

- `ft_strlen`: Calcula la longitud de una cadena
- `ft_strchr`: Busca un carácter en una cadena
- `ft_strjoin`: Une dos cadenas
- `ft_substr`: Extrae una subcadena
- `ft_strdup`: Duplica una cadena

## Características

- ✅ Lee de cualquier file descriptor (archivos, stdin, etc.)
- ✅ Versión bonus soporta múltiples file descriptors simultáneos
- ✅ Gestión correcta de memoria (sin leaks)
- ✅ Buffer size configurable en tiempo de compilación
- ✅ Maneja archivos grandes eficientemente

## Notas

- El `BUFFER_SIZE` se puede definir en tiempo de compilación
- Si no se define, se usa un valor por defecto de 42
- La función gestiona memoria estática para mantener el estado entre llamadas
- Recuerda liberar la memoria retornada por `get_next_line`

## Autor
jmiguele - 42 Madrid
