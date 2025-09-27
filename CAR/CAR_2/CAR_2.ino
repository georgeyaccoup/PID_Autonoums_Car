#include <Servo.h>

// Define the number of LDRs
const int NUM_LDRS = 4;

// Define analog pins for LDRs
const int ldrPins[NUM_LDRS] = {A0, A1, A2, A3};

// Define corresponding angles for each LDR
const int ldrAngles[NUM_LDRS] = {0, 90, 180, 270};
const int servoPin = 9;
Servo blindsServo;
int ldrValues[NUM_LDRS];
int targetAngle = 0;
void setup() {
  Serial.begin(9600);
  blindsServo.attach(servoPin);
  blindsServo.write(90);
  delay(1000); // Wait for servo to move
  Serial.println("Blinds Control System Initialized.");
}

// Function to read LDR values
void readLDRs() {
  for(int i = 0; i < NUM_LDRS; i++) {
    ldrValues[i] = analogRead(ldrPins[i]);
    Serial.print("LDR");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(ldrValues[i]);
    Serial.print("  ");
  }
  Serial.println();
}

int getMaxLightDirection() {
  int maxValue = ldrValues[0];
  int maxIndex = 0;
  
  for(int i = 1; i < NUM_LDRS; i++) {
    if(ldrValues[i] > maxValue) {
      maxValue = ldrValues[i];
      maxIndex = i;
    }
  }
  
  return ldrAngles[maxIndex];
}

int calculateTargetAngle(int detectedAngle) {
  int angle = detectedAngle + 90;
  
  if(angle >= 360) {
    angle -= 360;
  }
  int servoAngle = map(angle, 0, 360, 0, 180);
  
  return servoAngle;
}

void loop() {
  readLDRs();
    int detectedAngle = getMaxLightDirection();
  
  Serial.print("Detected Angle: ");
  Serial.print(detectedAngle);
  Serial.println(" degrees");
  
  // Calculate target angle by adding 90 degrees
  targetAngle = calculateTargetAngle(detectedAngle);
  Serial.print("Moving servo to: ");
  Serial.print(targetAngle);
  Serial.println(" degrees");
  blindsServo.write(targetAngle);
  delay(10000); 
}
