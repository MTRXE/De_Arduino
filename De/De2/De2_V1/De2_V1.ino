/*    
 *     Bette.Mathys
 *     Dé1_V2
 *     
 *     Systéme de dé, avec un bp quand il est appuyé mets une face aléatoire
 *     sur la bande néopixel
 *     
 *     Bande néopixel, Boutton Poussoir, Carte Arduino
 *     Néopixel: I2C, BP: D2
 *     
 *     19/09/2024 Dé1_V1: Appuie BP, afficher une face aléatoire du dé
 *     20/09/2024 Dé1_V2: Appuie BP, afficher une face aléatoire du dé
 *     20/09/2024 Dé2_V1: Appuie BP, faire defiler les faces aléatoirement 
 *     et arrete aléatoire
 *    
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define PIN        6 // La pin utilisée pour contrôler les NeoPixels
#define NUMPIXELS 9  // Nombre total de pixels sur l'anneau

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Temps entre chaque affichage de pixel

const int BP = 2; // La pin pour le bouton
byte etatBP = 0;
bool boutonPresse = false; // Vérifie si le bouton a déjà été pressé

long randNumber = 0; // Stocke le numéro aléatoire du dé

// Fonction pour faire défiler les faces du dé avec un ralentissement progressif
void Defil() {
  int vitesseInitiale = 50;  // Vitesse de départ du défilement (en ms)
  int tempsDefil = random(1000, 5000); // Temps de défilement aléatoire entre 1 et 5 secondes

  unsigned long startTime = millis();  // Obtenir le temps de départ

  // Défilement tant que la durée de défilement n'est pas atteinte
  while (millis() - startTime < tempsDefil) {
    randNumber = random(1, 7);  // Générer un nombre entre 1 et 6 pour simuler le lancer du dé

    // Affiche la face du dé correspondante
    if (randNumber == 1) {
      Face1();
    } else if (randNumber == 2) {
      Face2();
    } else if (randNumber == 3) {
      Face3();
    } else if (randNumber == 4) {
      Face4();
    } else if (randNumber == 5) {
      Face5();
    } else if (randNumber == 6) {
      Face6();
    }

    delay(vitesseInitiale);  // Pause entre chaque changement de face

    // Ici, tu pourrais ajouter une augmentation de la pause pour ralentir progressivement le défilement
  }
}

void rdm() {
  etatBP = digitalRead(BP);  // Lire l'état du bouton
  
  if (etatBP == HIGH && !boutonPresse) {  // Si le bouton est pressé et qu'il n'était pas déjà enfoncé
    boutonPresse = true;  // Verrouiller pour ne pas répéter
    Defil();  // Appeler la fonction qui fait défiler les faces du dé
    boutonPresse = false; // Réinitialiser l'état du bouton après le défilement
  }
}

// Fonction pour afficher le chiffre 1 sur les NeoPixels
void Face1() {
  pixels.clear();
  Serial.println("Face 1");
  pixels.setPixelColor(4, pixels.Color(0, 100, 0)); // Allumer le pixel du centre
  pixels.show();
  delay(300);
  randNumber = 0; // Réinitialiser après l'affichage
}

// Fonction pour afficher le chiffre 2 sur les NeoPixels
void Face2() {
  pixels.clear();
  Serial.println("Face 2");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Deux pixels opposés allumés
  pixels.setPixelColor(8, pixels.Color(0, 100, 0));
  pixels.show();
  delay(300);
  randNumber = 0;
}

// Fonction pour afficher le chiffre 3 sur les NeoPixels
void Face3() {
  pixels.clear();
  Serial.println("Face 3");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Trois pixels allumés
  pixels.setPixelColor(4, pixels.Color(0, 100, 0));
  pixels.setPixelColor(8, pixels.Color(0, 100, 0));
  pixels.show();
  delay(300);
  randNumber = 0;
}

// Fonction pour afficher le chiffre 4 sur les NeoPixels
void Face4() {
  pixels.clear();
  Serial.println("Face 4");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Quatre pixels allumés aux coins
  pixels.setPixelColor(2, pixels.Color(0, 100, 0));
  pixels.setPixelColor(6, pixels.Color(0, 100, 0));
  pixels.setPixelColor(8, pixels.Color(0, 100, 0));
  pixels.show();
  delay(300);
  randNumber = 0;
}

// Fonction pour afficher le chiffre 5 sur les NeoPixels
void Face5() {
  pixels.clear();
  Serial.println("Face 5");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Cinq pixels, comme un dé classique
  pixels.setPixelColor(2, pixels.Color(0, 100, 0));
  pixels.setPixelColor(4, pixels.Color(0, 100, 0));
  pixels.setPixelColor(6, pixels.Color(0, 100, 0));
  pixels.setPixelColor(8, pixels.Color(0, 100, 0));
  pixels.show();
  delay(300);
  randNumber = 0;
}

// Fonction pour afficher le chiffre 6 sur les NeoPixels
void Face6() {
  pixels.clear();
  Serial.println("Face 6");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Six pixels allumés en deux colonnes
  pixels.setPixelColor(1, pixels.Color(0, 100, 0));
  pixels.setPixelColor(2, pixels.Color(0, 100, 0));
  pixels.setPixelColor(6, pixels.Color(0, 100, 0));
  pixels.setPixelColor(7, pixels.Color(0, 100, 0));
  pixels.setPixelColor(8, pixels.Color(0, 100, 0));
  pixels.show();
  delay(300);
  randNumber = 0;
}

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  
  Serial.begin(9600); // Initialiser la communication série
  pinMode(BP, INPUT); // Configurer la pin du bouton comme entrée

  pixels.begin(); // Initialiser les NeoPixels
}

void loop() {
  rdm(); // Vérifier si le bouton est pressé et lancer le dé si c'est le cas
}
