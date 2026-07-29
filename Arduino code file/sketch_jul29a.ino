/*
  Simple 2 Sensor Line Following Robot
  Board: Arduino UNO
  Motor Driver: L298N
*/

// ---------------- Pins ----------------

// IR Sensors
#define S1 11      // Left Sensor
#define S2 12      // Right Sensor

// Left Motor
#define ENA 5
#define IN1 4
#define IN2 3

// Right Motor
#define ENB 6
#define IN3 7
#define IN4 8

// Motor Speed (0-255)
int speedA = 125;
int speedB = 125;

void setup()
{
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);

  Serial.begin(9600);
}

void loop()
{
  int leftSensor = digitalRead(S1);
  int rightSensor = digitalRead(S2);

  Serial.print("Left: ");
  Serial.print(leftSensor);
  Serial.print("  Right: ");
  Serial.println(rightSensor);

  /*
    Most IR sensors:
    BLACK = LOW (0)
    WHITE = HIGH (1)

    If yours behaves opposite,
    swap HIGH and LOW in the conditions.
  */

  // Both sensors on white
  if (leftSensor == LOW && rightSensor == LOW)
  {
    forward();
  }

  // Left sensor detects line
  else if (leftSensor == LOW && rightSensor == HIGH)
  {
    turnLeft();
  }

  // Right sensor detects line
  else if (leftSensor == HIGH && rightSensor == LOW)
  {
    turnRight();
  }

  // Both sensors detect line
  else
  {
    stopRobot();
  }
}

// ---------------- Motor Functions ----------------

void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}

void turnLeft()
{
  // Left motor slow/stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}

void turnRight()
{
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right motor stop
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}

void stopRobot()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}