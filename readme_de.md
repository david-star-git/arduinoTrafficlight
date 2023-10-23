## Sprachversionen
[![Englisch](https://img.shields.io/badge/Englisch-English-blue)](readme.md)
[![Deutsch](https://img.shields.io/badge/Deutsch-German-blue)](readme_de.md)
[![Spanisch](https://img.shields.io/badge/Spanisch-Spanish-blue)](readme_es.md)

# Einführung

Die Verkehrssteuerung ist ein entscheidender Aspekt der Stadtplanung, und das Verständnis der Funktionsweise von Verkehrsampeln ist grundlegend für die Schaffung effizienter Transportsysteme. Unser Gruppenschulprojekt konzentriert sich auf die Gestaltung und Steuerung eines simulierten Verkehrsampelsystems mithilfe eines Arduino-Mikrocontrollers. Das Ziel dieses Projekts besteht darin, eine praktische Lernerfahrung auf dem Gebiet der eingebetteten Systeme und der Programmierung zu bieten.

# Zweck des Projekts

Verkehrsampeln sind ein wesentlicher Bestandteil unseres täglichen Lebens, und ihre effiziente Funktion ist für die Verkehrssicherheit und den Verkehrsfluss unerlässlich. Durch die Simulation eines Verkehrsampelsystems mit Arduino möchten wir den Studierenden ein praktisches Verständnis dafür vermitteln, wie Verkehrsampeln funktionieren, wie sie gesteuert werden können und die zugrunde liegenden Prinzipien der Verkehrssteuerung. Unser Projekt ermöglicht es den Studierenden, die Welt der Elektronik und Programmierung zu erkunden und ihr Wissen anzuwenden, um ein funktionierendes Modell eines realen Systems zu erstellen.

# Projektvorteile

Dieses Projekt bietet mehrere Vorteile für Studierende und Pädagogen:

- **Praktisches Lernen:** Die Studierenden sammeln praktische Erfahrungen in Hardware-Einrichtung, Codierung und Systemsteuerung, was für diejenigen, die eine Karriere in Ingenieurwissenschaften, Informatik oder verwandten Bereichen anstreben, von unschätzbarem Wert ist.

- **Modularität:** Das Projekt ist darauf ausgelegt, leicht erweiterbar zu sein, so dass die Studierenden zusätzliche Verkehrsampeln hinzufügen und steuern können, was realen Verkehrskreuzungen entspricht.

- **Zeitplanung und Sequenzierung:** Die Studierenden können verschiedene Zeitabläufe für Verkehrsampeln ausprobieren und deren Auswirkungen auf den Verkehrsfluss und die Effizienz untersuchen.

- **Gruppenzusammenarbeit:** Dieses Projekt fördert die Teamarbeit, da die Studierenden zusammenarbeiten, um ein funktionierendes Verkehrsampelsystem zu entwerfen und zu bauen.

- **Problembehebung:** Die Studierenden können das System troubleshooten und debuggen, wodurch ihre Problemlösungsfähigkeiten verbessert werden.

- **Anwendung im echten Leben:** Das Verständnis der Funktionsweise von Verkehrsampelsystemen kann direkt auf die Stadtplanung und Verkehrssteuerung angewendet werden und wertvolle Einblicke in die Verkehrstechnik bieten.

Wir hoffen, dass dieses Projekt als Bildungsinstrument dient und die Studierenden dazu inspiriert, die faszinierende Welt der Elektronik, Programmierung und Verkehrssteuerung zu erkunden und sie letztendlich auf zukünftige Herausforderungen und Möglichkeiten in den Bereichen Technologie und Ingenieurwissenschaften vorbereitet.

Im folgenden Abschnitt dieser Dokumentation werden wir die Funktionalität des Codes erläutern, indem wir jeden Bestandteil zerlegen, um Ihnen zu helfen zu verstehen, wie dieses simulierte Verkehrsampelsystem entworfen und gesteuert wird. Dies bietet detaillierte Einblicke in die Funktionsweise des Projekts und wie es als Lernwerkzeug für an Technologie und Ingenieurwissenschaften interessierte Studierende genutzt werden kann.

## Variablen definieren

### pins

```cpp
int RedPins[] = {5, 8};
int YellowPins[] = {6, 9};
int GreenPins[] = {7, 10};
```

Hier definieren wir Arrays für die roten, gelben und grünen Lampenpins. Diese Arrays werden verwendet, um jede Farbe mit den spezifischen Pins zu verknüpfen, an die sie angeschlossen sind.

### Lampen

```cpp
int currentLamp = 1;
```

Diese Variable verfolgt die aktuelle Lampe, die gesteuert wird. Sie ermöglicht es dem Code, effizient durch die Lampen zu wechseln.

### Zeitabläufe

```cpp
int greenDuration = 5000;  // Dauer der grünen Ampel
int yellowDuration = 2000; // Dauer der gelben Ampel
int redDuration = 1000;    // Dauer der roten Ampel
int blinkDuration = 1000;  // Dauer des Blinkens für grün, bevor es gelb wird
int blinkTimes = 3;        // Anzahl der Male, die die grüne Ampel blinkt, bevor sie gelb wird
```

Diese Variablen definieren die Dauer und Zeitabläufe für die Verkehrsampelsequenz, um die Zeiteinstellungen einfach anpassen zu können, ohne mehrere Stellen im Code ändern zu müssen.

## Pins initialisieren

```cpp
void setup() {
  // Initialisieren der Pins
  for (int i = 0; i < numLamps; i++) {
    pinMode(RedPins[i], OUTPUT);
    pinMode(YellowPins[i], OUTPUT);
    pinMode(GreenPins[i], OUTPUT);
  }
}
```

Die `setup`-Funktion initialisiert die Pins für alle Lampen. Durch die Verwendung einer Schleife und der Variablen `numLamps` lässt sich der Code leicht für eine unterschiedliche Anzahl von Lampen skalieren. Dies hält den Code wartbar und effizient.

## Funktionen definieren

### controlLamp

```cpp
void controlLamp(int lampNum, int color, int state) {
  int lampIndex = lampNum - 1;  // Lampennummern beginnen bei 1

  if (lampIndex >= 0 && lampIndex < numLamps) {
    int pin;

    switch (color) {
      case 0:  // Rot
        pin = RedPins[lampIndex];
        break;
      case 1:  // Gelb
        pin = YellowPins[lampIndex];
        break;
      case 2:  // Grün
        pin = GreenPins[lampIndex];
        break;
      default:
        return;  // Ungültige Farbe
    }

    if (state == 0) {
      digitalWrite(pin, LOW);  // Ausschalten
    } else if (state == 1) {
      digitalWrite(pin, HIGH);  // Einschalten
    }
  }
}
```

Die Funktion `controlLamp` ermöglicht es, die Lichter einer bestimmten Lampe zu steuern, indem die Nummer, die Farbe und der Zustand (an oder aus) angegeben werden. Diese Funktion enthält die Logik, um den entsprechenden Pin basierend auf den bereitgestellten Parametern festzulegen, was den Code modulärer und lesbarer macht.

### turnOnAllRedLights

```cpp
void turnOnAllRedLights() {
  for (int lampNum = 1; lampNum <= numLamps; lampNum++) {
    controlLamp(lampNum, 0, 1);  // Rotes Licht für die aktuelle Lampe einschalten
  }
}
```

Die Funktion `turnOnAllRedLights` ist darauf ausgelegt, alle roten Lichter aller Lampen gleichzeitig einzuschalten. Diese Funktion bietet eine bequeme Möglichkeit, alle roten Lichter gemeinsam zu handhaben.

## Haupt-Schleifenfunktion

```cpp
void loop() {
  // Alle roten Lichter einschalten
  turnOnAllRedLights();
  delay(redDuration);

  // Rot -> Gelb
  controlLamp(currentLamp, 0, 0);
  controlLamp(currentLamp, 1, 1);
  delay(yellowDuration);

  // Gelb -> Grün
  controlLamp(currentLamp, 1, 0);
  controlLamp(currentLamp, 2, 1);
  delay(greenDuration);

  // Grünes Blinken
  for (int i = 0; i < blinkTimes + 1; i++) {
    controlLamp(currentLamp, 2, 1);
    delay(blinkDuration);
    controlLamp(currentLamp, 2, 0);
    delay(blinkDuration);
  }

  // Grün -> Gelb
  controlLamp(currentLamp, 2, 0);
  controlLamp(currentLamp, 1, 1);
  delay(yellowDuration);

  // Gelb ausschalten
  controlLamp(currentLamp, 1, 0);

  // Nächste Lampe
  currentLamp = (currentLamp % numLamps) + 1;
}
```

In der `loop`-Funktion steuert der Code die Verkehrsampelsequenz. Er behandelt nacheinander jede Lampe, schaltet die Lichter ein und aus und behält dabei die Zeit im Auge, bevor er effizient zur nächsten Lampe wechselt. Diese Herangehensweise minimiert Redundanz und ist effizient, da sie sich problemlos auf verschiedene Lampenanzahlen skalieren lässt. Die Verwendung von Funktionen wie `controlLamp` und `turnOnAllRedLights` hält den Code organisiert und wartbar, was die Modifikation und Erweiterung erleichtert.

`controlLamp(currentLamp, x, y);` Erlaubt es uns, die Lichter effizient ein- und auszuschalten. Die erste Variable `currentLamp` gibt immer an, welche Lampe gerade geändert wird. Dies muss nicht geändert werden. x ist entweder 0 für rot, 1 für gelb oder 2 für grün und y ist entweder 0 für aus oder 1 für an.
