# PROJECT 2: USER PROGRAMS. PROCESS MANAGEMENT SYSTEM CALLS

## EQUIPO
> Pon aquí los nombres y correos electrónicos de los integrantes de tu equipo.

<ADLG> <ccadlg@ciencias.unam.mx>

##  PRELIMINARES
> Si tienes algún comentario preliminar a tu entrega, notas para los ayudantes o extra créditos, por favor déjalos aquí.

> Por favor cita cualquier recurso offline u online que hayas consultado mientras preparabas tu entrega, otros que no sean la documentación de Pintos, las notas del curso, o el equipo de enseñanza

## SYSTEM CALLS

### ESTRUCTURAS DE DATOS

> B1: A cada declaración nueva o modificación de un `struct` o `struct member`, variable global o estática, `typedef` o `enum`. Agrega comentarios en el código en el que describas su propósito en 25 palabras o menos.

 R: Va directo en el código.

### ALGORITMOS

> B3: (Punto Extra) Describe el código encargado de leer y escribir datos de usuario desde el kernel.

R: Lo que se hace en esa parte es validar los apuntadores junto con sus accesos, de ahi se manejan los casos donde el acceso sea invalido (que se apunte hacia una direccion incorrecta o que no tenga sentido, sea un apuntador nulo, etc.). Una vez validados esos puntos se hace una llamada de lectura o escritura para acceder a la memoria y se checa que no haya excepciones o errores.

> B4: (Punto Extra) Supón que una __system call__ causa que una página completa (4096 bytes) de datos se copien del espacio de usuario al __kernel__. ¿Cuál es el número mínimo y máximo de inspecciones de la __page table__ (e.g llamadas a `pagedir_get_page()`) que pudieran resultar? ¿Qué ocurre cuando una llamada a sistema copia solo 2 bytes de datos? ¿Existe margen de mejora para estos números, y por cuánto? 

R: El numero minimo seria 1, que seria una pagina donde se guardan los datos a inspeccionar y el numero maximo el mencionado de una pagina completa, es decir, 4096.
Cuando solo se copian solo 2 bytes, el numero minimo seria 1 y el numero maximo seria 2.
No existe tal margen porque se pueden hacer busquedas en mas de una pagina.

> B5: Describe brevemente tu implementación de la __system call__ "wait" y cómo interactúa con la terminación del proceso.

R: En process_wait() (como solo interactua con los procesos hijos) primero se ve que la lista de hijos del proceso no sea vacia, de ahi se recorre la lista de procecsos del padre para tomar un proceso hijo y comparar el valor tid del hijo tomado con el recibido, si no se encuentra regresa -1 de lo contrario se regresa el exit_status del proceso hijo, claramente señalando o informando al padre que el hijo termino su ejecucion.

> B6: (Punto Extra) Cualquier acceso a una dirección de memoria especificada por el usuario en un proceso del usuario podría fallar si la dirección es incorrecta, en cuyo caso se debería terminar el proceso. Estos accesos podrían ocurrir en cualquier momento durante una __system call__, por ejemplo la __system call__ `write` requiere leer el id del stack del usuario, seguido de cada uno de los tres argumentos de la llamada y de una cantidad arbitraria de memoria del usuario, y cada uno de estos accesos podría fallar. Lo anterior supone un desafío de diseño y de manejo de errores. ¿Cómo se evita obscurecer la función principal del código, sin dejar de manejar los errores de acceso a memoria? Además, si un error es detectado, ¿Cómo se se garantiza que se liberen todos los recursos que se habían asignado temporalmente en la __system call__ (locks, buffers, etc.)? Describe las estrategias que se utilizaron para resolver estos problemas. Da un ejemplo.

R: Los casos señalados se evitan haciendo que cada apuntador apunte a una direcion de memoria valida, ademas de liberar la memoria tomada. Se hace con las funciones palloc_free_page(), palloc_get_page() y en una linea de thread_create() para la memoria que ocupara el proceso padre.

Un ejemplo se puede ver en process_execute() donde se asigna memoria para fn_copy, si hay algun error, es decir, si (tid == TID_ERROR) entonces se regresa -1 de lo contrario se sigue con la ejecucion normal de la funcion.

### SYNCHRONIZATION

> B7: La __system call__ `exec` regresa `-1` si falla la carga del ejecutable, por lo cual no puede regresar antes de que se complete la carga en el proceso hijo. ¿Cómo se garantiza que `exec` no regrese antes de que finalice la carga del ejecutable? ¿Cómo se pasa el resultado de la carga (éxito/fallo) hacia el __thread__ que llama a `exec`? 

R: Se garantiza con el if (if(!t->thready)) donde se verifica que el valor booleano thready sea verdadero para continuar con la ejecucion de process_execute(), de lo contrario se regresa un -1.
El resultado de la carga se pasa a traves de semaforos, inicializando y dando el down de dicho semaforo para indicar que se cargo correctamente el proceso hijo.

> B8: Considera un proceso padre P con un proceso hijo C. ¿Cómo se evitan __race conditions__ cuando P llama `wait(C)` antes de que C finalice? ¿Cómo se evitan __race conditions__ cuando P llama `wait(C)` luego de que C finalice? ¿Cómo se garantiza que todos los recursos se liberen en cada caso? ¿Qué ocurre cuando C finaliza su ejecución sin llamar a `wait`, antes de que C finalice? ¿Luego de que C finalice? ¿Existe algún caso especial que se deba tener en cuenta?  

R: Como se menciono anteriormente se evitan recorriendo y buscando el tid del hijo, si se encuentra se hace un down del padre (se despierta, se indica que ya esta listo para seguir), se elimina al hijo de la lista de hijos y se regresa el exit_status. Ahora para luego de que C finalice lo que se hace es no bloquear al proceso padre pero si regresar un valor de salida.
Cuando no se llama a wait se liberan los recursos (los que normalmente son usados en esas llamadas).
Y a sea que P sale antes que C o despues simplemente el hijo no se "enviara" a nadie.

### RATIONALE

> B9: (Punto Extra) ¿Por qué elegiste implementar el acceso a la memoria del usuario desde el __kernel__ de la forma en que lo hiciste?

R: Por la informacion que venia en el pdf en la seccion de 2.1. Procesos de usuario.

> B11: El mapeo de `tid_t` a `pid_t` utilizado por defecto es la función identidad. Si se utilizó un mapeo diferente, ¿Cuáles son las ventajas del mapeo utilizado?

R: Solo se trabajo con tid's, no hubo mapeos a pid_t.