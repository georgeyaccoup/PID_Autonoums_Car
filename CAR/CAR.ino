#include <Wire.h>
#include <TCS3200.h>

// Pins Config
#define S0 6
#define S1 5
#define S2 4
#define S3 3
#define OUT 2
#define ENA 5   // Enable pin for Motor A
#define IN1 6   // Control pin 1 for Motor A
#define IN2 7   // Control pin 2 for Motor A
#define ENB 10  // Enable pin for Motor B
#define IN3 9   // Control pin 1 for Motor B
#define IN4 8   // Control pin 2 for Motor B
#define trigPin 9
#define echoPin 10
#define stepPin 2
#define dirPin 3

// Define velocity levels
const int LOW_VELOCITY = 60;  // 60 RPM
const int MEDIUM_VELOCITY = 80;  // 80 RPM
const int HIGH_VELOCITY = 120; // 120 RPM

long duration;
int distance;
const int stepsPerRevolution = 200;                      // Number of steps per revolution of the stepper motor
const int stepDelay = 5;                                 // Delay between steps in milliseconds
const int stepsPer30Degree = stepsPerRevolution / 12;    // Number of steps to rotate 30 degrees

TCS3200 colorSensor(S0, S1, S2, S3, OUT);

// Wrapper function to select filter color
void selectColorFilter(uint8_t color) {
  colorSensor.select_filter(color);
}
void setMotorVelocity(int velocity) {
  // Map velocity to PWM values (assuming PWM control for speed)
  int pwmValue = map(velocity, 0, 255, 0, 255);

  // Motor A
  analogWrite(ENA, pwmValue);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Motor B
  analogWrite(ENB, pwmValue);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
// Function to move forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);  // Adjust speed by changing PWM value
  analogWrite(ENB, 200);  // Adjust speed by changing PWM value
}

// Function to move backward
void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);  // Adjust speed by changing PWM value
  analogWrite(ENB, 200);  // Adjust speed by changing PWM value
}

// Function to move right
void moveRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);  // Adjust speed by changing PWM value
  analogWrite(ENB, 200);  // Adjust speed by changing PWM value
}

// Function to move left
void moveLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);  // Adjust speed by changing PWM value
  analogWrite(ENB, 200);  // Adjust speed by changing PWM value
}

// Function to stop
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// Function to rotate the stepper motor clockwise by 30 degrees
void rotate30DegreeCW() {
  digitalWrite(dirPin, HIGH); // Set direction pin to HIGH for clockwise rotation
  for (int i = 0; i < stepsPer30Degree; i++) {
    digitalWrite(stepPin, HIGH);
    delay(stepDelay);
    digitalWrite(stepPin, LOW);
    delay(stepDelay);
  }
}

// Function to rotate the stepper motor counterclockwise by 30 degrees
void rotate30DegreeCCW() {
  digitalWrite(dirPin, LOW); // Set direction pin to LOW for counterclockwise rotation
  for (int i = 0; i < stepsPer30Degree; i++) {
    digitalWrite(stepPin, HIGH);
    delay(stepDelay);
    digitalWrite(stepPin, LOW);
    delay(stepDelay);
  }
}

// Function to return the stepper motor to its initial position (0 degrees)
void returnToInitialPosition() {
  digitalWrite(dirPin, HIGH); // Set direction pin to HIGH for clockwise rotation
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delay(stepDelay);
    digitalWrite(stepPin, LOW);
    delay(stepDelay);
  }
}

void stopMotor() {
  digitalWrite(stepPin, LOW); // Set step pin to LOW to stop stepping
}

void setup() {
  Serial.begin(9600);
  colorSensor.begin();
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // ColorSensor 
  selectColorFilter(RED); // Corrected function call
  int redIntensity = colorSensor.readRed();
  
  // UltrasonicSensor 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Check if red is detected and adjust motor accordingly
  // this steps check the distance then check the color

  if (redIntensity > 1000) {
    stopMotors();
    delay(stepDelay);
  } else {
    // If no red is detected, move forward
    moveForward();
  }
  // Check for obstacle using ultrasonic sensor
  if (distance < 20) {  // If an obstacle is detected within 20 cm, stop moving
    stopMotors();
  }
}
