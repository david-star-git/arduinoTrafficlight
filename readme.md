## Language Versions
[![English](https://img.shields.io/badge/English-English-blue)](readme.md)
[![German](https://img.shields.io/badge/Deutsch-German-blue)](readme_de.md)
[![Spanish](https://img.shields.io/badge/Español-Spanish-blue)](readme_es.md)

# Introduction

Traffic management is a critical aspect of urban planning, and understanding the operation of traffic lights is fundamental to creating efficient transportation systems. Our group school project focuses on the design and control of a simulated traffic light system using an Arduino microcontroller. The objective of this project is to provide a hands-on learning experience in the field of embedded systems and programming.

# Purpose of the Project

Traffic lights are an integral part of our daily lives, and their efficient operation is essential for road safety and traffic flow. By simulating a traffic light system with Arduino, we aim to offer students a practical understanding of how traffic lights work, how they can be controlled, and the underlying principles of traffic management. Our project allows students to explore the world of electronics and programming, applying their knowledge to create a functioning model of a real-world system.

# Project Benefits

This project offers several benefits to students and educators:

- **Hands-On Learning:** Students gain practical experience in hardware setup, coding, and system control, which is invaluable for those pursuing careers in engineering, computer science, or related fields.

- **Modularity:** The project is designed to be easily expandable, allowing students to add and control additional sets of traffic lights, reflecting real-world traffic intersections.

- **Timing and Sequencing:** Students can experiment with different timing sequences for traffic lights, exploring the impact on traffic flow and efficiency.

- **Group Collaboration:** This project encourages teamwork, as students work together to design and build a functioning traffic light system.

- **Problem Solving:** Students can troubleshoot and debug the system, enhancing their problem-solving skills.

- **Real-World Application:** Understanding how traffic light systems work can be directly applied to urban planning and traffic management, providing valuable insights into traffic engineering.

We hope that this project serves as an educational tool, inspiring students to explore the fascinating world of electronics, programming, and traffic management, ultimately preparing them for future challenges and opportunities in technology and engineering fields.

In the following part of this documentation, we will explain the functionality of the code, breaking down each component to help you understand how this simulated traffic light system is designed and controlled. This will provide a detailed insight into the project's inner workings and how it can be used as a learning tool for students interested in technology and engineering.

## Defining Variables

### pins

```cpp
int RedPins[] = {5, 8};
int YellowPins[] = {6, 9};
int GreenPins[] = {7, 10};
```
Here, we define arrays for Red, Yellow, and Green light pins. These arrays are used to associate each color with the specific pins they are connected to.

### Lamps

```cpp
int numLamps = 2;
```
This variable specifies the total number of lamps. In the example, you have two lamps, but this value can be adjusted to handle a different number of lamps easily.

```cpp
int currentLamp = 1;
```
This variable keeps track of the current lamp being controlled. It allows the code to cycle through the lamps efficiently.

### Timings

```cpp
int greenDuration = 5000;  // Green light duration
int yellowDuration = 2000; // Yellow light duration
int redDuration = 1000;    // Red light duration
int blinkDuration = 1000;  // Blinking duration for green before turning yellow
int blinkTimes = 3;        // Number of times to blink the green light before turning it yellow
```
These variables define the durations and timings for the traffic light sequence, making it easy to adjust the timing as needed without changing multiple instances in the code.

## Initialising pins

```cpp
void setup() {
  // Initialize the pins
  for (int i = 0; i < numLamps; i++) {
    pinMode(RedPins[i], OUTPUT);
    pinMode(YellowPins[i], OUTPUT);
    pinMode(GreenPins[i], OUTPUT);
  }
}
```
The `setup` function initializes the pins for all lamps. By using a loop and the `numLamps` variable, it's easy to scale the code for a different number of lamps. This keeps the code maintainable and efficient.

## Defining functions

### controlLamp

```cpp
void controlLamp(int lampNum, int color, int state) {
  int lampIndex = lampNum - 1;  // Lamp numbers start from 1

  if (lampIndex >= 0 && lampIndex < numLamps) {
    int pin;

    switch (color) {
      case 0:  // Red
        pin = RedPins[lampIndex];
        break;
      case 1:  // Yellow
        pin = YellowPins[lampIndex];
        break;
      case 2:  // Green
        pin = GreenPins[lampIndex];
        break;
      default:
        return;  // Invalid color
    }

    if (state == 0) {
      digitalWrite(pin, LOW);  // Turn off
    } else if (state == 1) {
      digitalWrite(pin, HIGH);  // Turn on
    }
  }
}
```
The `controlLamp` function allows you to control the lights of a specific lamp by specifying its number, the color, and the state (on or off). This function encapsulates the logic to set the corresponding pin based on the provided parameters, making the code more modular and readable.

### turnOnAllRedLights

```cpp
void turnOnAllRedLights() {
  for (int lampNum = 1; lampNum <= numLamps; lampNum++) {
    controlLamp(lampNum, 0, 1);  // Turn on the Red light for the current lamp
  }
}
```
The `turnOnAllRedLights` function is designed to turn on all the red lights for all lamps at once. This function provides a convenient way to handle all the red lights together.

## Main loop function

```cpp
void loop() {
  // All red lights turn on
  turnOnAllRedLights();
  delay(redDuration);

  // Red -> Yellow
  controlLamp(currentLamp, 0, 0);
  controlLamp(currentLamp, 1, 1);
  delay(yellowDuration);

  // Yellow -> Green
  controlLamp(currentLamp, 1, 0);
  controlLamp(currentLamp, 2, 1);
  delay(greenDuration);

  // Green Blinking
  for (int i = 0; i < blinkTimes + 1; i++) {
    controlLamp(currentLamp, 2, 1);
    delay(blinkDuration);
    controlLamp(currentLamp, 2, 0);
    delay(blinkDuration);
  }

  // Green -> Yellow
  controlLamp(currentLamp, 2, 0);
  controlLamp(currentLamp, 1, 1);
  delay(yellowDuration);

  // Yellow off
  controlLamp(currentLamp, 1, 0);

  // Next lamp
  currentLamp = (currentLamp % numLamps) + 1;
}
```
In the `loop` function, the code controls the traffic light sequence. It sequentially handles each lamp, turning on and off the lights while keeping track of timing and efficiently moving to the next lamp. This approach minimizes redundancy and is efficient because it scales easily to different numbers of lamps. The use of functions like `controlLamp` and `turnOnAllRedLights` also keeps the code organized and maintainable, making it easier to modify and extend.

`controlLamp(currentLamp, x, y);` Allows us to to turn the lights on and off efficiently. The first variable `currentLamp` always tells us what lamp we are changing this doesn't need to be changed. x is either 0 for red, 1 for yellow or 2 for green and y is either 0 for off or 1 for on.

## License

This project is licensed under the [GNU General Public License, version 3.0](LICENSE). You can find the full license text [here](https://www.gnu.org/licenses/gpl-3.0.html).
