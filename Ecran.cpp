#include "Ecran.h"

Ecran::Ecran(int8_t reset_pin) : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, reset_pin)
{
  _splashVisible = false;
  _changeFlag = false;
}

void Ecran::begin(uint8_t switchVCC, uint8_t i2cAddress)
{
  if (!Adafruit_SSD1306::begin(switchVCC, i2cAddress))
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
    setTextColor(WHITE);
  }
}

void Ecran::refresh()
{
  if (_changeFlag)
  {
    _changeFlag = false;
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
void Ecran::ecrire(char *msg, int line, int textSize)
{
  setTextSize(textSize);
  if (line >= 0 && line < 8)
  {
    writeFromBeginning(msg, line);
  }
}

void Ecran::dessinerPixel(int16_t x, int16_t y)
{
  drawPixel(x, y, SSD1306_WHITE);
  flag();
}

void Ecran::effacer()
{
  clearDisplay();
  flag();
}

void Ecran::writeFromBeginning(char *msg, int line)
{
  String buffer = msg;
  setTextColor(WHITE, BLACK);
  setCursor(0, 8 * line);
  print(buffer);
  flag();
}

void Ecran::flag()
{
  _changeFlag = true;
}

//Overriden method
void Ecran::endWrite()
{
  Adafruit_SSD1306::endWrite();
  _changeFlag = true;
}
