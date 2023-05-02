#include <AccelStepper.h>
#include <Servo.h>

#define PIN_SERVO D4

Servo servo;

// #define STEPS_PER_REV 200*16
uint16_t MAX_SPEED = 5000;
uint16_t ACCEL = 5000;

#define NUMBER_OF_AXIS 2

const int dirPins[NUMBER_OF_AXIS] = { D5, D8 };
const int stepPins[NUMBER_OF_AXIS] = { D6, D7 };

AccelStepper steppers[NUMBER_OF_AXIS];

void setup() {
  // servo.attach(PIN_SERVO);
  // servo.write(0);
  Serial.begin(115200); // initialize serial communication
  for (int i = 0; i < NUMBER_OF_AXIS; i++) {
    steppers[i] = AccelStepper(1, stepPins[i], dirPins[i]);
    steppers[i].setMaxSpeed(MAX_SPEED);
    steppers[i].setAcceleration(ACCEL);
  }
}

void loop() {
  // check for incoming serial data
  readSerial();

  // run the stepper motors
  for (int i = 0; i < NUMBER_OF_AXIS; i++) {
    if (steppers[i].distanceToGo() != 0) {
      steppers[i].run();
    }
  }
}

/*

packet structure

msglength msg packetlength payload

*/

int bufferIndex = 0;
uint8_t msgBuffer[100];

void readSerial() {
  if (Serial.available() > 0) {
    uint8_t incoming = Serial.read(); 
    if (incoming == 0x0A) { // \n terminated
      uint8_t msg = msgBuffer[0];
      if (msg == 0x00) { // "go"
        // 2 signed floats
        float floatData0 = readFloat(msgBuffer, 1);
        float floatData1 = readFloat(msgBuffer, 5);
        
        steppers[0].moveTo(floatData0);
        steppers[1].moveTo(floatData1);

        // in js should await this response
        Serial.println("moving");
      }

      if (msg == 0x01) { // "accel"
        float value = readFloat(msgBuffer, 1);
        for (int i = 0; i < NUMBER_OF_AXIS; i++) {
          steppers[i].setAcceleration(value);
        }
        Serial.println("accel");
        Serial.println(value);
      }

      if (msg == 0x02) { // "maxSpeed"
        float value = readFloat(msgBuffer, 1);
        for (int i = 0; i < NUMBER_OF_AXIS; i++) {
          steppers[i].setMaxSpeed(value);
        }
        Serial.println("speed");
        Serial.println(value);
      }

      if (msg == 0x03) { // "servo"
        uint16_t pulse_us = read_uint16(msgBuffer, 1);
        servo.writeMicroseconds(pulse_us);

        Serial.println("servo");
        Serial.println(pulse_us);
      }

      bufferIndex = 0;
    } else {
      msgBuffer[bufferIndex] = incoming;
      bufferIndex++;
    }
  }
}

float readFloat(uint8_t* buffer, int index) {
  uint8_t byte0 = buffer[index];
  uint8_t byte1 = buffer[index+1];
  uint8_t byte2 = buffer[index+2];
  uint8_t byte3 = buffer[index+3];

  // int32_t intData = (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3;
  // float floatData = (float)intData;

  uint8_t byteArray[] = {byte0, byte1, byte2, byte3};
  float floatValue;
  memcpy(&floatValue, &byteArray, sizeof(floatValue));

  Serial.println(floatValue);

  return floatValue;
}

float read_uint16(uint8_t* buffer, int index) {
  uint8_t byte0 = buffer[index];
  uint8_t byte1 = buffer[index+1];

  uint8_t byteArray[] = {byte0, byte1};
  uint16_t value;
  memcpy(&value, &byteArray, sizeof(value));

  return value;
}


