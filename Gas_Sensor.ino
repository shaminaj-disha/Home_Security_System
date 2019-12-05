int smokePin = A9;
//int sensorThres = 400;
int redLed = 13;

void setup() {
  pinMode(smokePin, INPUT);
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int analogSensor = analogRead(smokePin);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  /* Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    
  }
  else
  {
    digitalWrite(redLed, LOW);
  }*/
  delay(1000);

}
