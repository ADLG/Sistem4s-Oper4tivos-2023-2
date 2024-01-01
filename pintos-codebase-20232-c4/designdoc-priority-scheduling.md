# PROJECT 1: THREADS - PRIORITY SCHEDULER. DESIGN DOCUMENT

## EQUIPO
 > Pon aquí los nombres y correos electrónicos de los integrantes de tu equipo.

<ADLG> <ccadlg@ciencias.unam.mx>

 ##  PRELIMINARES
 > Si tienes algún comentario preliminar a tu entrega, notas para los ayudantes
 > o extra créditos, por favor déjalos aquí.

 > Por favor cita cualquier recurso offline u online que hayas consultado
 > mientras preparabas tu entrega, otros que no sean la documentación de Pintos,
 > las notas del curso, o el equipo de enseñanza

## PRIORITY SCHEDULING

### ESTRUCTURAS DE DATOS

> B1: A cada declaración nueva o modificación de un `struct` o `struct member`,
 > variable global o estática, `typedef` o `enum`. Agrega comentarios en el
 > código en el que describas su propósito en 25 palabras o menos.

 R: Agregue comentarios en thread_unblock() y thread_compare().

### ALGORITMOS

> B3: (Punto Extra) Cómo aseguras que el _thread_ de más alta
> prioridad que está esperando en un _semaphore_, _lock_ o 
> _condition_ despierta primero?

 R: Mediante el uso de la función list_insert_ordered() para ordenar los hilos en las 
 funciones thread_unblock() y thread_yield() ademas de un if en thread_unblock() para 
 llamar al scheduler dependiendo si un hilo esta o no en una interrupcion.

> B4: Qué tan eficiente es tu estrategia para insertar y borrar
> elementos de la `ready_list`? Puedes imaginar una estructura de
> datos para representar la `ready_list` en la que las inserciones y 
> operaciones de borrado tomen __O(1)__?
 
 R: Creo que las listas que se manejan en las funciones son listas ligadas, por lo que para
 insertar y eliminar elementos toman O(1), por otro lado en arreglos tomarian O(n).

### SINCRONIZACIÓN

> B6: Describe una posible _race condition_ en la función
> `thread_set_priority ()` y explica cómo tu implementación la evita.
> Puedes utilizar un _lock_ para evitarla?

 R: La posible race condition seria que el hilo actual tuviera menor prioridad que 
 el que esta en la cabeza de la ready_list o que tuvieran la misma prioridad, pero esto
 se evita en el if que esta en la función thread_unblock().

### RATIONALE

> B7: Por qué elegiste este diseño? En qué maneras es superior a otros
> diseños que hayas considerado?

 R: El diseño de la solucion fue gracias a los tips que se dieron de, en vez de ordenar en cada
 función la ready_list, simeplemente ordenarla en las dos funciones que mencione anteriormente 
 (thread_unblock() y thread_yield()), para que asi sea mas facil el manejo de los hilos.