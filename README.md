# Práctica 2 – Interrupciones (Parte A)

## Descripción

Este proyecto corresponde a la **Práctica 2 de Procesadores Digitales**, donde se estudia el funcionamiento de las **interrupciones en el ESP32** utilizando el framework Arduino en PlatformIO.

En esta primera parte se implementa una **interrupción por GPIO** mediante un botón conectado al pin **GPIO 18**. Cada vez que el botón se pulsa, se genera una interrupción que ejecuta una **rutina de servicio de interrupción (ISR)**. Esta rutina incrementa un contador que registra el número total de pulsaciones.

El programa muestra el número de veces que se ha pulsado el botón a través del **monitor serie**. Además, después de **60 segundos**, la interrupción se desactiva automáticamente utilizando `detachInterrupt()`.

## Funcionamiento

* El botón está configurado con **INPUT_PULLUP**.
* La interrupción se dispara con el modo **FALLING** (cambio de HIGH a LOW).
* La ISR incrementa el contador de pulsaciones.
* El programa imprime el número de pulsaciones en el monitor serie.
* Tras 60 segundos, se desactiva la interrupción.

## Hardware utilizado

* ESP32
* Botón
* Cables de conexión

## Conexión

Botón conectado entre:

* **GPIO 18**
* **GND**

## Entorno de desarrollo

* Visual Studio Code
* PlatformIO
* Framework Arduino
