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
    monEcran.display();
    delay(1000);

    monEcran.ecrire("Comment allez-vous?", 1); //Écrire un texte dans l'écran, sur la deuxième ligne.
    monEcran.display();
    delay(1000);

    monEcran.ecrire("Moi,\n bien.", 2, 3); //Écrire un texte dans l'écran,sur la quatrième ligne avec une taille de texte de 3.
    monEcran.display();
    delay(1000);

    monEcran.effacer(); //Effacer tout l'écran
    monEcran.display();
    delay(2000);

    monEcran.ecrire(" BOU!", 0, 4); //Écrire un texte dans l'écran,sur la première ligne avec une taille de texte de 4.
    monEcran.display();
    delay(1000);

    for (int taille = 1; taille <= 4; taille++) //Boucle de 4 itérations:
    {
        for (int ligne = 0; ligne < 8; ligne = ligne + taille)
        {
            monEcran.ecrire("TGP Ecran", ligne, taille); //Ecrire le texte sur une ligne donnée, de la taille donnée.
            monEcran.display();
            delay(200);
        }
        for (int ligne = 0; ligne < 8; ligne = ligne + taille) //Effacer une ligne donnée, de la taille donnée.
        {
            monEcran.effacer(ligne, taille);
            monEcran.display();
            delay(200);
        }
    }

    monEcran.effacer(); //Tout effacer l'écran.

    for (int i = 0; i < 500; i++) //Boucle de 500 itérations:
    {
        int x = random(monEcran.width());  //Générer une valeur aléatoire située entre 0 et la largeur de l'écran.
        int y = random(monEcran.height()); //Générer une valeur aléatoire située entre 0 et la hauteur de l'écran.

        monEcran.dessinerPixel(x, y); //Afficher un pixel blanc à la coordonnée (x,y).
        monEcran.display();
    }
}