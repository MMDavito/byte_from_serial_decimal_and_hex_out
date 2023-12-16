//Many thanks to Nick Gammon for the basis of this code
//http://www.gammon.com.au/serial

//https://github.com/alikabeel/Letters-and-Numbers-Seven-Segment-Display-Library
#include <SevenSegmentDisplay.h>
volatile byte b_in = 0b10000000;
volatile byte counter = 0b00000000;
const byte reset = 0xFF;



//MostSignificant, to LSB
//First 3 is decimal, last two is Hex
byte digitPins[] = {11,12,13,9,10};

SevenSegmentDisplay screenName(2, 8, 7, 6, 5, 3, 4, NULL, false);//CommonCathode no decimal-point


const unsigned int MAX_MESSAGE_LENGTH = 12;
char decimalArray [3] = {'2','0','0'};
String decimal = "";
String hex = "";
char hexArray[2] = {'0','0'};

void byteToArrays(byte value) {
  decimal="";
  hex="";
  
  
  if(value < 0x10) hex+= "0";
  if(value < 100) decimal += "0";
  if(value < 10) decimal += "0";

  hex += String(value,HEX);
  hex.toUpperCase();
  Serial.print("HEX: ");
  Serial.println(hex);
  Serial.println("");
  decimal += String(value, DEC);
  
  Serial.print("Decimal: ");
  Serial.println(decimal);
  Serial.print("length: ");
  Serial.println(decimal.length());
  decimal.toCharArray(decimalArray, 4);
  if(value >=100 && value < 200) decimalArray[0] = '1';
  else if(value >= 200) decimalArray[0] = '2';
  else decimalArray[0] = '0';

  Serial.println("DecimalArray:");
  for(int i=0; i<3; i++) Serial.println(decimalArray[i]);

  Serial.println("");
  hex.toCharArray(hexArray, 3);
  Serial.println("HexArray:");
  for(int i=0; i<2; i++) Serial.println(hexArray[i]);
  
}


void setup() {
 Serial.begin(9600);
 
  for(int i=0; i<5; i++)
  {
    pinMode(digitPins[i],OUTPUT);
    digitalWrite(digitPins[i],LOW);
  }
 
}

void loop() {

  //Check to see if anything is available in the serial receive buffer
  int numChars = 0;
  while (Serial.available() > 0)
  {
    //Create a place to hold the incoming message
    byte inByte = Serial.parseInt();
    if(inByte == NULL && numChars > 0) continue;
    numChars += 1;
    Serial.print("inByte:");
    Serial.println(inByte);
    Serial.print("b_in;");
    Serial.println(b_in);
    Serial.println("");
    byteToArrays(inByte);
  }
  for(int i=0; i<5; i++)
  {
    if(i>2)
    {
      screenName.displayCharacter(hexArray[i - 3]);
      digitalWrite(digitPins[i],HIGH);
      delay(5);//Longer light on since green is more dim, could use nanoseconds for red if it turns out to be causing bad refresh-rate.
    }
    else
    {
      screenName.displayCharacter(decimalArray[i]);
      digitalWrite(digitPins[i],HIGH);
      delay(1);
    }
    digitalWrite(digitPins[i],LOW); 
  }
}
