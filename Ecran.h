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
    Ecran();

    //Design oriented
    void begin();

    void ecrire(char *str, int textSize = 1);
    void dessinerPixel(int16_t, int16_t);
    void effacer();

private:
    void writeFromBeginning(char *str);
};
#endif
