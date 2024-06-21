int deviceDetect(void) {
  if (!mswitch->begin()) {
    return -1;
  }
  if (PID_VAL(mswitch->getDevID()) == PID_5_WAY_TACTILE_SWITCH) {
    key_names = grove_5way_tactile_keys;
  }
  mswitch->setEventMode(true);
  return 0;
}

void deplacementPion(int i) {
  if (key_names[i] == "KEY B") {
    if (emplacementPion == 63) {
      emplacementPion = 56;
    } else {
      emplacementPion++;
    }
  } else if (key_names[i] == "KEY D") {
    if (emplacementPion == 56) {
      emplacementPion = 63;
    } else {
      emplacementPion--;
    }
  }
}

void lancementChutePion(int i) {
  if (key_names[i] == "KEY E" && !messageEnvoye) {
    pionChute = true;
    coupJouer = true;
  }
}

void chutePion() {
  if (pionChute) {
    if (emplacementPion - 8 > -1 && plateau[((emplacementPion - 8) / 8)][((emplacementPion - 8) % 8)] == 0) {
      emplacementPion -= 8;
      delay(200);
    } else {
      pionChute = false;
      coup = poserPion(emplacementPion % 8, joueur);
      emplacementPion = 63;
      if (tourArduino && optionChoisie == 4) {
        partieEnCours = !verif(joueur);
        changerJoueur();
        if (!messageEnvoye && coupJouer) {
          SerialBT.write(convertArduino());
          messageEnvoye = true;
          tourArduino = !tourArduino;
        }
      }
    }
  }
}

void deplacementPionMain() {
  GroveMultiSwitch::ButtonEvent_t* evt;
  delay(1);
  evt = mswitch->getEvent();
  if (!evt) {
    deviceDetect();
    delay(1000);
    return;
  }

  for (int i = 0; i < mswitch->getSwitchCount(); i++) {
    if (evt->button[i] & GroveMultiSwitch::BTN_EV_SINGLE_CLICK) {  // simple clique
      if (optionChoisie != 4) {
        if (!pionChute) {
          deplacementPion(i);
        }
      } else if (optionChoisie == 4 && tourArduino) {
        if (!pionChute) {
          deplacementPion(i);
        }
      }
    }
    if (evt->button[i] & GroveMultiSwitch::BTN_EV_DOUBLE_CLICK) {  // double clique
      if (optionChoisie != 4) {
        if (!pionChute) {
          deplacementPion(i);
        }
        lancementChutePion(i);
      } else if (optionChoisie == 4 && tourArduino) {
        if (!pionChute) {
          deplacementPion(i);
        }
        lancementChutePion(i);
        if (pionChute) {
          while (pionChute) {
            affiche();
          }
        }
      }
    }
    if (evt->button[i] & GroveMultiSwitch::BTN_EV_LONG_PRESS) {  // clique long
      reset();
    }
  }
  affiche();
}

bool poserPion(int col, int joueur) {
  //cas de mauvaise entrée
  if ((col < 0) || (col >= cols)) {
    return false;
  }
  //cas de la chute
  for (int i = 0; i < rows; i++) {
    if (plateau[i][col] == 0) {
      plateau[i][col] = joueur;
      lastx = col;
      lasty = i;
      return true;
    }
  }
  //Cas de la colonne pleine -> on sort de la boucle !
  return false;
}