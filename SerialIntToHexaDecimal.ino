//Many thanks to Nick Gammon for the basis of this code
//http://www.gammon.com.au/serial

const unsigned int MAX_MESSAGE_LENGTH = 12;
volatile byte b_in = 0b10000000;
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
}

void loop() {

 //Check to see if anything is available in the serial receive buffer
 while (Serial.available() > 0)
 {
   //Create a place to hold the incoming message
   byte inByte = Serial.parseInt();
   if(inByte == NULL) continue;
   /*
   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n') )
   {
     //Add the incoming byte to our message
     message[message_pos] = inByte;
     message_pos++;
   }
   */
   //Full message received...
   /*
   else
   {
      //Add null character to string
      message[message_pos] = '\0';

      //Print the message (or do other things)
      Serial.println(message);
      int number = atoi(message);
      Serial.println(number);

     //Reset for the next message
     message_pos = 0;
   }
   */
   Serial.print("inByte:");
   Serial.println(inByte);
   Serial.print("b_in;");
   Serial.println(b_in);
   Serial.println("");
   byteToArrays(inByte);
 }
 delay(100);
}
