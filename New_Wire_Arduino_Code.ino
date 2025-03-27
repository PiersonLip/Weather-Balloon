/*
  arduinoCutterCode
  Reads the serial connection. When a signal higher than 0 is received,
  Initiates cutter sequence.
*/

#define LED_BUILTIN 2  // Define built-in LED for ESP32

int REDPIN = 12;
int pauseTime = 1000;  // Renamed variable

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(REDPIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {  // Check if data is available
    int outOfBounds = Serial.parseInt();
    
    if (outOfBounds > 0) {  // If message > 0, initiate cutting
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(REDPIN, HIGH);
      delay(10000); // 10 seconds
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(REDPIN, LOW);
      delay(30000); // 30 seconds

      // Blinking sequence
      while (Serial.available() == 0) {  // Wait for new serial input to exit
        if (pauseTime > 0) {
          digitalWrite(LED_BUILTIN, HIGH);
          delay(pauseTime);
          digitalWrite(LED_BUILTIN, LOW);
          pauseTime -= 300;
        } else {
          pauseTime = 1000;  // Reset pauseTime when it gets too low
        }
      }
    }
  }
}
