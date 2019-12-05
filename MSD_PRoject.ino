#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>

const byte Rows= 4; //number of rows on the keypad i.e. 4
const byte Cols= 4; //number of columns on the keypad i,e, 4
char keymap[Rows][Cols]=
{
{'1', '2', '3','A'},
{'4', '5', '6','B'},
{'7', '8', '9','C'},
{'*', '0', '#','D'}
};

byte rPins[Rows]= {11,10,9,8}; //Rows 0 to 3
byte cPins[Cols]= {7,6,5,4}; //Columns 0 to 3

Keypad keypad_key= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);

char password[4];
char initial_password[4],new_password[4];
int i=0;
int relay_pin = 10;
char key_pressed=0;
LiquidCrystal liquid_crystal_display(9,8,7,6,5,4);

//temperature
int valTemp;
int tempPin = A1;
//Pir 
int pirPin = 3;              // the pin that the sensor is atteched to
int pirState = LOW;             // by default, no motion detected
//MQ-6
int smokePin = A0;

int led = 13;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(tempPin,INPUT);      // initialize LM35sensor as an input
    pinMode(pirPin, INPUT);    // initialize PIRsensor as an input
    pinMode(smokePin, INPUT);     // initialize MQ-6 sensor as an input
    pinMode(led,OUTPUT);


    pinMode(relay_pin, OUTPUT);
    liquid_crystal_display.begin(16,2);
    liquid_crystal_display.print("MSD Project");
    liquid_crystal_display.setCursor(0,1);
    liquid_crystal_display.print("Electronic Lock ");
    delay(2000);
    liquid_crystal_display.clear();
    liquid_crystal_display.print("Enter Password");
    liquid_crystal_display.setCursor(0,1);
    initialpassword();

    


  
    
}

void loop() {
    // put your main code here, to run repeatedly:
  
    valTemp = analogRead(tempPin);
    float mv = ( valTemp/1024.0)*5000;
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
  
  
    //GAS Sensor
    int analogSensor = analogRead(smokePin);
    Serial.print("Gas Value: ");
    Serial.println(analogSensor);
    delay(1000);
  
    //PIR
    int valPIR = digitalRead(pirPin);   // read PIRsensor value
    if (valPIR == HIGH) {           // check if the sensor is HIGH
          digitalWrite(led, HIGH);   // turn LED ON
          //delay(100);                // delay 100 milliseconds 
          
          if (pirState == LOW) {
            Serial.println("Motion detected!"); 
            pirState = HIGH;       // update variable state to HIGH
          }
        } 
     else{
           digitalWrite(led, LOW); // turn LED OFF
           //delay(200);             // delay 200 milliseconds 
            
           if (pirState == HIGH){
           Serial.println("Motion stopped!");
           pirState = LOW;       // update variable state to LOW
          }
     }

     //password lock
     digitalWrite(relay_pin, HIGH);
     char key_pressed = keypad_key.getKey();
     /*if (key_pressed != NO_KEY)
     { 
          Serial.println(key_pressed);
     }*/
     if(key_pressed=='#')
        change();
     if(key_pressed)
     {
       password[i++]=key_pressed;
       liquid_crystal_display.print(key_pressed);
    }
    if(i==4)
    {
      delay(200);
      for(int j=0;j<4;j++)
        initial_password[j]=EEPROM.read(j);
        
      if(!(strncmp(password, initial_password,4)))
      {
        liquid_crystal_display.clear();
        liquid_crystal_display.print("Pass Accepted");
        digitalWrite(relay_pin, LOW);
        delay(2000);
        liquid_crystal_display.setCursor(0,1);
        liquid_crystal_display.print("Pres # to change");
        delay(2000);
        liquid_crystal_display.clear();
        liquid_crystal_display.print("Enter Password:");
        liquid_crystal_display.setCursor(0,1);
        i=0;
      }
      else
      {
        digitalWrite(relay_pin, HIGH);
        liquid_crystal_display.clear();
        liquid_crystal_display.print("Wrong Password");
        liquid_crystal_display.setCursor(0,1);
        liquid_crystal_display.print("Pres # to Change");
        delay(2000);
        liquid_crystal_display.clear();
        liquid_crystal_display.print("Enter Password");
        liquid_crystal_display.setCursor(0,1);
        i=0;
      }
    }
}

void change()
{
  int j=0;
  liquid_crystal_display.clear();
  liquid_crystal_display.print("Current Password");
  liquid_crystal_display.setCursor(0,1);
  while(j<4)
  {
    char key=keypad_key.getKey();
    if(key)
    {
      new_password[j++]=key;
      liquid_crystal_display.print(key);
    }
    key=0;
  }
  delay(500);
  if((strncmp(new_password, initial_password, 4)))
  {
    liquid_crystal_display.clear();
    liquid_crystal_display.print("Wrong Password");
    liquid_crystal_display.setCursor(0,1);
    liquid_crystal_display.print("Try Again");
    delay(1000);
  }
  else
  {
    j=0;
    liquid_crystal_display.clear();
    liquid_crystal_display.print("New Password:");
    liquid_crystal_display.setCursor(0,1);
    while(j<4)
    {
      char key=keypad_key.getKey();
      if(key)
      {
        initial_password[j]=key;
        liquid_crystal_display.print(key);
        EEPROM.write(j,key);
        j++;
      }
    }
    liquid_crystal_display.print("Pass Changed");
    delay(1000);
  }
  liquid_crystal_display.clear();
  liquid_crystal_display.print("Enter Password");
  liquid_crystal_display.setCursor(0,1);
  key_pressed=0;
}

void initialpassword(){
  for(int j=0;j<4;j++)
    EEPROM.write(j, j+49);
  for(int j=0;j<4;j++)
    initial_password[j]=EEPROM.read(j);
}
