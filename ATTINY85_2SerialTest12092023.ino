/**
  Notes on the matter of 2 Software Serials.
  It appears that whatever of the 2 Serials gets its begin() call last, is the only one that the 
  ATTINY will detect when transmitting. But BOTH Serials will still recieve. The first to have
  begin() called will still receive. The other that is not the last to have begin() or listen() used
  will not respond to any input.
  ATTiny25/45/85 Pin map with CE_PIN 3 and CSN_PIN 4          
 *                         +-\/-+                             
 *       PB5  1|o   |8  Vcc ---   
 *   --- PB3  2|    |7  PB2 ---      
 *   --- PB4  3|    |6  PB1 ---  
 *   --- GND  4|    |5  PB0 ---  
 *                         +----+
*/

#include <SoftwareSerial.h>
#define RX1    PB3   // Physical Pin 2
#define TX1    PB4   // Pin 3
#define RX2    PB0   // Physical Pin 5
#define TX2    PB1   // Pin 6
SoftwareSerial mySerial1(RX1, TX1);  // Pins 2 and 3 in the order of RX TX
SoftwareSerial mySerial2(RX2, TX2);  // Pins 5 and 6 in the order of RX TX
void setup() {
  pinMode(PB2, OUTPUT);
  mySerial1.begin(9600);    // Not entirely needed
  mySerial1.write("Starting");
  mySerial2.begin(9600);
  mySerial2.write("Starting");
  digitalWrite(PB2, LOW );
  mySerial1.begin(9600);    // Seems whoever has the last "begin" is the one that works, so this one is going to be the listener
  mySerial1.write("Boogaloo");
}
uint8_t b[32];
void loop() {
    if(mySerial1.available() > 0) {       // Incoming from the first serial
      mySerial1.readBytes(b, mySerial1.available());
      digitalWrite(PB2, HIGH );
      mySerial1.flush();
      mySerial2.print((char*)b);      // Send information to the other serial
      mySerial2.flush();
      mySerial2.listen();
    }  // if
  // If there is anything needing to be done with the incoming data before sending it out, here is the place to do it. 
    if(mySerial2.available() > 0) {  
      mySerial2.readBytes(b, mySerial2.available());
      digitalWrite(PB2, LOW );
      mySerial2.flush();
      mySerial1.print((char*)b);      // Send back to the first Serial.
      mySerial1.flush();
      mySerial1.listen();             // And now back to the first Serial listening. 
    } 
  delay(100);
}
