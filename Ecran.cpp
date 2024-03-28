#include "Ecran.h"

Ecran::Ecran(int8_t reset_pin, TwoWire *wire, uint8_t i2cAddress) : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, wire, reset_pin)
{
  _splashVisible = false;
  _changeFlag = false;
  _utf8 = 0;
  _utf8_error = false;
  _unicode = 0;
  _wrapLine = false;
  _i2cAddress = i2cAddress;
}

bool Ecran::begin()
{
  if (!Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, _i2cAddress))
  {
    return false;
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
    setTextColor(WHITE, BLACK);
  }
  return true;
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

void Ecran::setWrapLine(bool value)
{
  _wrapLine = value;
}
bool Ecran::getWrapLine()
{
  return _wrapLine;
}

void Ecran::wrapLine()
{
  if (_wrapLine)
  {
    Adafruit_SSD1306::setCursor(Adafruit_SSD1306::getCursorX(), Adafruit_SSD1306::getCursorY() % Adafruit_SSD1306::height());
  }
}

size_t Ecran::write(uint8_t c)
{
  if (_utf8 > 0)
  {
    _utf8--;
    if (!_utf8_error)
    {
      _unicode = (_unicode << 6) + (c & 63);
    }
    if (_utf8 == 0)
    {

      Ecran::wrapLine();
      size_t answer = Adafruit_SSD1306::write(mapUnicodeToExtASCII(_unicode));
      _unicode = 0;
      return answer;
    }
  }
  else if (c >> 3 == 30) // 4 bits utf-8
  {
    _utf8 = 3;
    _unicode = c & 7;
  }
  else if (c >> 4 == 14) // 3 bits utf-8
  {

    _utf8 = 2;
    _unicode = c & 15;
  }
  else if (c >> 5 == 6) // 2 bits utf-8
  {
    _utf8 = 1;
    _unicode = c & 31;
  }
  else
  {
    Ecran::wrapLine();
    return Adafruit_SSD1306::write(c);
  }
  return 1;
}

uint8_t Ecran::mapUnicodeToExtASCII(unsigned int unicode)
{
  static unsigned int mapping[] = {
      199,
      252,
      233,
      226,
      228,
      224,
      229,
      231,
      234,
      235,
      232,
      239,
      238,
      236,
      196,
      197,
      201,
      230,
      198,
      244,
      246,
      242,
      251,
      249,
      255,
      214,
      220,
      162,
      163,
      165,
      8359,
      402,
      225,
      237,
      243,
      250,
      241,
      209,
      170,
      186,
      191,
      8976,
      172,
      189,
      188,
      161,
      171,
      187,
      9617,
      9618,
      9619,
      9474,
      9508,
      9569,
      9570,
      9558,
      9557,
      9571,
      9553,
      9559,
      9565,
      9564,
      9563,
      9488,
      9492,
      9524,
      9516,
      9500,
      9472,
      9532,
      9566,
      9567,
      9562,
      9556,
      9577,
      9574,
      9568,
      9552,
      9580,
      9575,
      9576,
      9572,
      9573,
      9561,
      9560,
      9554,
      9555,
      9579,
      9578,
      9496,
      9484,
      9608,
      9604,
      9612,
      9616,
      9600,
      945,
      223,
      915,
      960,
      931,
      963,
      181,
      964,
      934,
      920,
      937,
      948,
      8734,
      966,
      949,
      8745,
      8801,
      177,
      8805,
      8804,
      8992,
      8993,
      247,
      8776,
      176,
      8729,
      183,
      8730,
      8319,
      178,
      9632,
      160};
  for (uint8_t i = 0; i < 128; i++)
  {
    if (mapping[i] == unicode)
    {
      return i + 128;
    }
  }
  return 0;
}

void Ecran::ecrire(const char *msg, int line, int textSize)
{
  setTextSize(textSize);
  if (line >= 0 && line < (SCREEN_HEIGHT / 8))
  {
    writeFromBeginning(msg, line);
  }
}
void Ecran::ecrire(String msg, int line, int textSize)
{
  setTextSize(textSize);
  if (line >= 0 && line < (SCREEN_HEIGHT / 8))
  {
    writeFromBeginning(msg, line);
  }
}

void Ecran::dessinerPixel(int16_t x, int16_t y)
{
  drawPixel(x, y, SSD1306_WHITE);
  flag();
}

void Ecran::effacer(int line, int textSize)

{
  if (line < 0)
  {
    clearDisplay();
    flag();
  }
  else
  {

    if (line < (SCREEN_HEIGHT / 8))
    {
      fillRect(0, line * 8, SCREEN_WIDTH, 8 * textSize, BLACK);
    }
  }
}

void Ecran::writeFromBeginning(const char *msg, int line)
{
  String buffer = msg;
  setTextColor(WHITE, BLACK);
  setCursor(0, 8 * line);
  print(buffer);
  flag();
}
void Ecran::writeFromBeginning(String buffer, int line)
{
  setTextColor(WHITE, BLACK);
  setCursor(0, 8 * line);
  print(buffer);
  flag();
}
void Ecran::flag()
{
  _changeFlag = true;
}

// Overriden method
void Ecran::endWrite()
{
  Adafruit_SSD1306::endWrite();
  _changeFlag = true;
}
