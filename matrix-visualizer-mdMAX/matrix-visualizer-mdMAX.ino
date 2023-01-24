#include <Arduino.h>

// Uses most of the functions in the library
#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES  4

#define CLK_PIN   13  // or SCK
#define DATA_PIN  5  // or MOSI
#define CS_PIN    10  // or SS

int clearCount = 0;

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup()
{
  Serial.begin(230400);
  Serial.setTimeout(0);
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 1);

}

String input = "";

bool getInput() {
  while (Serial.available()) {
    char c = (char) Serial.read();
    if (c == '\n')
      return true; //terminator found

    input += c; // accumulate characters into input string
  }
  return false;
}

void loop()
{
  if (getInput()) {

    if(input.toInt() == 0) {
      mx.clear();
      mx.setRow(0, 0xff);
    }
//    Serial.print("I received: ");
//    Serial.println(input); 
    if (input.length() == 32) {

//      if (clearCount > 5) {
//        mx.clear();
//        clearCount = 0;
//      }
//
//      clearCount++;

      mx.clear();

      for (int i = 0; i < 8; i++) {
        mx.setPoint(atoi(input[i]), i, 0xff); 
      }
      for (int i = 8; i < 16; i++) {
        mx.setPoint(atoi(input[i]), i, 0xff);
      }
      for (int i = 16; i < 24; i++) {
        mx.setPoint(atoi(input[i]), i, 0xff);
      }
      for (int i = 24; i < 32; i++) {
        mx.setPoint(atoi(input[i]), i, 0xff);
      }
      
    }

    //done processing? reset the input string
    input = "";
  }

}

//mx.setRow(0, 0x00);

//      for (int i = 0; i < 8; i++) {
//        mx.setPoint(atoi(input[i]), i, 0xff);
//        mx.setPoint(atoi(input[map(i, 0, 8, 8, 16)]), map(i, 0, 8, 8, 16), 0xff);
//        mx.setPoint(atoi(input[map(i, 0, 8, 16, 24)]), map(i, 0, 8, 16, 24), 0xff);
//        mx.setPoint(atoi(input[map(i, 0, 8, 24, 32)]), map(i, 0, 8, 24, 32), 0xff);
//        // mx.setRow(0, 0x00); 
//      }
