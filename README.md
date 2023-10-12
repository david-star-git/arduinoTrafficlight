
# Introducción

La gestión del tráfico es un aspecto crítico de la planificación urbana, y comprender el funcionamiento de los semáforos es fundamental para crear sistemas de transporte eficientes. Nuestro proyecto escolar en grupo se centra en el diseño y control de un sistema de semáforos simulado utilizando un microcontrolador Arduino. El objetivo de este proyecto es proporcionar una experiencia de aprendizaje práctica en el campo de sistemas embebidos y programación.

# Propósito del Proyecto

Los semáforos son una parte integral de nuestra vida cotidiana, y su funcionamiento eficiente es esencial para la seguridad vial y el flujo del tráfico. Al simular un sistema de semáforos con Arduino, nuestro objetivo es ofrecer a los estudiantes una comprensión práctica de cómo funcionan los semáforos, cómo se pueden controlar y los principios subyacentes de la gestión del tráfico. Nuestro proyecto permite a los estudiantes explorar el mundo de la electrónica y la programación, aplicando sus conocimientos para crear un modelo funcional de un sistema del mundo real.

# Beneficios del Proyecto

Este proyecto ofrece varios beneficios para los estudiantes y educadores:

- **Aprendizaje Práctico:** Los estudiantes adquieren experiencia práctica en la configuración de hardware, programación y control del sistema, lo cual es invaluable para aquellos que persiguen carreras en ingeniería, informática u otros campos relacionados.

- **Modularidad:** El proyecto está diseñado para ser fácilmente ampliable, lo que permite a los estudiantes agregar y controlar conjuntos adicionales de semáforos, reflejando intersecciones de tráfico del mundo real.

- **Temporización y Secuenciación:** Los estudiantes pueden experimentar con diferentes secuencias de tiempo para los semáforos, explorando el impacto en el flujo de tráfico y la eficiencia.

- **Colaboración en Grupo:** Este proyecto fomenta el trabajo en equipo, ya que los estudiantes trabajan juntos para diseñar y construir un sistema de semáforos funcional.

- **Resolución de Problemas:** Los estudiantes pueden diagnosticar y solucionar problemas del sistema, mejorando sus habilidades de resolución de problemas.

- **Aplicación en el Mundo Real:** Comprender cómo funcionan los sistemas de semáforos se puede aplicar directamente a la planificación urbana y la gestión del tráfico, proporcionando conocimientos valiosos sobre ingeniería de tráfico.

Esperamos que este proyecto sirva como una herramienta educativa, inspirando a los estudiantes a explorar el fascinante mundo de la electrónica, la programación y la gestión del tráfico, preparándolos en última instancia para futuros desafíos y oportunidades en los campos de la tecnología e ingeniería.

En la siguiente parte de esta documentación, explicaremos la funcionalidad del código, desglosando cada componente para ayudarte a comprender cómo se diseña y controla este sistema simulado de semáforos. Esto proporcionará una visión detallada del funcionamiento interno del proyecto y cómo puede utilizarse como una herramienta de aprendizaje para estudiantes interesados en tecnología e ingeniería.

## Definición de Variables

### pines

```cpp
int RedPins[] = {5, 8};
int YellowPins[] = {6, 9};
int GreenPins[] = {7, 10};
```
Aquí, definimos arreglos para los pines de luz Roja, Amarilla y Verde. Estos arreglos se utilizan para asociar cada color con los pines específicos a los que están conectados.

### semaforo

```cpp
int numLamps = 2;
```
Esta variable especifica el número total de semaforo. En el ejemplo, tienes dos semaforo, pero este valor se puede ajustar fácilmente para manejar un número diferente de semaforo.

```cpp
int currentLamp = 1;
```
Esta variable realiza un seguimiento de la semaforo actual que se está controlando. Permite que el código recorra las semaforo de manera eficiente.

### Temporizaciones

```cpp
int greenDuration = 5000;  // Duración de la luz verde
int yellowDuration = 2000; // Duración de la luz amarilla
int redDuration = 1000;    // Duración de la luz roja
int blinkDuration = 1000;  // Duración de parpadeo antes de que la luz verde se vuelva amarilla
int blinkTimes = 3;        // Número de veces que parpadea la luz verde antes de volverse amarilla
```
Estas variables definen las duraciones y temporizaciones para la secuencia del semáforo, lo que facilita ajustar el tiempo según sea necesario sin cambiar múltiples instancias en el código.

