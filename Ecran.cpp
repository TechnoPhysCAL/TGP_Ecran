#include "Ecran.h"

Ecran::Ecran() : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
  _splashVisible = false;
}

void Ecran::begin()
{
  if (!Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, DEFAULT_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
  }
  else
  {
    if (getSplashVisible())
    {
      display();
      delay(2000); // Pause for 2 seconds
    }
    // Clear the buffer
    clearDisplay();
    display();
  }
}

void Ecran::setSplashVisible(bool value)
{
  _splashVisible = value;
}
bool Ecran::getSplashVisible()
{
  return _splashVisible;
}
void Ecran::ecrire(char *msg, int textSize)
{
  setTextSize(textSize);
  writeFromBeginning(msg);
}

void Ecran::dessinerPixel(int16_t x, int16_t y)
{
  drawPixel(x, y, SSD1306_WHITE);
  display();
}

void Ecran::effacer()
{
  clearDisplay();
  display();
}

void Ecran::writeFromBeginning(char *msg)
{
  String buffer = msg;
  clearDisplay();
  setTextColor(WHITE);
  setCursor(0, 0);
  print(buffer);
  display();
}