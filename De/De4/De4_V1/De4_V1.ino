/*    
 *     Bette.Mathys
 *     Dé4_V1
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
 *     23/09/2024 Dé3_V1: Ajout d'effet quand la face 6 tombe
 *     
 *    
 */


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Nécessaire pour les Adafruit Trinket à 16 MHz
#endif

// Définition de la broche où les NeoPixels sont connectés
#define PIN        6       

// Définition du nombre de pixels sur l'anneau NeoPixel
#define NUMPIXELS  9       

// Initialisation de la bande de pixels avec le bon protocole de communication
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Temps de pause entre les pixels en millisecondes
#define DELAYVAL 500       

// Définition de la broche pour le bouton poussoir
const int BP = 2;          

// Variables pour gérer l'état du bouton et le verrouillage de la pression
byte etatBP = 0;            
bool boutonPresse = false;  

// Variable pour stocker la face aléatoire du dé
long randNumber = 0;       

// Fonction pour gérer le défilement avec un ralentissement progressif
void Defil() {
  int vitesseInitiale = 1;           // Vitesse initiale du défilement en millisecondes
  int ralentissement = 50;           // Facteur de ralentissement progressif
  int tempsDefil = random(2500, 3500); // Durée totale du défilement aléatoire (entre 2,5 et 3,5 secondes)

  unsigned long startTime = millis(); // Capturer le temps de départ

  // Défilement aléatoire des faces du dé
  while (millis() - startTime < tempsDefil) {
    randNumber = random(1, 7);  // Sélectionner un numéro de dé aléatoire entre 1 et 6

    // Afficher la face correspondant au numéro tiré en rouge
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

    delay(vitesseInitiale);  // Pause pour chaque changement de face

    // Augmentation progressive du délai pour ralentir le défilement
    vitesseInitiale += ralentissement;
  }

  // Afficher la face finale en vert pour indiquer la fin du défilement
  if (randNumber == 1) {
    Face1();  
    pixels.setPixelColor(4, pixels.Color(0, 100, 0));  // LED centrale verte
  } else if (randNumber == 2) {
    Face2();  
    pixels.setPixelColor(0, pixels.Color(0, 100, 0));  // LED verte en haut à gauche
    pixels.setPixelColor(8, pixels.Color(0, 100, 0));  // LED verte en bas à droite
  } else if (randNumber == 3) {
    Face3();  
    pixels.setPixelColor(0, pixels.Color(0, 100, 0));  
    pixels.setPixelColor(4, pixels.Color(0, 100, 0));  
    pixels.setPixelColor(8, pixels.Color(0, 100, 0));  
  } else if (randNumber == 4) {
    Face4();  
    pixels.setPixelColor(0, pixels.Color(0, 100, 0));  
    pixels.setPixelColor(2, pixels.Color(0, 100, 0));  
    pixels.setPixelColor(6, pixels.Color(0, 100, 0));  
    pixels.setPixelColor(8, pixels.Color(0, 100, 0));  
  } else if (randNumber == 5) {
    Face5();  
    pixels.setPixelColor(0, pixels.Color(0, 100, 0));  
    pixels.setPixelColor(2, pixels.Color(0, 100, 0));  
    pixels.setPixelColor(4, pixels.Color(0, 100, 0));  
    pixels.setPixelColor(6, pixels.Color(0, 100, 0));  
    pixels.setPixelColor(8, pixels.Color(0, 100, 0));  
  } else if (randNumber == 6) {
    RGBAnimation();  // Animation colorée pour la face 6
  }

  pixels.show();  // Mettre à jour les pixels pour afficher les modifications
}

// Fonction pour gérer la pression du bouton et lancer le dé
void rdm() {
  etatBP = digitalRead(BP);
  
  while (etatBP == HIGH && !boutonPresse) {  // Si le bouton est pressé
    boutonPresse = true;  // Verrouiller pour éviter plusieurs pressions consécutives
    Defil();              // Lancer le dé
    boutonPresse = false; // Réinitialiser l'état du bouton après l'action
    break;
  }
}

// Fonctions pour afficher chaque face du dé
void Face1() { 
  pixels.clear();
  pixels.setPixelColor(4, pixels.Color(100, 0, 0)); // LED centrale rouge
  pixels.show();
}

void Face2() { 
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(100, 0, 0)); // Haut gauche
  pixels.setPixelColor(8, pixels.Color(100, 0, 0)); // Bas droite
  pixels.show();
}

void Face3() { 
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(4, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(8, pixels.Color(100, 0, 0));  
  pixels.show();
}

void Face4() { 
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(2, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(6, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(8, pixels.Color(100, 0, 0));  
  pixels.show();
}

void Face5() { 
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(2, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(4, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(6, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(8, pixels.Color(100, 0, 0));  
  pixels.show();
}

void Face6() { 
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(1, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(2, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(6, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(7, pixels.Color(100, 0, 0));  
  pixels.setPixelColor(8, pixels.Color(100, 0, 0));  
  pixels.show();
}

// Animation RGB pour la face 6
void RGBAnimation() {
  for (int i = 0; i < 10; i++) { // 10 cycles de changement de couleurs
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Rouge
    pixels.setPixelColor(1, pixels.Color(0, 255, 0)); // Vert
    pixels.setPixelColor(2, pixels.Color(0, 0, 255)); // Bleu
    pixels.setPixelColor(6, pixels.Color(255, 0, 0)); // Rouge
    pixels.setPixelColor(7, pixels.Color(0, 255, 0)); // Vert
    pixels.setPixelColor(8, pixels.Color(0, 0, 255)); // Bleu
    pixels.show();
    delay(250);

    pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // Inverser les couleurs
    pixels.setPixelColor(1, pixels.Color(255, 0, 0)); 
    pixels.setPixelColor(2, pixels.Color(0, 255, 0)); 
    pixels.setPixelColor(6, pixels.Color(0, 0, 255)); 
    pixels.setPixelColor(7, pixels.Color(255, 0, 0)); 
    pixels.setPixelColor(8, pixels.Color(0, 255, 0)); 
    pixels.show();
    delay(250); 
  }
}

// Fonction setup pour initialiser le programme
void setup() {
  Serial.begin(9600);  // Initialiser la communication série
  pinMode(BP, INPUT);  // Définir la broche du bouton comme entrée
  pixels.begin();      // Initialiser l'anneau NeoPixel
}

// Boucle principale
void loop() {
  rdm();  // Appeler la fonction pour vérifier si le bouton est pressé
}
