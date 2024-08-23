#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

#define LEDDataPIN 7
#define NUMPIXELS 15
#define DELAYVAL 500  // Time (in milliseconds) to pause between pixels

Adafruit_NeoPixel pixels(NUMPIXELS, LEDDataPIN, NEO_GRB + NEO_KHZ800);

int redValue = 0;
int greenValue = 150;
int blueValue = 0;

String pattern = "all";

void setup() {
  Serial.begin(9600);  // Default communication rate of the Bluetooth module
  pixels.begin();      // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  if (Serial.available() > 0) {  // Checks whether data is comming from the serial port
    // Serial.setTimeout(1000);
    String command = Serial.readStringUntil('\n');
    // Serial.println(command);  // Reads the data from the serial port
    // Check the received command and update the LED color accordingly
    command.trim();

    // Change Collor
    if (command.length() == 9) {
      // Serial.println(command);
      // Extract the RGB values from the command
      redValue = command.substring(0, 3).toInt();
      greenValue = command.substring(3, 6).toInt();
      blueValue = command.substring(6, 9).toInt();
      drawPattern();
    }

    // Change patter
    if (command.length() == 5) {
      String temPattern = command.substring(0, 3);
      String state = command.substring(4, 5);
      if (state == "1") {
        pattern = "all";
        delay(100);
        drawPattern();
        pattern = temPattern;
      } else if (temPattern == pattern) {
        pattern = "all";
      }
    }
  }
  drawPattern();
}

// all light on
void drawPattern() {
  pixels.clear();
  // knight rider
  if (pattern == "knr") {
    // Sweep from left to right
    for (int i = 0; i < NUMPIXELS; i++) {
      // Turn off all pixels
      pixels.clear();
      // Set the current pixel to green (or any color of your choice)
      pixels.setPixelColor(i, pixels.Color(greenValue, redValue, blueValue));  // Green color

      // Show the updated colors
      pixels.show();

      // Wait for a bit
      delay(100);
    }

    // Sweep from right to left
    for (int i = NUMPIXELS - 1; i >= 0; i--) {
      // Turn off all pixels
      pixels.clear();
      // Set the current pixel to green (or any color of your choice)
      pixels.setPixelColor(i, pixels.Color(greenValue, redValue, blueValue));  // Green color

      // Show the updated colors
      pixels.show();

      // Wait for a bit
      delay(100);
    }
  } else {                                 // All
    for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

      pixels.setPixelColor(i, pixels.Color(greenValue, redValue, blueValue));

      pixels.show();  // Send the updated pixel colors to the hardware.
    }
  }



  // Serial.println(redValue);  // Reads the data from the serial port
}
