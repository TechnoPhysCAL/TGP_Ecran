#ifndef Ecran_h
#define Ecran_h

#include "Arduino.h"
#include "Adafruit_SSD1306.h" //Pour l'affichage OLED
#include <SPI.h>
#include <Wire.h> //Pour l'affichage OLED

// Les paramètres par défaut correspondent au à l'écran OLED 128x64 tel que branché sur la plateforme ProtoTPhys.
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    //Si pas nécessaire, il faut alors mettre <= 0
#define SWITCH_VCC SSD1306_SWITCHCAPVCC //Switch to VCC par défaut
#define DEFAULT_ADDRESS 0x3C //Adresse I2C par défaut

/******************************************************************************
* Definitions
******************************************************************************/
class Ecran : public Adafruit_SSD1306
{
public:
    Ecran(uint8_t width=SCREEN_WIDTH, uint8_t height=SCREEN_HEIGHT,TwoWire *twoWire=&Wire,int8_t resetPin=OLED_RESET );
    void begin(uint8_t switchVCC = SWITCH_VCC, uint8_t i2cAddress = DEFAULT_ADDRESS);
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
