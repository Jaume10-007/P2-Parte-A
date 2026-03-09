# Práctica 2 – Interrupciones en ESP32 (Parte A)

## Descripción

Este proyecto corresponde a la **Práctica 2 de la asignatura Procesadores Digitales**.
El objetivo de la práctica es comprender el funcionamiento de las **interrupciones hardware en un microcontrolador ESP32** utilizando el framework **Arduino** en **PlatformIO**.

En esta primera parte se implementa una **interrupción generada por un pin GPIO** mediante un botón. Cada vez que se pulsa el botón, se genera una interrupción que ejecuta una **rutina de servicio de interrupción (ISR)** que incrementa un contador. El número de pulsaciones se muestra a través del **monitor serie**.

Además, el programa incluye un mecanismo que **desactiva la interrupción después de 60 segundos** utilizando la función `detachInterrupt()`.

---

# Objetivos de la práctica

Los principales objetivos de esta práctica son:

* Comprender qué es una **interrupción hardware**.
* Aprender a utilizar **attachInterrupt()** en el ESP32.
* Implementar una **ISR (Interrupt Service Routine)**.
* Diferenciar entre **polling e interrupciones**.
* Mostrar información por el **monitor serie**.
* Gestionar eventos externos (pulsación de un botón).

---

# Conceptos teóricos

## Interrupciones

Una **interrupción** es una señal que provoca que el microcontrolador **interrumpa temporalmente la ejecución normal del programa** para atender un evento urgente.

Cuando ocurre una interrupción:

1. El programa que se está ejecutando se pausa.
2. Se ejecuta una función especial llamada **ISR (Interrupt Service Routine)**.
3. Cuando termina la ISR, el programa continúa desde el punto donde se había detenido.

Las interrupciones permiten responder rápidamente a eventos externos sin tener que comprobar continuamente el estado de una entrada.

---

## Polling vs Interrupciones

### Polling

En el polling el programa comprueba continuamente el estado de una entrada:

```cpp
if(digitalRead(buttonPin) == LOW)
```

Problemas del polling:

* Consume tiempo de CPU
* Puede perder eventos rápidos
* Hace el programa menos eficiente

### Interrupciones

Con interrupciones el microcontrolador solo ejecuta código cuando ocurre el evento.

Ventajas:

* Respuesta inmediata
* Mejor eficiencia
* Código más organizado

---

# Funcionamiento del programa

El sistema utiliza un **botón conectado al GPIO 18 del ESP32**.

El pin se configura como:

```
INPUT_PULLUP
```

Esto significa que:

* El pin normalmente está en **HIGH**
* Cuando se pulsa el botón pasa a **LOW**

La interrupción se configura con el modo:

```
FALLING
```

Esto provoca que la interrupción se dispare cuando el pin cambia de **HIGH a LOW**.

Cada vez que ocurre la interrupción:

1. Se ejecuta la función **ISR**.
2. Se incrementa un contador de pulsaciones.
3. El programa muestra el número de pulsaciones por el monitor serie.

Después de **60 segundos**, la interrupción se desactiva automáticamente.

---

# Hardware utilizado

* ESP32
* Pulsador (botón)
* Cables de conexión
* Ordenador con Visual Studio Code

---

# Conexión del circuito

El botón se conecta entre el pin **GPIO 18** y **GND**.

Esquema básico:

```
ESP32
  |
GPIO18 ---- Botón ---- GND
```

Debido al uso de `INPUT_PULLUP` no es necesario utilizar resistencias externas.

---

# Código del programa

```cpp
#include <Arduino.h>

struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button1 = {18, 0, false};

void IRAM_ATTR isr() {
  button1.numberKeyPresses += 1;
  button1.pressed = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr, FALLING);
}

void loop() {

  if (button1.pressed) {
    Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
    button1.pressed = false;
  }

  static uint32_t lastMillis = 0;

  if (millis() - lastMillis > 60000) {
    lastMillis = millis();
    detachInterrupt(button1.PIN);
    Serial.println("Interrupt Detached!");
  }

}
```

---

# Explicación del código

## Estructura Button

Se define una estructura para almacenar la información del botón:

* Pin donde está conectado
* Número de pulsaciones
* Estado de pulsación

---

## ISR (Interrupt Service Routine)

```cpp
void IRAM_ATTR isr()
```

Esta función se ejecuta cada vez que ocurre la interrupción.

Su función es:

* incrementar el contador de pulsaciones
* indicar que se ha detectado una pulsación

El modificador `IRAM_ATTR` coloca la función en la memoria RAM para que se ejecute más rápidamente.

---

## attachInterrupt()

```cpp
attachInterrupt(button1.PIN, isr, FALLING);
```

Parámetros:

* **button1.PIN** → pin que genera la interrupción
* **isr** → función que se ejecuta
* **FALLING** → interrupción cuando el pin pasa de HIGH a LOW

---

## Desactivar la interrupción

Después de 60 segundos se ejecuta:

```cpp
detachInterrupt(button1.PIN);
```

Esto hace que el ESP32 deje de monitorizar el pin.

---

# Ejecución del programa

Al ejecutar el programa y abrir el **monitor serie a 115200 baudios**, se obtiene una salida similar a:

```
Button 1 has been pressed 1 times
Button 1 has been pressed 2 times
Button 1 has been pressed 3 times
```

Después de un minuto aparece:

```
Interrupt Detached!
```

A partir de ese momento las pulsaciones ya no se registran.

---

# Entorno de desarrollo

Este proyecto ha sido desarrollado utilizando:

* **Visual Studio Code**
* **PlatformIO**
* **Framework Arduino**
* **ESP32**

---

# Conclusión

Esta práctica permite entender cómo funcionan las interrupciones en sistemas embebidos.
Las interrupciones permiten que el microcontrolador reaccione inmediatamente a eventos externos, evitando el uso de polling y mejorando la eficiencia del programa.

Además, se ha aprendido a:

* configurar interrupciones en el ESP32
* implementar una ISR
* gestionar eventos mediante hardware
* mostrar resultados a través del monitor serie


## Entorno de desarrollo

* Visual Studio Code
* PlatformIO
* Framework Arduino
