#include <Adafruit_NeoPixel.h>

#define LED_PIN_1       7         // Pin pentru prima bandă LED
#define LED_PIN_2       8         // Pin pentru a doua bandă LED
#define LED_PIN_3       9         // Pin pentru a treia bandă LED
#define LED_COUNT       34        // Numărul total de LED-uri pe fiecare bandă
#define BRIGHTNESS_LOW  100       // Luminozitatea normală (mică)
#define BRIGHTNESS_HIGH 170       // Luminozitatea ridicată
#define DELAY_TIME      50        // Delay între aprinderea fiecărui LED (ms)

Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN_3, NEO_GRB + NEO_KHZ800);

void setup() {
  strip1.begin();
  strip2.begin();
  strip3.begin();
  
  strip1.setBrightness(BRIGHTNESS_LOW); // Setează luminozitatea inițială
  strip2.setBrightness(BRIGHTNESS_LOW);
  strip3.setBrightness(BRIGHTNESS_LOW);

  strip1.show(); // Stinge toate LED-urile inițial
  strip2.show();
  strip3.show();
}

void loop() {
  // Secvență de culori pentru ambele benzi
  lightUpAndHoldColor(0, 0, 255); // Albastru
  lightUpAndHoldColor(255, 255, 0); // Galben
  lightUpAndHoldColor(255, 0, 0); // Roșu
}

// Funcție pentru secvența de aprindere LED-uri fără a stinge cele din față
void lightUpAndHoldColor(uint8_t red, uint8_t green, uint8_t blue) {
  // Aprinde LED-urile secvențial pentru toate benziile
  for (int i = 0; i < LED_COUNT; i++) {
    strip1.setPixelColor(i, strip1.Color(red, green, blue)); // Prima bandă
    strip2.setPixelColor(i, strip2.Color(red, green, blue)); // A doua bandă
    strip3.setPixelColor(i, strip3.Color(red, green, blue)); // A treia bandă
    
    strip1.show();
    strip2.show();
    strip3.show();
    delay(DELAY_TIME); // Așteaptă un timp scurt înainte de următorul LED
  }

  // Crește luminozitatea pentru toate LED-urile temporar
  strip1.setBrightness(BRIGHTNESS_HIGH);
  strip2.setBrightness(BRIGHTNESS_HIGH);
  strip3.setBrightness(BRIGHTNESS_HIGH);
  strip1.show();
  strip2.show();
  strip3.show();
  delay(2000); // Așteaptă 2 secunde cu luminozitate ridicată

  // Revine la luminozitatea inițială
  strip1.setBrightness(BRIGHTNESS_LOW);
  strip2.setBrightness(BRIGHTNESS_LOW);
  strip3.setBrightness(BRIGHTNESS_LOW);
  strip1.show();
  strip2.show();
  strip3.show();

  delay(1000); // Pauză înainte de următoarea secvență
}
