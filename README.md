# Aprendizaje de Procesos en Sistemas Operativos

Este repositorio contiene ejemplos prácticos para entender el manejo de procesos en sistemas operativos tipo Unix/Linux, implementados en C/C++.

## 📋 Contenido

### 1. Conceptos Básicos de Procesos
- **`procesos.cpp`** - Primer ejemplo de creación de procesos con `fork()`
- **`procesosdos.cpp`** - Cadena lineal de procesos (altura 5)
- **`procesostres.cpp`** - Árbol básico con padre, hijos y nieto
- **`procesoscuatro.cpp`** - Árbol binario completo de dos niveles
- **`procesoscuatro-for.cpp`** - Versión optimizada con bucles

### 2. Sincronización y Coordinación
- **`forkjoin-uno.cpp`** - Tareas paralelas independientes con sincronización
- **`forkjoin-dos.cpp`** - Implementación de grafo de precedencia complejo

## 🚀 Compilación y Ejecución

### Prerrequisitos
En Fedora 42, instalar las herramientas de desarrollo:
```bash
sudo dnf install gcc g++
```

### Compilar cualquier archivo
```bash
g++ archivo.cpp -o ejecutable

g++ forkjoin-uno.cpp -o forkjoin

g++ procesos.cpp -o procesos
```



### Ejecutar
```bash
./ejecutable
```

## 📊 Descripción de Ejemplos

### 1. Proceso Básico (`procesos.cpp`)
**Objetivo:** Entender el comportamiento básico de `fork()`

**Estructura:**
```
Proceso Original
    ↓
   fork()
   ↙    ↘
Padre   Hijo
```

**Conceptos:**
- Valor de retorno de `fork()`: 0 para hijo, PID para padre
- Ejecución simultánea de procesos
- Diferencia entre PID del proceso y valor de `fork()`

---

### 2. Cadena Lineal (`procesosdos.cpp`)
**Objetivo:** Crear una secuencia lineal de procesos

**Estructura:**
```
Original → Hijo1 → Hijo2 → Hijo3 → Hijo4
```

**Características:**
- 4 iteraciones = 5 procesos total
- Cada proceso crea un único hijo y termina (`break`)
- Cadena secuencial, no árbol

---

### 3. Árbol Básico (`procesostres.cpp`)
**Objetivo:** Crear estructura jerárquica simple

**Estructura:**
```
       Padre
      /     \
   Hijo1   Hijo2
    |
  Nieto
```

**Características:**
- Padre crea 2 hijos
- Hijo1 crea un nieto
- Hijo2 no tiene descendientes

---

### 4. Árbol Binario Completo (`procesoscuatro.cpp`)
**Objetivo:** Crear árbol binario de dos niveles

**Estructura:**
```
           Padre
          /     \
      Hijo1     Hijo2
      /   \     /    \
  Nieto   Nieto Nieto Nieto
   1.1     1.2   2.1   2.2
```

**Características:**
- 7 procesos total (1 padre + 2 hijos + 4 nietos)
- Cada hijo crea exactamente 2 nietos
- Versión con bucles disponible en `procesoscuatro-for.cpp`

---

### 5. Tareas Paralelas (`forkjoin-uno.cpp`)
**Objetivo:** Demostrar paralelismo y sincronización

**Estructura:**
```
    Padre
   /  |  \
Hijo1 Hijo2 Hijo3
 (1s)  (2s)  (3s)
   \    |    /
    wait() × 3
```

**Características:**
- 3 hijos ejecutan tareas de diferente duración
- Padre espera a que TODOS terminen antes de continuar
- Uso de `wait(NULL)` para sincronización

**Salida esperada:**
```
Padre (PID: 1234) inicia la creación de procesos
Soy el hijo 1, mi PID es 1235
Soy el hijo 2, mi PID es 1236
Soy el hijo 3, mi PID es 1237
Hijo 1 (PID: 1235) terminó su tarea.    [1 segundo]
Hijo 2 (PID: 1236) terminó su tarea.    [2 segundos]
Hijo 3 (PID: 1237) terminó su tarea.    [3 segundos]
Padre (PID: 1234) ha terminado de esperar a sus hijos.
```

