#ifndef Ecran_h
#define Ecran_h

#include "Arduino.h"
#include "Adafruit_SSD1306.h" //Pour l'affichage OLED
#include <SPI.h>
#include <Wire.h> //Pour l'affichage OLED

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    //Si pas nécessaire, il faut alors mettre <= 0

#define DEFAULT_ADDRESS 0x3C

/******************************************************************************
* Definitions
******************************************************************************/
class Ecran : public Adafruit_SSD1306
{
public:
    Ecran(int8_t reset_pin = OLED_RESET);
    void begin(uint8_t switchVCC = SSD1306_SWITCHCAPVCC, uint8_t i2cAddress = DEFAULT_ADDRESS);
    void refresh();
    size_t write(uint8_t c);
    void setSplashVisible(bool);
    bool getSplashVisible();

    void setWrapLine(bool);
    bool getWrapLine();

    void ecrire(const char *str, int line = 0, int textSize = 1);
    void ecrire(String str, int line = 0, int textSize = 1);
    void dessinerPixel(int16_t, int16_t);
    void effacer(int line =-1, int textSize = 1);

    //Méthode surchargé provenant de la classe Adafruit GFX, pour flagger le changement d'image.
    void endWrite();

private:
    bool _splashVisible;
    bool _changeFlag;
    bool _wrapLine;
    uint8_t _utf8;
    bool _utf8_error;
    unsigned int _unicode;
    uint8_t mapUnicodeToExtASCII(unsigned int _unicode);
    void flag();
    void writeFromBeginning(const char *str, int line);
    void writeFromBeginning(String str, int line);
    void wrapLine();
};
#endif