## Inicialización de Pines

```cpp
void setup() {
  for (int i = 0; i < numLamps; i++) {
    pinMode(RedPins[i], OUTPUT);
    pinMode(YellowPins[i], OUTPUT);
    pinMode(GreenPins[i], OUTPUT);
  }
}
```
La función `setup` inicializa los pines para todas las semaforo. Al usar un bucle y la variable `numLamps`, es fácil escalar el código para un número diferente de semaforo. Esto mantiene el código mantenible y eficiente.

## Definición de Funciones

### controlLamp

```cpp
void controlLamp(int lampNum, int color, int state) {
  int lampIndex = lampNum - 1; // Los números de semaforos comienzan en 1

  if (lampIndex >= 0 && lampIndex < numLamps) {
    int pin;

    switch (color) {
      case 0:  // Rojo
        pin = RedPins[lampIndex];
        break;
      case 1:  // Amarillo
        pin = YellowPins[lampIndex];
        break;
      case 2:  // Verde
        pin = GreenPins[lampIndex];
        break;
      default:
        return;  // Color inválido
    }

    if (state == 0) {
      digitalWrite(pin, LOW);  // Apagar
    } else if (state == 1) {
      digitalWrite(pin, HIGH);  // Encender
    }
  }
}
```
La función `controlLamp` te permite controlar las luces de una semaforo específica especificando su número, el color y el estado (encendido o apagado). Esta función encapsula la lógica para establecer el pin correspondiente según los parámetros proporcionados, lo que hace que el código sea más modular y legible.

### turnOnAllRedLights

```cpp
void turnOnAllRedLights() {
  for (int lampNum = 1; lampNum <= numLamps; lampNum++) {
    controlLamp(lampNum, 0, 1);  // Encender la luz roja para todos semaforos
  }
}
```
La función `turnOnAllRedLights` está diseñada para encender todas las luces rojas de todas las semaforo a la vez. Esta función proporciona una forma conveniente de manejar todas las luces rojas juntas.

## Función del Bucle Principal

```cpp
void loop() {
  // Todas las luces rojas se encienden
  turnOnAllRedLights();
  delay(redDuration);

  // Rojo -> Amarillo
  controlLamp(currentLamp, 0, 0);
  controlLamp(currentLamp, 1, 1);
  delay(yellowDuration);

  // Amarillo -> Verde
  controlLamp(currentLamp, 1, 0);
  controlLamp(currentLamp, 2, 1);
  delay(greenDuration);

  // Parpadeo Verde
  for (int i = 0; i < blinkTimes + 1; i++) {
    controlLamp(currentLamp, 2, 1);
    delay(blinkDuration);
    controlLamp(currentLamp, 2, 0);
    delay(blinkDuration);
  }

  // Verde -> Amarillo
  controlLamp(currentLamp, 2, 0);
  controlLamp(currentLamp, 1, 1);
  delay(yellowDuration);

  // Amarillo apagado
  controlLamp(currentLamp, 1, 0);

  // Siguiente semaforo
  currentLamp = (currentLamp % numLamps) + 1;
}
```
En la función `loop`, el código controla la secuencia del semáforo. Maneja secuencialmente cada semaforo, enciende y apaga las luces y lleva un seguimiento del tiempo y se mueve eficientemente a la siguiente semaforo. Este enfoque minimiza la redundancia y es eficiente porque se escala fácilmente a diferentes números de semaforo. El uso de funciones como `controlLamp` y `turnOnAllRedLights` también mantiene el código organizado y mantenible, lo que facilita su modificación y ampliación.

`controlLamp(currentLamp, x, y);` Nos permite encender y apagar las luces del semáforo de manera eficiente. La primera variable, `currentLamp`, siempre nos indica qué semáforo estamos cambiando y no necesita ser modificada. x puede ser 0 para rojo, 1 para amarillo o 2 para verde, y y puede ser 0 para apagado o 1 para encendido.
