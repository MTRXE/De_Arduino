/*    
 *     Bette.Mathys
 *     Dé3_V1
 *     
 *     Systéme de dé, avec un bp quand il est appuyé mets une face aléatoire
 *     sur la bande néopixel
 *     
 *     Bande néopixel, Boutton Poussoir, Carte Arduino
 *     Néopixel: D6, BP: D2
 *     
 *     19/09/2024 Dé1_V1: Appuie BP, afficher une face aléatoire du dé
 *     20/09/2024 Dé1_V2: Appuie BP, afficher une face aléatoire du dé
 *     20/09/2024 Dé2_V1: Appuie BP, faire defiler les faces aléatoirement 
 *     et arrete aléatoire
 *     20/09/2024 Dé3_V1: Appuie BP, faire defiler les faces aléatoirement 
 *     et ralentit petit à petit et s'arrete sur une face rdm
 *     
 *    
 */


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Nécessaire pour le Trinket 16 MHz
#endif

// Pin où les NeoPixels sont connectés
#define PIN        6 

// Nombre de pixels sur l'anneau NeoPixel
#define NUMPIXELS 9 

// Initialisation de la bibliothèque NeoPixel avec les paramètres : nombre de pixels, pin de contrôle et protocole
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Délai entre l'affichage des pixels (en millisecondes)

// Pin du bouton poussoir
const int BP = 2; 
byte etatBP = 0; // État actuel du bouton
bool boutonPresse = false; // Indique si le bouton a été pressé

long randNumber = 0; // Stocke la face aléatoire du dé

// Fonction pour faire défiler les faces du dé avec un ralentissement progressif
void Defil() {
  int vitesseInitiale = 50;  // Vitesse initiale du défilement (en ms)
  int ralentissement = 30;    // Augmentation progressive du délai
  int tempsDefil = random(1000, 3000); // Durée du défilement (entre 1 et 3 secondes)

  unsigned long startTime = millis();  // Stocke l'heure de début du défilement

  while (millis() - startTime < tempsDefil) { // Continue le défilement jusqu'à ce que le temps soit écoulé
    randNumber = random(1, 7);  // Choisit une face du dé aléatoire

    // Affiche la face correspondante
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

    delay(vitesseInitiale);  // Délai avant de changer de face

    // Ralentit progressivement
    vitesseInitiale += ralentissement;
  }
}

// Fonction pour détecter si le bouton est pressé
void rdm() {
  etatBP = digitalRead(BP); // Lire l'état du bouton
  
  // Si le bouton est pressé et qu'il ne l'était pas avant
  if (etatBP == HIGH && !boutonPresse) {
    boutonPresse = true;  // Verrouiller pour éviter plusieurs détections
    Defil();  // Lancer le défilement du dé
    boutonPresse = false; // Réinitialiser l'état après le défilement
  }
}

// Fonctions pour afficher les différentes faces du dé

void Face1() { 
  pixels.clear(); // Efface les pixels avant d'afficher une nouvelle face
  Serial.println("Face 1");
  pixels.setPixelColor(4, pixels.Color(100, 0, 0)); // Allume le pixel du milieu (face 1)
  pixels.show(); // Met à jour les LEDs
}

void Face2() { 
  pixels.clear();
  Serial.println("Face 2");
  pixels.setPixelColor(0, pixels.Color(100, 0, 0)); // Allume deux pixels (face 2)
  pixels.setPixelColor(8, pixels.Color(100, 0, 0));
  pixels.show();
}

void Face3() { 
  pixels.clear();
  Serial.println("Face 3");
  pixels.setPixelColor(0, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(4, pixels.Color(100, 0, 0)); // Trois pixels (face 3)
  pixels.setPixelColor(8, pixels.Color(100, 0, 0));
  pixels.show();
}

void Face4() { 
  pixels.clear();
  Serial.println("Face 4");
  pixels.setPixelColor(0, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(2, pixels.Color(100, 0, 0)); // Quatre pixels (face 4)
  pixels.setPixelColor(6, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(8, pixels.Color(100, 0, 0));
  pixels.show();
}

void Face5() { 
  pixels.clear();
  Serial.println("Face 5");
  pixels.setPixelColor(0, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(2, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(4, pixels.Color(100, 0, 0)); // Cinq pixels (face 5)
  pixels.setPixelColor(6, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(8, pixels.Color(100, 0, 0));
  pixels.show();
}

void Face6() { 
  pixels.clear();
  Serial.println("Face 6");
  pixels.setPixelColor(0, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(1, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(2, pixels.Color(100, 0, 0)); // Six pixels (face 6)
  pixels.setPixelColor(6, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(7, pixels.Color(100, 0, 0)); 
  pixels.setPixelColor(8, pixels.Color(100, 0, 0));
  pixels.show();
}

void setup() {
  Serial.begin(9600); // Démarrer la communication série pour debug
  pinMode(BP, INPUT); // Initialiser le bouton en entrée
  pixels.begin(); // Initialisation de la bande de pixels NeoPixel
}

void loop() {
  rdm();  // Vérifie l'état du bouton et lance le dé si nécessaire

  // Affiche la dernière face obtenue après le défilement
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
}
