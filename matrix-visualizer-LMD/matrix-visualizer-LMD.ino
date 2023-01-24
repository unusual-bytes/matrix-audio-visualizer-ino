#include <LEDMatrixDriver.hpp>

// Define the ChipSelect pin for the led matrix (Dont use the SS or MISO pin of your Arduino!)
// Other pins are Arduino specific SPI pins (MOSI=DIN, SCK=CLK of the LEDMatrix) see https://www.arduino.cc/en/Reference/SPI
const uint8_t LEDMATRIX_CS_PIN = 9;

// Number of 8x8 segments you are connecting
const int LEDMATRIX_SEGMENTS = 4;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;

// The LEDMatrixDriver class instance
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);

int clearCount = 0;

void setup() {
  Serial.begin(230400);
  Serial.setTimeout(0);

  // init the display
  lmd.setEnabled(true);
  lmd.setIntensity(1);   // 0 = low, 10 = high
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

int x = 0, y = 0; // start top left
bool s = true;  // start with led on

void loop() {

  if (getInput()) {

    if (input.toInt() == 0) {
      lmd.clear();
    }

//        Serial.print("I received: ");
//        Serial.println(input);  

    if (input.length() == 32) {

//      if (clearCount > 5) {
//      lmd.clear();
//        clearCount = 0;
//      }
//
//      clearCount++;
lmd.clear();

      for (int i = 0; i < 32; i++) {
        lmd.setPixel(i, String(input[i]).toInt(), s);
//        Serial.println(int(input[i]));  
//        Serial.println(i);  
//        Serial.println(" "); 
      }

      // Flush framebuffer
      lmd.display();
    }

    //done processing? reset the input string
    input = "";
  }
}
