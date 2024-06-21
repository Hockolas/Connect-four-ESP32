void reset() {
  ESP.restart();
}

void initPlateau() {
  for (uint8_t i = 0; i < rows; i++) {
    for (uint8_t j = 0; j < cols; j++) {
      plateau[i][j] = 0;
    }
  }
}
void changerJoueur() {
  if (joueur == 1 && coup && !pionChute && partieEnCours) {
    joueur = 2;
  } else if (joueur == 2 && coup && !pionChute && partieEnCours) {
    joueur = 1;
  }
}

void waitUntilBtSerial() {
  partieEnCours = !verif(joueur);
  if (partieEnCours) {
    while (!SerialBT.available()) {
      GroveMultiSwitch::ButtonEvent_t* evt;
      delay(1);
      evt = mswitch->getEvent();
      if (!evt) {
        deviceDetect();
        delay(1000);
        return;
      }
      for (int i = 0; i < mswitch->getSwitchCount(); i++) {
        if (evt->button[i] & GroveMultiSwitch::BTN_EV_LONG_PRESS) {  // clique long
          reset();
        }
      }
    }  //On attend de recevoir
    bt = SerialBT.read();
    if (bt == '0') {
      emplacementPion = 63;
      pionChute = true;
    } else if (bt == '1') {
      emplacementPion = 62;
      pionChute = true;
    } else if (bt == '2') {
      emplacementPion = 61;
      pionChute = true;
    } else if (bt == '3') {
      emplacementPion = 60;
      pionChute = true;
    } else if (bt == '4') {
      emplacementPion = 59;
      pionChute = true;
    } else if (bt == '5') {
      emplacementPion = 58;
      pionChute = true;
    } else if (bt == '6') {
      emplacementPion = 57;
      pionChute = true;
    } else if (bt == '7') {
      emplacementPion = 56;
      pionChute = true;
    } else if (bt == 'R') {
      reset();
    }
  }
}

char convertArduino() {
  if (7 - lastx == 0) {
    return '0';
  } else if (7 - lastx == 1) {
    return '1';
  } else if (7 - lastx == 2) {
    return '2';
  } else if (7 - lastx == 3) {
    return '3';
  } else if (7 - lastx == 4) {
    return '4';
  } else if (7 - lastx == 5) {
    return '5';
  } else if (7 - lastx == 6) {
    return '6';
  } else if (7 - lastx == 7) {
    return '7';
  }
}