---

### 6. Grafo de Precedencia (`forkjoin-dos.cpp`)
**Objetivo:** Implementar dependencias complejas entre procesos

**Estructura:**
```
      S1
   /  |  \
  S2  S3  S4
   \ /    |
    S5    |
     \    |
      \   /
       S6
```

**Dependencias:**
- **S1** → **S2, S3, S4** (en paralelo)
- **S2, S3** → **S5** (S5 espera a S2 y S3)
- **S4, S5** → **S6** (S6 espera a S4 y S5)

**Sincronización:**
```cpp
waitpid(pid1, NULL, 0);  // Espera S2
waitpid(pid2, NULL, 0);  // Espera S3
// Crea S5

waitpid(pid3, NULL, 0);  // Espera S4
waitpid(pid4, NULL, 0);  // Espera S5
// Crea S6
```

## 🔧 Conceptos Clave Aprendidos

### Funciones Principales
- **`fork()`** - Crear nuevos procesos
- **`getpid()`** - Obtener PID del proceso actual
- **`getppid()`** - Obtener PID del proceso padre
- **`wait(NULL)`** - Esperar a cualquier proceso hijo
- **`waitpid(pid, NULL, 0)`** - Esperar a un proceso específico
- **`sleep(n)`** - Pausar ejecución por n segundos

### Valores de Retorno de `fork()`
- **`< 0`** - Error al crear proceso
- **`== 0`** - Estás en el proceso hijo
- **`> 0`** - Estás en el proceso padre (valor = PID del hijo)

### Patrones de Programación
1. **Creación única:** Un proceso crea un hijo
2. **Cadena lineal:** Cada proceso crea uno y termina
3. **Árbol:** Un proceso crea múltiples hijos
4. **Paralelismo:** Múltiples procesos ejecutan simultáneamente
5. **Sincronización:** Usar `wait()` para coordinar procesos

## 🎯 Casos de Uso

### Cuándo usar cada patrón:

**Cadena Lineal:**
- Pipeline de procesamiento
- Tareas secuenciales que se pasan datos

**Árbol Binario:**
- Divide y vencerás
- Procesamiento jerárquico

**Tareas Paralelas:**
- Procesamiento independiente
- Aprovechar múltiples cores

**Grafo de Precedencia:**
- Flujos de trabajo complejos
- Dependencias específicas entre tareas

## 📚 Recursos Adicionales

### Bibliotecas Utilizadas
```cpp
#include <stdio.h>      // printf, perror
#include <unistd.h>     // fork, getpid, getppid, sleep
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait, waitpid
```

### Compilación con Flags Útiles
```bash
# Compilación con información de debug
g++ -g -Wall archivo.cpp -o ejecutable

# Compilación optimizada
g++ -O2 archivo.cpp -o ejecutable
```

### Monitoreo de Procesos
```bash
# Ver procesos en tiempo real
ps aux | grep ejecutable

# Árbol de procesos
pstree -p

# Monitoreo continuo
watch "ps aux | grep ejecutable"
```

## ⚠️ Notas Importantes

1. **Procesos Zombie:** Siempre usar `wait()` para limpiar procesos hijo
2. **Orden de ejecución:** Los procesos pueden ejecutar en cualquier orden
3. **Recursos compartidos:** Los procesos hijo heredan descriptores de archivo
4. **Memoria:** Cada proceso tiene su propio espacio de memoria
5. **Variables:** Los cambios en variables del hijo no afectan al padre

## 🔄 Próximos Pasos

Para profundizar en el tema:
1. Implementar comunicación entre procesos (pipes, shared memory)
2. Estudiar señales (signals) para comunicación asíncrona
3. Explorar threads vs procesos
4. Practicar con `exec()` family para cargar programas diferentes
5. Implementar semáforos y mutex para sincronización avanzada

---

**¡Feliz aprendizaje de Sistemas Operativos! 🚀**