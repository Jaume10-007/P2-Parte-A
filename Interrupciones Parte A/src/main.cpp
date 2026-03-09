#include <Arduino.h>

struct Button {
  const uint8_t PIN;          // Pin donde está conectado el botón
  uint32_t numberKeyPresses;  // Número de veces que se ha pulsado
  bool pressed;               // Indica si se ha detectado una pulsación
};

Button button1 = {18, 0, false};   // Botón en GPIO 18

void IRAM_ATTR isr() {
  button1.numberKeyPresses += 1;   // Suma una pulsación
  button1.pressed = true;          // Marca que se ha pulsado
}

void setup() {
  Serial.begin(115200);                  // Inicia monitor serie
  pinMode(button1.PIN, INPUT_PULLUP);    // Pin como entrada con resistencia pull-up interna
  attachInterrupt(button1.PIN, isr, FALLING);  // Interrupción al pasar de HIGH a LOW
}

void loop() {
  if (button1.pressed) {
    Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
    button1.pressed = false;
  }

  static uint32_t lastMillis = 0;

  if (millis() - lastMillis > 60000) {   // Después de 1 minuto
    lastMillis = millis();
    detachInterrupt(button1.PIN);        // Desactiva la interrupción
    Serial.println("Interrupt Detached!");
  }
}