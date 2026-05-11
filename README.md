# 🍝 Philosophers - Dining with threads

¡Hola! Como estudiante de 42, este es mi proyecto **Philosophers** (y en particular, la versión obligatoria: `philo`). Este proyecto aborda el clásico problema de la sincronización en ciencias de la computación ("The Dining Philosophers problem"), introducido por Edsger Dijkstra.

## 🎯 Objetivos y Fundamentos

El objetivo principal de Philosophers es aprender sobre hilos (threads) y evitar el bloqueo mutuo (*deadlocks*) o la inanición (*starvation*). Los fundamentos de este proyecto radician en:

1.  **Concurrencia vs Paralelismo:** Entender cómo se comportan múltiples hilos (`pthread_create()`, `pthread_join()`) ejecutándose simultáneamente dentro del mismo espacio de memoria de un único proceso.
2.  **Sincronización:** Uso estricto de candados o *mutexes* (`pthread_mutex_t`) para proteger recursos compartidos (como la salida por pantalla con `printf` o las variables de control).
3.  **Filósofos y Tenedores:** Modelar la lógica de que cada filósofo necesita 2 tenedores (los mutexes `l_f` y `r_f`) para comer, pero los tenedores son recursos finitos y compartidos.
4.  **Monitoreo y Ciclos de Vida:** Asegurar que ningún filósofo muera de hambre (`get_end()`, `death()`), monitoreando el tiempo constantemente mediante llamadas rápidas a `gettimeofday()`.

## 🏗️ Construcción y Arquitectura

El núcleo del programa se sostiene sobre hilos de POSIX y memoria compartida. La estructura consiste en las estructuras `t_main` (para los datos globales y compartidos) y `t_philo` (datos individuales para cada hilo/filósofo).

*   **`init.c`:** Parsea los argumentos de entrada, inicializa arrays compartidos (para tenedores/mutexes), configura la estructura global `t_main` local alojando espacio para cada filósofo (`t_philo`). Llama a `pthread_create()`.
*   **`routine.c` (`philo_routine`):** Aquí vive el bucle del filósofo: intenta tomar o "lockear" el tenedor izquierdo y derecho (`pthread_mutex_lock`), come, actualiza su tiempo de la última comida, "unlockea", duerme (`ft_usleep()`) y luego piensa.
*   **`death.c`:** Aquí se aloja el hilo espía auxiliar o `monitor_thread`. En lugar de sobrecargar cada filósofo con un control rígido, un hilo de control chequea continuamente si algún filósofo ha superado `time_to_die` (leído por `get_time_ms()`) u optimizando si todos pasaron por su límite de comidas `mx_m_reached()`.
*   **Gestores compartidos:** Mutexes adicionales como `print_l` para imprimir en consola, y `end_l` para proteger el flag que detiene con gracia a todos los hilos (`end`).

## 🧗 Dificultades del Proyecto

Philosophers parece pequeño porque no admite el uso de norminette en variables infinitas o complejas (lo cual obliga a hacer estructuras pequeñas como `s_philo { ... id, m_e, t2d ... }`). Sus verdaderas pesadillas son:

1.  **Data Races:** El mayor dolor de cabeza es asegurar el acceso a variables compartidas. Leer `t_main->end` sin su respectivo `pthread_mutex_lock(&end_l)` causa *data races*, localizables gracias a las banderas `-fsanitize=thread`.
2.  **Pausas (Sleepers) ineficientes:** El `usleep()` a menudo no respeta los tiempos precisos requeridos. Construir una función `ft_usleep()` propia que constantemente verifique si alguien ha muerto mientras descansa (gracias a `gettimeofday`) era necesario para el correcto flujo.
3.  **Deadlocks:** En tableros donde los filósofos toman simultáneamente todo su respectivo tenedor "izquierdo" al mismo tiempo, el programa cuelga por siempre. Es crítico el tratamiento de desfases entre hilos (como hacer a los pares dormir antes de agarrar).
4.  **Gestión de Memoria y Mutexes:** Asegurarse de realizar `pthread_mutex_destroy/free` correctamente sobre un gran array (ya sea por fin natural o por fallos intencionados al inicializar el `pthread_create`).

## 🧠 Conocimientos adquiridos y reforzados

**Nuevos Conocimientos:**
*   Diferencia radical en manipulación entre `fork()`/procesos (Minishell) y el uso de `pthread()`/hilos dentro del mismo heap y pila.
*   Conceptos de Exclusión Mutua (`mutex`).
*   Dominio del uso de `gettimeofday()` para cronometraje en microsegundos y conversión a milisegundos.
*   Uso extremo de `-fsanitize=thread` (Helgrind) para corregir acceso simultáneo inestable en hilos.

**Conocimientos Reforzados:**
*   Mantenimiento óptimo de recursos modulares (`ft_clean()`).
*   Arquitectura basada en paso de punteros globales entre rutinas independientes.
