int RedPins[] = {5, 8};     // Red light pins
int YellowPins[] = {6, 9};  // Yellow light pins
int GreenPins[] = {7, 10};  // Green light pins
int numLamps = 2;           // Total number of lamps

int currentLamp = 1;  // Current lamp to control
// Define timing variables (in milliseconds)
int greenDuration = 5000;  // Green light duration
int yellowDuration = 2000; // Yellow light duration
int redDuration = 1000;    // Red light duration
int blinkDuration = 1000;   // Blinking duration for green before turning yellow
int blinkTimes = 3; // Add 1 for it to work propperly

void setup() {
  // Initialize the pins
  for (int i = 0; i < numLamps; i++) {
    pinMode(RedPins[i], OUTPUT);
    pinMode(YellowPins[i], OUTPUT);
    pinMode(GreenPins[i], OUTPUT);
  }
}

// Function to control a lamp
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

void turnOnAllRedLights() {
  for (int lampNum = 1; lampNum <= numLamps; lampNum++) {
    controlLamp(lampNum, 0, 1);  // Turn on the Red light for the current lamp
  }
}


void loop() {
  turnOnAllRedLights();
  delay(redDuration);

  controlLamp(currentLamp, 0, 0);  // Red off
  controlLamp(currentLamp, 1, 1);  // Yellow on
  delay(yellowDuration);

  controlLamp(currentLamp, 1, 0);  // Yellow off
  controlLamp(currentLamp, 2, 1);  // Green on
  delay(greenDuration);

  for (int i = 0; i < blinkTimes + 1; i++) {
    controlLamp(currentLamp, 2, 1);  // Turn on the Green light for the current lamp
    delay(blinkDuration);
    controlLamp(currentLamp, 2, 0);  // Turn off the Green light for the current lamp
    delay(blinkDuration);
  }

  controlLamp(currentLamp, 2, 0);  // Green off
  controlLamp(currentLamp, 1, 1);  // Yellow on
  delay(yellowDuration);

  controlLamp(currentLamp, 1, 0);  // Yellow off

  // Move to the next lamp
  currentLamp = (currentLamp % numLamps) + 1;
}
