
# Puissance 4

Bonjour, nous vous proposons notre version du puissance 4, pour cela suiver la notice d'utilisation étape par étape.



## I) Requis et branchement

### a) Matériel requis

Pour commencer, le matériel nécessaire au projet sont:

- 2 carte Adafruit ESP32 Feather + Shield FeatherWing
- 2 cable usb
- 2 double matrice 32 Led
- 2 joystick 5-way switch
- 1 Led bleu

### b) branchement

Les cartes Adafruit ESP32 Feather doivents être branché sur les Shield FeatherWing.
Ensuite les double matrice 32 Led doivents être branché sur les cartes Adafruit ESP32 Feather. Ensuite les joystick 5-way switch doivents être branché sur un des ports I2C présent sur le bas de la carte, et la Led bleu doit être branché sur une des 2 cartes sur le port AO présent sur le haut de la carte, cette carte deviendra alors votre carte Master. Pour finir brancher les 2 carte Adafruit ESP32 Feather sur un ordinateur avec les cables USB.
## II) Setup logiciel

### a) IDE et Librairie

#### a.I) IDE
Installer IDE Arduino sur le site Arduino officiel. 

#### a.II) Board Manager
Une fois installer, dirigez-vous sur la gauche de l'IDE dans "Boards Manager" et chercher "ESP32" et installer esp32 by Espressif version 3.0.1 (dernière en date).

#### a.III) Library Managaer
Dirigez-vous maintenant dans "Library Manager" et chercher "neopixel" et installer Adafruit NeoPixel by Adafruit version 1.12.2 (dernière en date). Ensuite digirez-vous sur la page git suivante : https://github.com/Seeed-Studio/Grove_Multi_Switch , cliquez sur le bouton code et cliquez sur Download Zip, ensuite dirigez-vous sur l'IDE, cliquez sur Sketch puis passez la souris sur Include Library et cliquez sur Add .ZIP Library et sélectionner le fichier que vous venez de télécharger.

### b) Configuration des cartes

Branchez bien votre microcontroleur sur un port USB.
En dessous de Tools et Help cliquez sur Select Board puis séléctionnez le microcontroleur que vous possédez, ainsi que Serial Port USB.

### c) Importation du projet

Téléchargez puis décompressez le projet ou clonez le repository GitLab.
Dans Arduino Launcher cliquez File puis Open et ouvrez ce fichier:

\45_ari_dattanasio_puissance4/CodeFinalPuissance4

Ensuite dézippez le fichier, et vous obtiendrez deux fichier : "Puissance4_EspMaster" , "Puissance4_EspSlave"

La carte qui possède la Led bleu sera la carte "Master" et vous devez utiliser le programme Puissance4_EspMaster et l'autre carte aura donc le programme Puissance4_EspSlave.

Avant d'upload vous devez sur la carte "Slave" récuperer l'adresse MAC du bluetooth pour cela lancez la carte avec le programme Puissance4_EspSlave et lancer le mode TP, en bougeant le joystick et double click et en vous connectant avec votre téléphone au bluetooth de la carte et en regardant dans les paramètre de l'appareil bluetooth. 

Ensuite dirigez-vous sur le programme Puissance4_EspMaster et dirigez-vous à la ligne 15 et modifier les valeurs pour les valeurs de l'adresse MAC de la carte "Slave".

Vous pouvez désormais Upload les deux programme sur les deux carte !

### d) Application mobile

Vous aurez besoin d'une application mobile pour un des 4 modes, pour cela téléchargez l'application sur le git (Puissance4.apk)

Ensuite connectez-vous avec votre téléphone une première fois au bluetooth des 2 cartes et lancez l'application et dirigez-vous dans les paramètre de l'application et autoriser "Appareils à proximité".
## III) Utilisation

### a) Menu

Le programme possède 4 modes différents qu'on retrouve dans le menu, vous pouvez passer d'un mode à un autre grâce au joystick (droite,gauche) et pour valider le mode effectuer un double clique rapide au milieu, cela lancera le mode, pour revenir dans le menu vous pouvez soit rester appuyer longtemps sur le joystick ou en cliquant sur le bouton reset présente sur la carte.

### b) Mode 1 (1P, Bot, 1 joueur sur une carte)

Le premier mode, se joue avec le joystick : vous déplacer le pion (droite,gauche), une fois votre colonne souhaiter effectuez un double clique pour lancer la chute du pion, ensuite le bot jouera un pion et ainsi de suite jusqu'à la victoire de l'un ou de l'autre.

### c) Mode 2 (1P, 1P, 2 joueur sur une carte avec le joystick)

Le deuxième mode, se joue avec le joystick, même fonctionnement que pour le premier mode seulement avec quelqu'un, chacun son tour choississez votre colonne et lancez les pions jusqu'à la victoire.

### d) Mode 3 (TP, 2 joueur sur une carte ,joystick/application)

Le troisième mode, se joue avec le joystick pour le joueur 1, et avec l'application pour le joueur 2. Pour le joueur 2, une fois sur l'application, vous devez cliquer sur la barre tout en haut de l'application et séléctionné le bluetooth de la carte ESP32 (déjà connecté au préalable), une fois connecté, vous devez séléctionné la colonne voulu lorsque c'est votre tour. Cela jusqu'a la victoire d'un des deux joueurs.

### e) Mode 4 (TP, BT, 2 joueur sur 2 carte avec le joystick)

Le quatrième et dernier mode, se joue avec les 2 cartes esp32, le mode doit être lancer sur les 2 carte en même temps, attendez que la led bleu de la carte Master s'allume, cela signifie que les deux cartes sont bien connecté entre elles, puis jouer chacun votre tour en attendant la chute du pion adverse, jusqu'à la victoire de l'un des deux joueurs.
## IV) Contributeurs

Ari Tural, D'attanasio Thomas, IUT Lyon 1 Bourg en Bresse, INFO 1ère année