# Librairie TGP

Permet l'utilisation d'un écran OLED, construite sur la librairie [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306).

## Détails

L'écran offre quelques méthodes simplifiées pour afficher du texte à l'écran. Pour davantage de possibilités graphiques, elle expose également les méthodes primitives déjà présentes dans la librairie Adafruit GFX.

## Utilisation


La classe peut s'utiliser de manière non-bloquante: 
```cpp
#include "Ecran.h"

Ecran monEcran;

void setup() {
  monEcran.begin();
}

void loop() {
  monEcran.refresh(); //La méthode s'occupe d'appeler la méthode primitive display(), lorsque nécessaire  
                      //(quand des éléments graphiques ont été modifiées au cours du loop() ).

  if(millis() % 1000 < 10){ //Condtition temporelle
     monEcran.effacer();               //Effacer l'écran
    
    monEcran.ecrire("Bonjour!");       //Écrire un texte
    monEcran.ecrire("Salut!", 1);      //Écrire un texte sur la 2e ligne
    monEcran.ecrire("Au revoir!",2,3); //Écrire un texte sur la 3e ligne avec une taille de 3

    monEcran.dessinerPixel(10,10);     //Dessiner un pixel à la coordonnée (10,10);
  }
}
```

La classe peut s'utiliser aussi de manière bloquante: 

```cpp
#include "Ecran.h"

Ecran monEcran;

void setup() {
  monEcran.begin();
}

void loop() {

  monEcran.ecrire("Bonjour!");       //Écrire un texte
  monEcran.ecrire("Salut!", 1);      //Écrire un texte sur la 2e ligne
  monEcran.ecrire("Au revoir!",2,3); //Écrire un texte sur la 3e ligne avec une taille de 3
  monEcran.display();
  delay(1000);


  monEcran.dessinerPixel(10,10);     //Dessiner un pixel à la coordonnée (10,10);
  monEcran.display();
  delay(1000);

  monEcran.effacer();
  monEcran.display();
  delay(1000);
}
```

## Constructeurs
```cpp
Ecran()
Ecran(int8_t reset_pin)
```
Au besoin, on peut préciser le numéro de la broche pour le reset (par défault, -1 ).

## Méthodes disponibles

```cpp
void begin()
void begin(uint8_t switchVCC, uint8_t i2cAddress )
```
Initialise l'écran, on peut facultativement préciser les valeurs de switchVCC et i2cAddress (voir documentation Adafruit SSD1306).

---
```cpp
void setSplashVisible(bool)
bool getSplashVisible()
```
Permet de lire et écrire l'apparition ou non de l'écran de démarrage (splash screen) au moment du lancement de l'écran. Cette méthode doit être appelée AVANT l'appel de la méthode begin().

--- 
```cpp
void ecrire(char *str, int line, int textSize)

```
Permet d'afficher une chaîne de texte à l'écran, à ligne voulue (indice 0 à 7) et de taille voulue (minimum de 1). Les deux derniers paramètres sont facultatifs.

--- 
```cpp
void dessinerPixel(int16_t x, int16_t y)

```
Permet de dessiner un seul pixel à la coordonnée (x,y).

--- 
```cpp
void effacer()

```
Permet d'effacer l'écran.

---

### Remarque

Toutes les méthodes primitives déjà présentes dans la librairie Adafruit GFX sont disponibles.