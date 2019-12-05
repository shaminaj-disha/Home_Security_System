#include <Keypad.h>

const byte Rows= 4; //number of rows on the keypad i.e. 4
const byte Cols= 4; //number of columns on the keypad i,e, 3



char keymap[Rows][Cols]=
{
{'1', '2', '3','A'},
{'4', '5', '6','B'},
{'7', '8', '9','C'},
{'*', '0', '#','D'}
};

byte rPins[Rows]= {A0,A1,A2,A3}; //Rows 0 to 3
byte cPins[Cols]= {A4,A5,A6,A7}; //Columns 0 to 3

Keypad kpd= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  char keypressed = kpd.getKey();
     if (keypressed != NO_KEY)
     { 
          Serial.println(keypressed);
     }
}
