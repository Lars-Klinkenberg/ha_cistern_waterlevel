#define TXD1 1
#define RXD1 3

#define TRIGGER_PIN  32
#define ECHO_PIN     39

#include <HardwareSerial.h>

HardwareSerial mySerial(1);

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, RXD1, TXD1);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("ESP32 UART Sensor Server");
}

void loop() {
  // Check if data is available from UART
  if (mySerial.available()) {
    String command = mySerial.readStringUntil('\n');
    command.trim(); // Remove whitespace

    if (command == "MEASURE") {
      float distance = measureDistance();

      if (distance < 0) {
        mySerial.println("ERROR");
        Serial.println("Measurement timeout");
      } else {
        mySerial.println(String(distance, 3)); // Send distance in meters with 3 decimals
        Serial.print("Measured and sent: ");
        Serial.print(distance);
        Serial.println(" m");
      }
    } else {
      Serial.println("Unknown command: " + command);
    }
  }
}

float measureDistance() {
  long duration;
  float distance;

  // Trigger pulse
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Echo pulse
  duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout

  if (duration == 0) {
    return -1.0; // Timeout = invalid
  }

  // Calculate distance (meters)
  distance = (duration / 2.0) * 0.000343;
  return distance;
}
