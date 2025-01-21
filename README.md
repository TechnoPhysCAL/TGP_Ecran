# Librairie TGP

Permet l'utilisation d'un écran OLED, construite sur la librairie [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306).

## Détails

L'écran offre quelques méthodes simplifiées pour afficher du texte à l'écran. Pour davantage de possibilités graphiques, elle expose également les méthodes primitives déjà présentes dans la librairie Adafruit GFX.

## Notes de version

### 2.0.0 : 
 - Numéro de version en phase avec le reste des librairies TGP
 - Meilleur commentaires dans les exemples

### 1.3.1 :
- correction pour une instruction non rejoignable après un return.
 
### 1.3.0 :
- Ajout de setWrapLine(bool) et getWrapLine(), pour permettre le retour automatique à la première ligne lorsque le texte déborde par le bas.
 
### 1.2.1 :
- Retiré des Serial.print() temporaires pour débogage.

### 1.2.0 : 
- Les chaînes codées UTF-8 par Arduino sont maintenant décodées: si le caractère Unicode existe dans l'ASCII étendue, il sera correctement affiché;
- La méthode effacer() permet maintenant d'effacer une seule ligne de taille voulue, à l'image de la méthode écrire();
- Les exemples ont été modifiées en conséquence.

### 1.1.0 :
- Support des String et const char* dans la méthode ecrire().

### 1.0.0 :
- Première version officielle.


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
void setSplashVisible(bool value)
bool getSplashVisible()
```
Permet de lire et écrire l'apparition ou non de l'écran de démarrage (splash screen) au moment du lancement de l'écran. Cette méthode doit être appelée AVANT l'appel de la méthode begin(). L'image affichée ne peut pas être changée: il est mise en mémoire par la librairie Adafruit GFX.

--- 
```cpp
void begin()
void begin(uint8_t switchVCC, uint8_t i2cAddress )
```
Doit être appelée dans la fonction setup(). Initialise l'écran, on peut facultativement préciser les valeurs de switchVCC et i2cAddress (voir documentation Adafruit SSD1306).

---
```cpp
 void refresh()
```
Cette méthode doit être placée en début de boucle loop(): elle permet de mettre à jour l'état de l'écran sans bloquer l'exécution du reste de la boucle.

---
```cpp
void ecrire(char *str)
void ecrire(char *str, int line)
void ecrire(char *str, int line, int textSize)

```
Permet d'afficher une chaîne de texte à l'écran, à ligne voulue (0 à 7, par défault 0) et de taille voulue (facteur entier entre 1 et 4, par défaut 1). Les deux derniers paramètres sont facultatifs.

--- 
```cpp
void dessinerPixel(int16_t x, int16_t y)

```
Permet de dessiner un seul pixel à la coordonnée (x,y).

--- 
```cpp
void effacer()
void effacer(int line)
void effacer(int line, int textSize)

```
Permet d'effacer l'écran tout l'écran (si aucun paramètre n'est fourni), ou seulement une ligne spécifique (0 à 7, ou -1 pour effacer tout l'écran) et de taille spécifique (facteur entier, par défaut 1).

---
```cpp
void setWrapLine(bool value)
bool getWrapLine()
```
Permet de lire et écrire le retour (ou le non-retour) automatique à la première ligne lorsque le texte déborde de l'écran par le bas.

### Remarque

Toutes les méthodes primitives déjà présentes dans la librairie Adafruit GFX sont disponibles.