# 🎨 Coloreto (Versión reducida en C++)

Este proyecto es una **versión simplificada del juego de mesa Coloreto**, desarrollada en **C++ modulado** con manejo de **memoria dinámica** y opción de **guardar y cargar partidas**.

---

## 🧠 Descripción general

El objetivo del juego es **acumular la mejor combinación de colores** en tus cartas antes de que termine la partida.
Durante el juego, los jugadores colocan o toman pilas de cartas, buscando equilibrar sus colores para sumar la mayor cantidad de puntos.

---

## 🧩 Características del proyecto

* Lenguaje: **C++17**
* Estructura modular con los siguientes archivos:

  * `main.cpp` → punto de entrada del programa
  * `game.cpp / game.h` → control principal de turnos y lógica
  * `player.cpp / player.h` → manejo de jugadores y sus manos
  * `deck.cpp / deck.h` → generación y control del mazo
  * `save.cpp / save.h` → sistema de guardado/carga de partida
  * `card.h` → definición de la estructura de cartas
* Uso de **memoria dinámica**
* **Validación de entradas**: evita datos inválidos
* **Advertencias sin romper el flujo** (pila llena, dato inválido, etc.)
* Soporta **3 a 5 jugadores**
* Permite **guardar partida y continuar después**
* Implementa las **reglas básicas de Coloreto**, sin comodines

---

## 🎮 Manual de juego

### 🎴 Preparación

Según el número de jugadores:

| Jugadores | Colores usados | Cartas totales |
| --------- | -------------- | -------------- |
| 3         | 5 colores      | 56 cartas      |
| 4         | 6 colores      | 65 cartas      |
| 5         | 7 colores      | 74 cartas      |

Cada color tiene 9 cartas. Además hay:

* 10 cartas **+2**
* 1 carta de **última ronda**, colocada a 15 cartas del final del mazo

---

### 🕹️ Reglas principales

* En el centro hay **pilas de cartas** (máximo 3 por pila).

* En su turno, un jugador puede:

  1. **Robar una carta** y colocarla en una pila que **no esté llena**, o
  2. **Tomar una pila completa**, quedando fuera de la ronda hasta que comience la siguiente.

* **Una pila robada no puede recibir más cartas** hasta la siguiente ronda.

* Si todas las pilas están llenas, los jugadores **deben tomar pilas**.

* Cuando se roba la carta de **última ronda**, la partida termina al finalizar esa ronda.

---

### ⚠️ Validaciones y advertencias

* Si un jugador intenta colocar una carta en una pila llena → se muestra un mensaje de advertencia, **sin perder turno**.
* Si el dato ingresado no es válido → muestra `(dato inválido)` y permite reintentar.
* El flujo del juego **continúa normalmente** tras cada advertencia.

---

### 🏁 Final del juego

Después de que se robe la carta de **última ronda**, se completa la ronda actual.
Luego se cuentan los puntos según los colores que cada jugador mantuvo.
El programa muestra el **ganador con mayor puntaje**.

---

## 💾 Guardado y carga

Durante el juego puedes:

* **Guardar partida** → se almacena en un archivo binario.
* **Cargar partida** → permite continuar más tarde.

---

## ⚙️ Compilación

Desde la carpeta raíz del proyecto:

```bash
g++ -std=c++17 src/*.cpp -o coloreto
```

En Windows:

```bash
g++ -std=c++17 src/*.cpp -o coloreto.exe
coloreto.exe
```

---

## 🧱 Diagrama UML (Resumen)
<img width="1024" height="1536" alt="image" src="https://github.com/user-attachments/assets/89fef297-1f95-42f0-91be-1404286764a0" />

```

---

## 🧑‍💻 Autor

Proyecto académico desarrollado por **Karen Johana Ortiz Arias**
**Lenguaje:** C++
**Versión:** v1.0 (2025)
