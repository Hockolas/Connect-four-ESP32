
#include "Grove_Multi_Switch.h"
#include <Adafruit_NeoPixel.h>
#include "BluetoothSerial.h"
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif                  //On utilise la 2.0.16
#define LED_PIN 27
#define LED_COUNT 64
BluetoothSerial SerialBT;
bool SlaveConnected;
String device_name = "ESP32-Puissance4Master";
String slaveName = "ESP32-Puissance4Slave";
int previousMillisReconnect = 0;
uint8_t address[6] = { 0xA8, 0x03, 0x2A, 0xEA, 0x90, 0xD6 };  //Slave adress
GroveMultiSwitch mswitch[1];
const char* grove_5way_tactile_keys[] = {
  "KEY A",
  "KEY B",
  "KEY C",
  "KEY D",
  "KEY E",
};
const char** key_names;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint8_t emplacementPion = 63;
int joueur = 1;
const uint8_t rows = 7;
const uint8_t cols = 8;
int lastx;
uint8_t lasty;
bool partieEnCours = true;
uint8_t plateau[rows][cols];
bool tourBot = false;
bool deplacementFini = true;
uint8_t emplacementVoulu;
bool pionChute = false;
bool coup = false;
uint8_t optionChoisie = 0;
uint8_t optSurvolee = 1;
char bt;
int bt2;
int delayVictoire = 0;
uint8_t compteurLed = 63;
bool tourArduino = false;
bool messageEnvoye = false;
bool coupJouer = false;

void setup() {
  Serial.begin(115200);
  pinMode(26, OUTPUT);
  if (deviceDetect() < 0) {
    for (;;)
      ;
  }
  strip.begin();
  strip.show();
  strip.setBrightness(10);
  choixMode();
  if (optionChoisie == 3 || optionChoisie == 4) {
    SerialBT.begin(device_name);
    if (optionChoisie == 4) {
      SerialBT.register_callback(Bt_Status);
      SlaveConnect();
    }
  }
  initPlateau();
  affiche();
}

void loop() {
  if (optionChoisie == 4) {
    if (!SlaveConnected) {                                // BT: Condition to evalute if the connection is established/lost
      if (millis() - previousMillisReconnect >= 10000) {  // BT: Check that 10000ms is passed
        previousMillisReconnect = millis();               // BT: Set previousMillisReconnect to current millis                                                                        // BT: Increase the the reconnection attempts counter +1
        SerialBT.end();                                   // BT: Close the bluetooth device
        SerialBT.begin(device_name, true);                // BT: Starts the bluetooth device with the name stored in the myName variable as SERVER(Master)
        SlaveConnect();                                   // BT: Calls the bluetooth connection function to cnnect to the CLIENT(Slave)
      }
    }
  }
  coup = false;
  if (optionChoisie == 2 || !tourBot) {  //Si c'est un 1v1 ou si ce n'est pas le tour du bot
    deplacementPionMain();
  }
  if (partieEnCours && !pionChute && optionChoisie == 1) {  // Jouer contre le "hasard"
    affiche();
    partieEnCours = !verif(joueur);
    changerJoueur();
    deroulementBot();
    if (!partieEnCours) {
      delayVictoire = millis();
    }
  }
  else if (partieEnCours && !pionChute && optionChoisie == 2) {  // Déroulement 1v1 contre un joueur humain
    affiche();
    partieEnCours = !verif(joueur);
    changerJoueur();
    if (!partieEnCours) {
      delayVictoire = millis();
    }
  } else if (partieEnCours && !pionChute && optionChoisie == 3) {
    affiche();
    partieEnCours = !verif(joueur);
    changerJoueur();
    if (joueur == 2) {
      waitUntilBtSerial();
      partieEnCours = !verif(joueur);
      changerJoueur();
    }
    if (!partieEnCours) {
      delayVictoire = millis();
    }
  }
  if (partieEnCours == false) {
    victoire();
  }
  if (optionChoisie == 4 && partieEnCours && !pionChute && SlaveConnected) {
    if (!tourArduino) {
      messageEnvoye = false;
      coupJouer = false;
      waitUntilBtSerial();
      tourArduino = !tourArduino;

    } else if (tourArduino) {
    }
    if (!partieEnCours) {
      delayVictoire = millis();
    }
  }
}
