/*    
 *     Bette.Mathys
 *     Dé1_V2
 *     
 *     Systéme de dé, avec un bp quand il est appuyé mets une face aléatoire
 *     sur la bande néopixel
 *     
 *     Bande néopixel, Boutton Poussoir, Carte Arduino
 *     Néopixel: D6, BP: D2
 *     
 *     19/09/2024 Dé1_V1: Appuie BP, afficher une face aléatoire du dé
 *     19/09/2024 Dé1_V2: Appuie BP, afficher une face aléatoire du dé
 *    
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define PIN        6 // Pin pour les LED NeoPixel
#define NUMPIXELS 9  // Nombre de LED sur l'anneau

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Temps de pause entre les pixels

const int BP = 2; // Pin du bouton
byte etatBP = 0;

long randNumber;

void rdm () {
  etatBP = digitalRead(BP); // Lire l'état du bouton
  if (etatBP == HIGH) { // Si le bouton est appuyé
    randNumber = random(1, 7); // Générer un nombre entre 1 et 6
    Serial.println(randNumber); // Afficher le nombre généré
    delay(200); // Petite pause
    return randNumber;
  }
}

void Chiffre1() { // Affichage pour le chiffre 1
  pixels.clear(); // Effacer les pixels
  Serial.println("Face 1"); 
  pixels.setPixelColor(4, pixels.Color(0, 100, 0)); // Allumer le pixel central
  pixels.show(); // Afficher la couleur
  delay(300); // Pause avant de réinitialiser
  randNumber = 0; // Réinitialiser le nombre
}

void Chiffre2() { // Affichage pour le chiffre 2
  pixels.clear();
  Serial.println("Face 2");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Allumer deux pixels opposés
  pixels.setPixelColor(8, pixels.Color(0, 100, 0));
  pixels.show();
  delay(300);
  randNumber = 0;
}

void Chiffre3() { // Affichage pour le chiffre 3
  pixels.clear();
  Serial.println("Face 3");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Allumer trois pixels
  pixels.setPixelColor(4, pixels.Color(0, 100, 0)); 
  pixels.setPixelColor(8, pixels.Color(0, 100, 0));
  pixels.show();
  delay(300);
  randNumber = 0;
}

void Chiffre4() { // Affichage pour le chiffre 4
  pixels.clear();
  Serial.println("Face 4");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Allumer quatre pixels en croix
  pixels.setPixelColor(2, pixels.Color(0, 100, 0));
  pixels.setPixelColor(6, pixels.Color(0, 100, 0));
  pixels.setPixelColor(8, pixels.Color(0, 100, 0));
  pixels.show();
  delay(300);
  randNumber = 0;
}

void Chiffre5() { // Affichage pour le chiffre 5
  pixels.clear();
  Serial.println("Face 5");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Comme un dé, cinq pixels allumés
  pixels.setPixelColor(2, pixels.Color(0, 100, 0));
  pixels.setPixelColor(4, pixels.Color(0, 100, 0));
  pixels.setPixelColor(6, pixels.Color(0, 100, 0));
  pixels.setPixelColor(8, pixels.Color(0, 100, 0));
  pixels.show();
  delay(300);
  randNumber = 0;
}

void Chiffre6() { // Affichage pour le chiffre 6
  pixels.clear();
  Serial.println("Face 6");
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Six pixels allumés sur deux colonnes
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
  pinMode(BP, INPUT); // Configurer le bouton en entrée

  pixels.begin(); // Initialiser les pixels
}

void loop() {
  pixels.clear(); // Effacer les pixels à chaque boucle

  rdm(); // Appeler la fonction pour générer un nombre

  if (randNumber == 1) {
    Chiffre1(); // Si le nombre est 1, afficher 1 sur les LED
  } else if (randNumber == 2) {
    Chiffre2(); // Si c'est 2, afficher 2
  } else if (randNumber == 3) {
    Chiffre3(); // Etc. pour chaque chiffre
  } else if (randNumber == 4) {
    Chiffre4();
  } else if (randNumber == 5) {
    Chiffre5();
  } else if (randNumber == 6) {
    Chiffre6();
  }
}
