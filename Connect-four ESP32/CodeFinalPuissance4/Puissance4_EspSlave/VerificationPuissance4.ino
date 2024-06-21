bool verifPossible(int col) {
  //cas de mauvaise entrée
  if ((col < 0) || (col >= cols)) {
    return false;
  }
  //cas de la chute
  for (int i = 0; i < rows; i++) {
    if (plateau[i][col] == 0) {
      return true;
    }
  }
  //Cas de la colonne pleine -> on sort de la boucle !
  return false;
}

bool verifVerticale(uint8_t joueur) {
  for (uint8_t i = 0; i <= rows - 4; ++i) {
    if ((plateau[i][lastx] == joueur) && (plateau[i + 1][lastx] == joueur)
        && (plateau[i + 2][lastx] == joueur) && (plateau[i + 3][lastx] == joueur)) {
      return true;
    }
  }
  return false;
}

bool verifHorizontale(uint8_t joueur) {
  for (uint8_t i = 0; i <= cols - 4; ++i) {
    if ((plateau[lasty][i] == joueur) && (plateau[lasty][i + 1] == joueur)
        && (plateau[lasty][i + 2] == joueur) && (plateau[lasty][i + 3] == joueur)) {
      return true;
    }
  }
  return false;
}

bool verifDiagonaleGauche(uint8_t joueur) {
  uint8_t count = 0;
  int x = lastx;
  int y = lasty;
  while (x > 0 && y > 0) {
    x--;
    y--;
  }  //on se positionne sur coin bas de la diago
  while (x < cols && y < rows) {
    if (plateau[y][x] == joueur) {
      count++;
      if (count == 4) {
        return true;
      }
    } else {
      count = 0;
    }
    x++;
    y++;
  }
  return false;
}

bool verifDiagonaleDroite(uint8_t joueur) {
  uint8_t count = 0;
  int x = lastx;
  int y = lasty;
  while (x > 0 && y < rows - 1) {
    x--;
    y++;
  }  //on se positionne sur coin bas de la diago
  while (x < cols && y >= 0) {
    if (plateau[y][x] == joueur) {
      count++;
      if (count == 4) {
        return true;
      }
    } else {
      count = 0;
    }
    x++;
    y--;
  }
  return false;
}

bool verifDiagonale(uint8_t joueur) {
  return (verifDiagonaleDroite(joueur)) || (verifDiagonaleGauche(joueur));
}

bool verif(uint8_t joueur) {
  return (verifHorizontale(joueur)) || (verifVerticale(joueur)) || (verifDiagonale(joueur));
}