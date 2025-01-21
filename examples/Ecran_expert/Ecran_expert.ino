/*
  Librairie TPG Ecran - Ecran_expert.ino

  ### Démonstration des quelques fonctions avancées pour la classe Ecran.
  Pour plus d'informations, consultez la documentation de la librairie Adafruit GFX : https://learn.adafruit.com/adafruit-gfx-graphics-library

*/
#include "Ecran.h"


Ecran monEcran(128, 64, &Wire, -1 ); //Création de l'objet 'ecran' de classe Ecran avec les paramètres pour Adadruit_SSD1306.

unsigned long next_event;

void setup()
{
    monEcran.setSplashVisible(true); //Affichera l'écran de démarrage (splash screen) pendant 2 secondes.
    monEcran.begin(0x02,0x3c);                // Initialiser l'écran en avec les paramètres pour Adadruit_SSD1306.
    next_event = 0;
}

void loop()
{

    monEcran.refresh(); //Permet d'actualiser l'état de l'écran. Effectue également l'appel à la méthode primitive display()
    // CETTE MÉTHODE EST OBLIGATOIRE EN DÉBUT DE LOOP(), IDÉALEMENT.

    if (millis() > next_event)
    {
        next_event = millis() + 500 + (unsigned long)(random(1000)); //Le prochain évènement aura lieu entre 500 et 1500 ms plus tard.

        int x1 = random(monEcran.width());  //Générer une valeur aléatoire située entre 0 et la largeur de l'écran.
        int y1 = random(monEcran.height()); //Générer une valeur aléatoire située entre 0 et la hauteur de l'écran.

        int x2 = random(monEcran.width());  //Générer une valeur aléatoire située entre 0 et la largeur de l'écran.
        int y2 = random(monEcran.height()); //Générer une valeur aléatoire située entre 0 et la hauteur de l'écran.

        int rnd = random(4); //Piger une tâche au hasard
        if (rnd < 1)
        {

            //Méthodes primitives de la librairie Adafruit GFX.
            monEcran.drawLine(x1, y1, x2, y2, WHITE); //Tracer une ligne
        }
        else if (rnd < 2)
        {
            //Méthodes primitives de la librairie Adafruit GFX.
            monEcran.drawCircle(x1, y1, 6, WHITE); //Tracer un cercle
            monEcran.fillCircle(x2, y2, 4, WHITE); //Tracer un cercle plein
        }
        else if (rnd < 3)
        {

            //Méthodes primitives de la librairie Adafruit GFX.
            monEcran.drawRect(x1, y1, 5, 10, WHITE); //Tracer un rectangle
            monEcran.fillRect(x2, y2, 12, 4, WHITE); //Tracer un plein
        }
        else
        {

            //Méthodes primitives de la librairie Adafruit GFX.
            monEcran.setCursor(x1, y1); //Positionner le curseur
            monEcran.print("tic");      //Écrire le texte

            monEcran.setCursor(x2, y2); //Positionner le curseur
            monEcran.print("TOC");      //Écrire le texte
        }
    }
}