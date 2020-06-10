// Setting global variables

int inches = 0;

int cm = 0;

int Posterior = 0;

int Anterior = 0;

int Difference = 0;

int differenceComparison = 0;

// Configuring Ultrasonic Distance Sensor

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);

}

void loop()
{
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  // Setting signal input variables
  Posterior = analogRead(A0);
  Anterior = analogRead(A1);
  // Performing signal comparison analysis
  differenceComparison = (2.5 * Anterior - Posterior);
  // Determining motor direction and speed as well as
  // haptic feedback output
  if (cm < 5 && differenceComparison < -5) { //Extension Classification and object close
    analogWrite(11, 75);
    analogWrite(10, 0);
    digitalWrite(4, HIGH);
  }
  if (cm >= 5 && differenceComparison < -5) { //Extension Classification and object not close
    analogWrite(11, 255);
    analogWrite(10, 0);
    digitalWrite(4, LOW);
  }
  if (cm < 5 && differenceComparison > 5) { // Flexion Classification and object close
    analogWrite(10, 75);
    analogWrite(11, 0);
    digitalWrite(4, HIGH);
  }
  if (cm >= 5 && differenceComparison > 5) { // Flexion Classification and object not close
    analogWrite(10, 255);
    analogWrite(11, 0);
    digitalWrite(4, LOW);
  }
  if (abs(differenceComparison) <= 5) { //Values under tolerance level
    analogWrite(10, 0);
    analogWrite(11, 0);
    digitalWrite(4, LOW);
  }
  // Printing distance detector information
  Serial.print(cm);
  Serial.print("cm,");
  Serial.print(inches);
  Serial.println("in");
  delay(50); // Wait for 50 millisecond(s)
  digitalWrite(4, LOW);
}
