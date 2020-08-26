/*
  Librairie TPG Ecran - Ecran_simple.ino

  ### Démonstration des quelques fonctions simplifiée pour la classe Ecran.


  Note: Toutes les méthodes primitives de la classe Adafruit_SSD1306 sont disponibles dans la classe Ecran également.

*/
#include "Ecran.h"

Ecran monEcran; //Création de l'objet 'ecran' de classe Ecran.
void setup()
{
    Serial.begin(115200);

    monEcran.begin(); // Initialiser l'écran.
}

void loop()
{
    monEcran.ecrire("Bonjour!"); //Écrire un texte dans l'écran.
    delay(1000);

    monEcran.ecrire("Comment allez-vous?", 2); //Écrire un texte dans l'écran, avec une taille de texte de 2.
    delay(1000);

    monEcran.ecrire("Moi,\n bien.", 3); //Écrire un texte dans l'écran, avec une taille de texte de 3.
    delay(1000);

    monEcran.effacer(); //Effacer tout l'écran
    delay(2000);

    monEcran.ecrire(" BOU!", 4); //Écrire un texte dans l'écran, avec une taille de texte de 4.
    delay(1000);

    for (int i = 0; i < 500; i++) //Boucle de 500 itérations:
    {
        int x = random(monEcran.width());  //Générer une valeur aléatoire située entre 0 et la largeur de l'écran.
        int y = random(monEcran.height()); //Générer une valeur aléatoire située entre 0 et la hauteur de l'écran.

        monEcran.dessinerPixel(x, y); //Afficher un pixel blanc à la coordonnée (x,y).
    }
}