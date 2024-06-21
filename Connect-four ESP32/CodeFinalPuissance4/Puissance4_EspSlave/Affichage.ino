void affiche() {
  uint8_t compteur = 0;
  chutePion();
  if (partieEnCours && compteurLed != 1) {
    strip.clear();
  }
  for (uint8_t i = 0; i < rows; i++) {
    for (uint8_t j = 0; j < cols; j++) {
      if (plateau[i][j] == 1) {
        strip.setPixelColor(compteur, strip.Color(50, 0, 0));
      } else if (plateau[i][j] == 2) {
        strip.setPixelColor(compteur, strip.Color(50, 50, 0));
      }
      compteur++;
    }
  }
  if (joueur == 1) {
    strip.setPixelColor(emplacementPion, strip.Color(50, 0, 0));
  } else if (joueur == 2) {
    strip.setPixelColor(emplacementPion, strip.Color(50, 50, 0));
  }
  strip.show();
}

void victoire() {
  if (delayVictoire + 50 < millis() && compteurLed != -1) {
    if (joueur == 1) {
      strip.setPixelColor(compteurLed, strip.Color(50, 0, 0));
      strip.show();
    } else {
      strip.setPixelColor(compteurLed, strip.Color(50, 50, 0));
      strip.show();
    }
    if (compteurLed == 0) {
      compteurLed = 63;
      strip.clear();
    }
    compteurLed--;
    delayVictoire = millis();
  }
}