#include <LEDMatrixDriver.hpp>

// Define the ChipSelect pin for the led matrix (Dont use the SS or MISO pin of your Arduino!)
// Other pins are Arduino specific SPI pins (MOSI=DIN, SCK=CLK of the LEDMatrix) see https://www.arduino.cc/en/Reference/SPI
const uint8_t LEDMATRIX_CS_PIN = 9;

// Number of 8x8 segments you are connecting
const int LEDMATRIX_SEGMENTS = 4;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;

// The LEDMatrixDriver class instance
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);

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

bool fill, upsideDown, controlGlow = false;

void loop() {

  if (getInput()) {

    // Serial.print("I received: ");
    // Serial.println(input);

    if (input.toInt() == 0) {
      lmd.clear();
    }

    if (input.length() == 2) {
      if (input == "f1") fill = true;
      if (input == "f0") fill = false;
      if (input == "u1") upsideDown = true;
      if (input == "u0") upsideDown = false;
      if (input == "c1") controlGlow = true;
      if (input == "c0") controlGlow = false;
    }

    if (input.length() == 32) {

      lmd.clear();

      for (int i = 0; i < 32; i++) {

        if (fill && upsideDown) {
          for (int f = String(input[i]).toInt(); f < 8; f++) {
            lmd.setPixel(i, f, s);
          }
        } else if (fill && !upsideDown) {
          for (int f = String(input[i]).toInt(); f >= 0; f--) {
            lmd.setPixel(i, f, s);
          }
        } else if (!fill) {
          lmd.setPixel(i, String(input[i]).toInt(), s);
        }

      }

      // Flush framebuffer
      lmd.display();
    }

    // done processing? reset the input string
    input = "";
  }
}
