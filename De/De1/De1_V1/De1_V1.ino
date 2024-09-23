/*    
 *     Bette.Mathys
 *     Dé1_V1
 *     
 *     Systéme de dé, avec un bp quand il est appuyé mets une face aléatoire
 *     sur la bande néopixel
 *     
 *     Bande néopixel, Boutton Poussoir, Carte Arduino
 *     Néopixel: D6, BP: D2
 *     
 *     19/09/2024 Dé1_V1: Appuie BP, afficher une face aléatoire du dé
 *    
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define PIN        6 
#define NUMPIXELS 18 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 

const int BP = 2; 
byte etatBP = 0;

long randNumber;

void rdm (){
  etatBP = digitalRead(BP);
  if (etatBP == HIGH){
    randNumber = random(1 , 7); // Génère un nombre aléatoire entre 1 et 6 si le bouton est appuyé
    Serial.println(randNumber); // Affiche le nombre généré dans le moniteur série
    delay(200);
    return randNumber;
  }
}

void Chiffre1(){
  Serial.println("1"); 
  pixels.setPixelColor(1, pixels.Color(0, 150, 0)); // Change la couleur du pixel 1 en vert
  delay(300); 
  randNumber = 0; // Réinitialise le nombre aléatoire après l'affichage du chiffre
}

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  
  Serial.begin(9600);
  pinMode(BP, INPUT); // Configure le bouton comme entrée

  pixels.begin(); // Initialise la bande de LED
}

void loop() {
  pixels.clear(); // Efface les pixels pour chaque boucle

  rdm(); // Appelle la fonction pour générer un nombre aléatoire

  if (randNumber == 1){
    Chiffre1(); // Si le nombre aléatoire est 1, on change la couleur d'un pixel
  }
}
