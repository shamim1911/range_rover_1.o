#define trigPin 7
#define echoPin 8
#define inchesDivisor 74
char requestedUnit = 'C';
bool serialMonitorEnabled = true;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command == "Start") {
      serialMonitorEnabled = true;
      Serial.println("Shamim Boss Started this, So we are starting");
    } else if (command == "Stop") {
      serialMonitorEnabled = false;
      Serial.println("Shamim Boss Stopped This, So we are stopped");
    } else if (command == "I" || command == "C") {
      requestedUnit = command.charAt(0);
      Serial.print("Distance unit set to: ");
      Serial.println(requestedUnit);
    }
  }

  long duration;
  float inches, cm;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  inches = duration / inchesDivisor;
  cm = duration / 58.2;

  if (serialMonitorEnabled) {
    if (requestedUnit == 'I') {
      Serial.print("Distance in inches: ");
      Serial.print(inches);
      Serial.println(" in");
    } else {
      Serial.print("Distance in cm: ");
      Serial.print(cm);
      Serial.println(" cm");
    }
  }

  delay(100);
}
