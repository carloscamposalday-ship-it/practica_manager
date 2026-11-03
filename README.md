# Manager K-pop

## Equipo
- Carlos Campos Alday
- Enriquez Ruiz Itzlly Manuel
- Cruz Ramirez Daniel

**Materia:** Introducción al Software  **Profesor:** ______
**Scrum Master:** Sprint 1: ______ · Sprint 2: ______ · Sprint 3: ______ · Sprint 4: ______

Práctica en C sobre **apuntadores a struct**, **paso por apuntador**, **aritmética de apuntadores** y uso correcto de `const`. El programa simula a un manager que administra idols (`Idol`), canciones (`Cancion`) y un grupo (`Grupo`).

- **Archivo principal:** `manager.c`
- **Metodología:** Scrum (4 sprints) + estimación con PSP
- **Lenguaje:** C (estándar de `gcc`)

## Compilar y ejecutar

```bash
gcc manager.c -o manager
./manager
```

La compilación final no genera advertencias.

## Estructuras

| Struct | Campos | Notas |
| --- | --- | --- |
| `Cancion` | `nombre[30]`, `bonus`, `vigencia` | `vigencia` = presentaciones restantes (0 = vencida) |
| `Idol` | `nombre[30]`, `popularidad`, `energia`, `energia_max`, `fans`, `Cancion *cancion` | `cancion == NULL` significa "sin canción" |
| `Grupo` | `nombre[30]`, `Idol miembros[MAX_MIEMBROS]`, `n`, `Idol *lider` | `lider` apunta dentro de `miembros` |

Constantes: `MAX_MIEMBROS = 4`, `ENERGIA_CONCIERTO = 10`, `FANS_POR_POPULARIDAD = 10`.

## Avance por sprint

| Sprint | Tema | Etapas | Historias | Puntos | Estado |
| --- | --- | --- | --- | --- | --- |
| 1 | Cimientos: apuntador a struct y paso por apuntador | 0, 1, 2 | HU-00 a HU-08 | 17 | Completado |
| 2 | Seguridad con NULL y primer enlace entre structs | 3 y parte de 4 | HU-09 a HU-14 | 16 | Completado |
| 3 | Relación Idol–Cancion–Grupo y recorrido con apuntadores | parte de 4 y 5 | HU-15 a HU-20 | 18 | Completado (ver nota sobre HU-17) |
| 4 | Concierto, presentación final y defensa del diseño | final de 5 y reto final | HU-21 a HU-25 | 18 | Completado |

### Sprint 1: Cimientos
- `Idol` definida con `typedef struct`; `jennie` creada en `main`.
- Lectura de `fans` con `.`, `(*p).` y `->`, y comparación de direcciones con `%p` (HU-02).
- `mostrar(const Idol *)`, `limitar`, `ensayar`, `descansar`, `esta_activa` (HU-03 a HU-07).
- `ensayar_por_valor` frente a `ensayar` para demostrar qué se copia en cada caso (HU-08).
- Pruebas: 20 ensayos y 20 descansos seguidos sin salir del rango `0..energia_max`.

### Sprint 2: NULL e intercambio de apuntadores
- `colaboracion(Idol *a, Idol *b)` rechaza `NULL` y `a == b` antes de usar `->` (HU-09).
- Dinámica por turnos con `turno` y `otra`, intercambiando **apuntadores** con variable temporal (HU-10, HU-11).
- `Cancion`, campo `Cancion *cancion` en `Idol` y `asignar_cancion`; una misma canción se comparte entre dos idols y se quita con `NULL` (HU-12 a HU-14).

### Sprint 3: Idol – Cancion – Grupo
- `popularidad_total` suma el bono solo si hay canción y `vigencia > 0` (HU-15).
- `Grupo`, `inicializar_grupo`, `agregar_miembro` y `cambiar_lider`, que compara **direcciones** y rechaza NULL, idols fuera del grupo y lugares sin integrante (HU-16, HU-17).
- `mostrar_grupo`, `contar_activas` e `idol_mas_cansada` recorren el arreglo con aritmética de apuntadores; `mostrar_grupo` usa `p++` y `p < g->miembros + g->n`, sin `[]` (HU-18 a HU-20).

### Sprint 4: Concierto y presentación
- `dar_concierto`: solo participan las idols activas (HU-21).
  - Fórmula de fans: `fans += popularidad_total(idol) * 10`.
  - Gasto de energía: 10 por idol activa, con `limitar`.
  - Vigencia: la canción pierde **una presentación por cada integrante activa que la tiene**; nunca baja de 0 y avisa al llegar a 0.
