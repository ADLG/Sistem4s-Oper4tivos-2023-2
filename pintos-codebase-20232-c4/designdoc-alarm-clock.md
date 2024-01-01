# PROJECT 1: THREADS. DESIGN DOCUMENT

## EQUIPO
> Pon aquí los nombres y correos electrónicos de los integrantes de tu equipo.

<ADLG> <ccadlg@ciencias.unam.mx>

##  PRELIMINARES
> Si tienes algún comentario preliminar a tu entrega, notas para los ayudantes
> o extra créditos, por favor déjalos aquí. 

> Por favor cita cualquier recurso offline u online que hayas consultado
> mientras preparabas tu entrega, otros que no sean la documentación de Pintos,
> las notas del curso, o el equipo de enseñanza

## ALARM CLOCK

### ESTRUCTURAS DE DATOS

> A1: A cada declaración nueva o modificación de un `struct` o `struct member`, 
> variable global o estática, `typedef` o enumeración. Agrega comentarios en el
> código en el que describas su propósito en 25 palabras o menos.

R: Deje comentarios en las funciones thread_sleep(), compara_thticks(), thread_wake() y en 
el struct de la lista block_list en el thread.c.

### ALGORITMOS

> A2: Describe brevemente qué sucede en una llamada a `timer_sleep ()`
> incluyendo los efectos del __interrupt_handler__ del __timer__.

R: La funcion timer_sleep () le dice a un hilo cuanto tiempo (cuantos ticks) se debe dormir. Primero verifica
si el hilo ha llegado un cierto número de ticks y dependiendo de eso se llama la función thread_sleep(), que 
guarda el tiempo en donde tiene que despertar el hilo, apaga las interrupciones, agrega a dicho hilo
en la block_list para posteriormente bloquear al hilo. En timer_interrupt() se verifica en la block_list
que hilos ya deben de despertar, si se despierta un hilo se vuelven a activar las interrupciones para repetir 
el proceso.

> A3: Qué pasos son tomados para minimizar la cantidad de tiempo gastada
> por el __interrupt_handler__ del __timer__?

R: El paso donde se calcula el tiempo en el que un hilo debe de despertar y donde se agregan los hilos a
la block_list para que un hilo se bloquee. Asi ya no ocurre lo que pasaba con thread_yield()

### SINCRONIZACIÓN

> A4: Cómo evitas __race conditions__ cuando multiples __threads__ llaman
> `timer_sleep ()` simultaneamente?

R: Se evitan apagando las interrupciones, eso quita concurrencia de las llamadas de los hilos.

> A5: Cómo evitas __race conditions__ cuando ocurre una interrupción del __timer__
> durante una llamada a `timer_sleep ()`?

R: De nuevo apagando las interrupciones para que así los hilos o incluso uno mismo, no puedan realizar interrupciones.

### ARGUMENTACIÓN

> A6: Por qué elegiste este diseño? En qué formas es superior a otros diseños 
> que hayas considerado?

R: Al menos es mejor al thread_yield() ya que no está preguntando constantemente si ya paso el tiempo
de los ticks gastando recursos, en esta implementación se agregan y se bloquean directamente a los hilos y ya 
el timer_interrupt() se encarga de despertar a los hilos que llegaron a los ticks requeridos.