#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

#define LEDDataPIN 7
#define NUMPIXELS 8
#define DELAYVAL 500  // Time (in milliseconds) to pause between pixels

Adafruit_NeoPixel pixels(NUMPIXELS, LEDDataPIN, NEO_GRB + NEO_KHZ800);

int redValue = 246;
int greenValue = 205;
int blueValue = 180;
int brightness = 255;  // Default brightness (0 to 255)

// Define max number of patterns
int pattern = 1;

void setup() {
  Serial.begin(9600);  // Default communication rate of the Bluetooth module
  pixels.begin();      // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  if (Serial.available() > 0) {  // Checks whether data is coming from the serial port
    String command = Serial.readStringUntil('\n');
    command.trim();

    // Change Color
    if (command.length() == 9) {
      // Extract the RGB values from the command
      redValue = command.substring(0, 3).toInt();
      greenValue = command.substring(3, 6).toInt();
      blueValue = command.substring(6, 9).toInt();
    }

    // Change pattern
    if (command.length() == 1 || command.length() == 2) {
      int temPattern = command.toInt();
      if (temPattern) {
        pattern = temPattern;
      }
    }

    // Change Brightness
    if (command.length() == 3) {
      brightness = command.toInt();  // Update brightness
      pixels.setBrightness(brightness);
    }
  }
  drawPatterns();
}


// Function to draw all patterns
void drawPatterns() {
  pixels.setBrightness(brightness);
  // Define patterns
  if (pattern == 1) {
    allOn();
  } else if (pattern == 2) {
    knightRider();
  } else if (pattern == 3) {
    randomPattern();
  } else if (pattern == 4) {  // blink
    blink();
  } else if (pattern == 5) {  // wave
    wave();
  } else if (pattern == 6) {  //theater
    theaterChase();
  } else if (pattern == 7) {  // fade
    fade();
  } else if (pattern == 8) {  // strobe
    strobe();
  } else if (pattern == 9) {  // sweep
    sweep();
  } else if (pattern == 10) {  // colorWipe
    sparkle();
  }
}

// All on pattern
void allOn() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(greenValue, redValue, blueValue));
  }
  pixels.show();
}

// Knight Rider pattern
void knightRider() {
  // Sweep from left to right
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(greenValue, redValue, blueValue));
    pixels.show();
    delay(100);
  }

  

  // Sweep from right to left
  for (int i = NUMPIXELS - 1; i >= 0; i--) {
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(greenValue, redValue, blueValue));
    pixels.show();
    delay(100);
  }
}

// Random pattern
void randomPattern() {
  for (int i = 0; i < NUMPIXELS; i++) {
    // Generate random color values
    int randRed = random(0, 256);
    int randGreen = random(0, 256);
    int randBlue = random(0, 256);
    // Generate random brightness
    int randBrightness = random(0, 256);

    // Set random brightness
    pixels.setBrightness(randBrightness);
    
    // Set pixel color
    pixels.setPixelColor(i, pixels.Color(randGreen, randRed, randBlue));
  }
  pixels.show();
  delay(500);  // Delay to allow viewing of the pattern before it changes
}


// Blink pattern
void blink() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(greenValue, redValue, blueValue));
  }
  pixels.show();
  delay(500);
  pixels.clear();
  pixels.show();
  delay(500);
}

// Wave pattern
void wave() {
  for (int j = 0; j < NUMPIXELS; j++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      int pos = (i + j) % NUMPIXELS;
      pixels.setPixelColor(pos, pixels.Color(greenValue, redValue, blueValue));
    }
    pixels.show();
    delay(100);
    pixels.clear();
  }
}

// Theater Chase pattern
void theaterChase() {
  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      pixels.clear();
      for (int i = 0; i < NUMPIXELS; i += 3) {
        pixels.setPixelColor(i + q, pixels.Color(greenValue, redValue, blueValue));
      }
      pixels.show();
      delay(100);
    }
  }
}

// Fade pattern
void fade() {
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(greenValue * j / 255, redValue * j / 255, blueValue * j / 255));
    }
    pixels.show();
    delay(10);
  }
  for (int j = 255; j >= 0; j--) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(greenValue * j / 255, redValue * j / 255, blueValue * j / 255));
    }
    pixels.show();
    delay(10);
  }
}

// Strobe pattern
void strobe() {
  for (int i = 0; i < 10; i++) {
    pixels.fill(pixels.Color(greenValue, redValue, blueValue));
    pixels.show();
    delay(100);
    pixels.clear();
    pixels.show();
    delay(100);
  }
}

// Sweep pattern
void sweep() {
  for (int j = 0; j < NUMPIXELS * 2; j++) {
    pixels.clear();
    int pos = j % NUMPIXELS;
    pixels.setPixelColor(pos, pixels.Color(greenValue, redValue, blueValue));
    pixels.show();
    delay(100);
  }
}

// Sparkle
void sparkle() {
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    if (random(0, 10) < 2) { // Adjust the probability of sparkles
      int randRed = random(0, 256);
      int randGreen = random(0, 256);
      int randBlue = random(0, 256);
      pixels.setPixelColor(i, pixels.Color(randGreen, randRed, randBlue));
    }
  }
  pixels.show();
  delay(100); // Delay to view the sparkle effect
}
