void afficheOption1() {
  strip.clear();
  uint8_t tab[] = { 62, 55, 54, 46, 39, 38, 37, 59, 51, 43, 35, 58, 57, 42, 49, 41 };  //62 à 37 -> 1 //59 à 41 -> P
  for (uint8_t i : tab) {
    strip.setPixelColor(i, strip.Color(50, 0, 0));
  }
  strip.show();
}

void afficheOption2() {
  strip.clear();
  uint8_t tab[] = { 62, 55, 54, 46, 39, 38, 37, 59, 51, 43, 35, 58, 57, 42, 49, 41, 30, 23, 22, 14, 7, 6, 5, 27, 19, 11, 3, 26, 25, 10, 17, 9 };  //62 à 37 -> 1 //59 à 41 -> P
  for (uint8_t i : tab) {
    if (i > 32) {
      strip.setPixelColor(i, strip.Color(50, 0, 0));
    } else {
      strip.setPixelColor(i, strip.Color(50, 50, 0));
    }
  }
  strip.show();
}

void afficheOption3() {
  strip.clear();
  uint8_t tab[] = { 63, 62, 61, 54, 46, 38, 59, 51, 43, 35, 58, 57, 42, 49, 41 };
  for (uint8_t i : tab) {
    strip.setPixelColor(i, strip.Color(50, 50, 0));
  }
  strip.show();
}

void afficheOption4() {
  strip.clear();
  uint8_t tab[] = { 63, 62, 61, 54, 46, 38, 59, 51, 43, 35, 58, 57, 42, 49, 41, 31, 23, 15, 7, 6, 5, 22, 21, 13, 27, 26, 25, 18, 10, 2 };  //après 41 c le bas
  for (uint8_t i : tab) {
    strip.setPixelColor(i, strip.Color(50, 50, 0));
  }
  strip.show();
}

void choixmenuMain() {
  GroveMultiSwitch::ButtonEvent_t* evt;
  delay(1);
  evt = mswitch->getEvent();
  if (!evt) {
    deviceDetect();
    delay(1000);
    return;
  }

  for (int i = 0; i < mswitch->getSwitchCount(); i++) {
    if (evt->button[i] & GroveMultiSwitch::BTN_EV_DOUBLE_CLICK) {
      if (key_names[i] != "KEY D" && key_names[i] != "KEY B") {
        optionChoisie = optSurvolee;
      }
    }
    if (evt->button[i] & GroveMultiSwitch::BTN_EV_SINGLE_CLICK) {  // simple clique
      if (key_names[i] == "KEY B") {
        if (optSurvolee == 1) {
          optSurvolee = 4;
        } else {
          optSurvolee--;
        }
      } else if (key_names[i] == "KEY D") {
        if (optSurvolee == 4) {
          optSurvolee = 1;
        } else {
          optSurvolee++;
        }
      }
    }
  }
}

void choixMode() {
  while (optionChoisie == 0) {
    if (optSurvolee == 1) {
      afficheOption1();
      choixmenuMain();
    } else if (optSurvolee == 2) {
      afficheOption2();
      choixmenuMain();
    } else if (optSurvolee == 3) {
      afficheOption3();
      choixmenuMain();
    } else if (optSurvolee == 4) {
      afficheOption4();
      choixmenuMain();
    }
  }
}