- `demostrar_aritmetica`: imprime con `%p` que `&g->miembros[i]` y `g->miembros + i` son la misma dirección, y que sumar 1 avanza `sizeof(Idol)` bytes (HU-22).
- `mostrar_cancion_lider`: verifica grupo, líder y canción antes de cada flecha; probada con 4 escenarios (HU-23).
- `preparar_presentacion`: hace descansar a la más cansada, da el concierto y muestra el resumen (HU-24).
- Tabla de justificación de funciones y compilación limpia (HU-25).

## HU-25: Justificación del diseño de cada función

| Función | Parámetro | Modifica / Lee | Razón |
| --- | --- | --- | --- |
| `mostrar` | `const Idol *` | Lee | Solo imprime; `const` hace que el compilador impida modificar el struct. Un apuntador evita copiar toda la `Idol`. |
| `limitar` | `int` por valor | Calcula | Solo trabaja con números; no hay nada que modificar fuera de la función. |
| `esta_activa_energia` | `int` por valor | Calcula | Recibe un entero simple; no necesita apuntador. |
| `esta_activa` | `const Idol *` | Lee | Solo consulta la energía. |
| `ensayar_por_valor` | `Idol` por valor | Modifica una copia | Función de demostración (HU-08): el original no cambia porque se copia todo el struct. |
| `ensayar` | `Idol *` | Modifica | Cambia popularidad y energía del struct original, por eso no lleva `const`. |
| `descansar` | `Idol *` | Modifica | Cambia la energía del struct original. |
| `colaboracion` | `Idol *`, `Idol *` | Modifica | Modifica a las dos idols; verifica `NULL` y `a == b` antes de usar `->`. |
| `asignar_cancion` | `Idol *`, `Cancion *` | Modifica | Guarda la dirección de la canción en `i->cancion` (permite compartirla y quitarla con `NULL`). |
| `popularidad_total` | `const Idol *` | Lee | Solo calcula; verifica `cancion != NULL` antes de `cancion->vigencia`. |
| `inicializar_grupo` | `Grupo *`, `const char *` | Modifica | Escribe nombre, contador y líder; el nombre recibido solo se lee, por eso es `const char *`. |
| `agregar_miembro` | `Grupo *`, `const Idol *` | Modifica el grupo | Copia la idol al arreglo del grupo; la idol de origen solo se lee. |
| `cambiar_lider` | `Grupo *`, `Idol *` | Modifica | Asigna `lider` solo si la dirección está dentro de `miembros[0..n-1]`; devuelve 1 o 0. |
| `contar_activas` | `const Grupo *` | Lee | Solo recorre y cuenta. |
| `idol_mas_cansada` | `Grupo *` (sin `const`) | Lee, pero devuelve acceso modificable | **Excepción justificada:** devuelve un `Idol *` modificable a un elemento del grupo, así que el parámetro no puede ser `const`. |
| `mostrar_grupo` | `const Grupo *` | Lee | Solo imprime. |
| `dar_concierto` | `Grupo *` | Modifica | Cambia fans, energía y vigencia de las canciones. |
| `demostrar_aritmetica` | `const Grupo *` | Lee | Solo imprime direcciones. |
| `mostrar_cancion_lider` | `const Grupo *` | Lee | Solo imprime; verifica grupo, líder y canción. |
| `preparar_presentacion` | `Grupo *` | Modifica | Hace descansar a una idol y da el concierto. |

No hay variables globales.

## Historial del repositorio

| Fecha | Commit | Contenido |
| --- | --- | --- |
| 5 oct 2026 | commit inicial y `Definicion_de_Estructura` | Estructura base de `Idol` |
| 7 oct 2026 | `Add Idol structure and display function`, `sprim_1` | `Idol` y `mostrar` |
| 10 oct 2026 | `sprim_1_terminado` | Sprint 1 completo |
| 28 oct 2026 | `sprim_4_terminado` | Sprints 2, 3 y 4 |

## Estimación y registro PSP

Documentos en `docs/`: `PSP_1_Plantilla_de_estimación_de_tamaño_y_tiempo.docx`, `PSP_1_Estimacion_Manager_Grupo_Musical.docx`, `PSP_0_Registro_de_tiempos.docx` y `PSP_0_Resumen_del_plan_del_proyecto.docx`.

| Concepto | Plan | Real |
| --- | --- | --- |
| Función más grande (LOC) | 33.83 (`main`) | 160 (`main`) |
| Función más pequeña (LOC) | 4.79 | 4 |
| LOC totales | 216.45 | 345 (según GitHub, sin líneas en blanco) |
| Tiempo total (min) | 546 | 585 (estimado) |
| Defectos inyectados / removidos | n/a | 12 / 12 (estimado) |

Tiempo por fase (min):

| Fase | Plan | Real (estimado) |
| --- | --- | --- |
| Planificación | 40 | 39 |
| Diseño | 80 | 78 |
| Codificación | 260 | 253 |
| Compilación | 40 | 59 |
| Pruebas | 90 | 117 |
| Postmortem | 36 | 39 |
