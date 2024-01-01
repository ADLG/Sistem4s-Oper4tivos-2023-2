# PROJECT 1: THREADS - MLFQ SCHEDULER. DESIGN DOCUMENT

## EQUIPO
 > Pon aquí los nombres y correos electrónicos de los integrantes de tu equipo.
<ADLG> <ccadlg@ciencias.unam.mx>

 ##  PRELIMINARES
 > Si tienes algún comentario preliminar a tu entrega, notas para los ayudantes
 > o extra créditos, por favor déjalos aquí.
 > Por favor cita cualquier recurso offline u online que hayas consultado
 > mientras preparabas tu entrega, otros que no sean la documentación de Pintos,
 > las notas del curso, o el equipo de enseñanza

 R: Como comentarios en esta practica, al parecer solo paso 5/9 de los tests y no se si los pase bien.
 Me costo entender como tenia que implementar los if's en thread_tick(), segun yo realice lo que se 
 vio en la ayudantia de laboratorio pero de seguro se me fueron varias cosas. Ademas no pude logar modificar 
 la variable de recent_cpu, supongo que igual debio haber sido algun tema con los tipos o llamadas para
 actualizar esa parte de los hilos.

## ADVANCED SCHEDULER

### ESTRUCTURAS DE DATOS

> B1: A cada declaración nueva o modificación de un `struct` o `struct member`,
 > variable global o estática, `typedef` o `enum`. Agrega comentarios en el
 > código en el que describas su propósito en 25 palabras o menos.
 
 R: Va directo en el código.

### ALGORITMOS

> C2: Dados los threads A, B y C con el valor nice de 0, 1 y 2 respectivamente.
> Cada uno con un valor recent_cpu de 0. Llena la tabla que se muestra a
> continuación con los valores de recent_cpu, prioridad y el thread que esta
> corriendo para cada tick de la primera columna.

timer  recent_cpu    prioridad  thread
ticks   A   B   C   A   B   C   corriendo
-----  --  --  --  --  --  --   ------
 0     0   0   0   63  61  59   A
 4     4   0   0   62  61  59   A
 8     8   0   0   61  61  59   A
12     12  0   0   60  61  59   B
16     12  4   0   60  60  59   B
20     12  8   0   60  59  59   A
24     16  8   0   59  59  59   A
28     16  8   0   58  59  59   C
32     20  8   4   58  59  58   B
36     20  12  4   58  58  58   B

> C3: ¿Alguna ambigüedad en la especificación del _scheduler_ hace que los valores en la tabla sean inciertos?
> En caso de ser así, ¿Qué regla usaste para resolver dichos
> valores? ¿Esta regla está implementada en tu solución?

R: Podria causar ambigüedad el tiempo que se requiere para los calculos de las variables como load_avg o recent_cpu.
Y lo que resolveria dichos conflictos serian los if's dentro dee if (thread_mlfqs) de la funcion thread_tick().

> C4. En tu implementación, ¿Como afecta el rendimiento del sistema operativo
> el costo que agregan las operaciones del scheduler dentro y fuera del contexto
> de interrupción?

R: Afecta en la parte de las interrupciones pero al cambiar las prioridades de los hilos
Y llamar al scheduler se busca reducir la cantidad de tiempo de las interrupciones.

### ARGUMENTACIÓN

> C5: Brevemente critica tu diseño, añade ventajas y desventajas que
> tiene la solución que elegiste. Si tuvieras más tiempo para trabajar
> en el scheduler, ¿Que cambios harías para refinar y mejorar tu
> diseño?

El cambio importante que haria seria pasar las 4 pruebas que me faltaron o al menos poder modificar 
el valor de recent_cpu para terminar la practica bien.