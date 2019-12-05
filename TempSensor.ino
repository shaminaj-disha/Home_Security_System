int val;
int tempPin = A8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tempPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000;
  float cel = mv/10; 
  
  
  float farh = (cel*9)/5 + 32;
  
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);


  /* uncomment this to get temperature in farenhite
  Serial.print("TEMPRATURE = ");
  Serial.print(farh);
  Serial.print("*F");
  Serial.println();
  
  
  */
}
