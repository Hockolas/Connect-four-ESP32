void deplacervers(uint8_t emplacementVoulu) {
  if (emplacementPion > emplacementVoulu) {
    emplacementPion--;
    delay(125);
  }
  if (emplacementPion < emplacementVoulu) {
    emplacementPion++;
    delay(125);
  }
  if (emplacementPion == emplacementVoulu) {
    affiche();
    deplacementFini = true;
  }
}

uint8_t trouverPossible() {
  uint8_t i = -1;
  while (verifPossible(i) == false) {
    i = random(0, 7);
  }
  return i;
}

void deroulementBot() {
  if (joueur == 2) {
    tourBot = true;
    if (deplacementFini) {
      emplacementVoulu = trouverPossible() + 56;
      deplacementFini = false;
    }
    deplacervers(emplacementVoulu);
    if (deplacementFini) {
      tourBot = false;
      pionChute = true;
      while (pionChute == true) {
        affiche();
      }
      partieEnCours = !verif(joueur);
      changerJoueur();
    }
  }
}