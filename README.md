# ESP_Board_Portail
Le but de ce programme est de permettre d'utiliser une carte wifi relay trouvable sur le net pour quelque euros pour injecter un programme personnalisé.
![carte_wifi_relay_3](https://user-images.githubusercontent.com/38717304/56850312-43823000-6901-11e9-9394-a343268da8ee.jpg)
Le cas échéant, il s'agit de réaliser un module qui permettra via Jeedom (par exemple) de réaliser les opérations suivantes :
- Commander l'ouverture d'un portail (relais) par une commande http.
- Récupérer l'état du portail (MQTT) via une interruption déclenchée par le signal issu de l'optocoupleur.

## Matériel nécessaire
- Une carte wifi relay
- Un adaptateur USB série (FT232 par exemple)
- Le programme arduino pour téléversser

## Modifications à effectuer sur la carte
Souder des connecteur (header 2.54) sur les emplacements P5 et P6
 * P5 : pour le shunt de programmation.
 * P6 : pour le port série.

## Chargement du nouveau programme
### Important :
- Je ne détaille pas la partie programmation depuis le logiciel arduino, je supose que c'est acqui.
- Activer le shunt de programmation seulement pour programmer le module.
- Connecter la masse de l'alimentation de la carte à celle de l'adaptateur USB série (FT232 par exemple)
### procédure de mise à jour (chargement)
- Débrancher toutes les alims exterieur et port série
- Activer le shunt de programmation
- Brancher l'alim externe
- Brancher l'alim port serie
- Lancer la mise à jour
- Une fois la mise a jour démarrée led module bleu clignote rapidement, on peut retirer le shunt de prog
- Retirer l'alim du port série
- Debrancher et rebrancher l'alim externe pour redemarrer le module

## Jeedom
- Installer et paramétrer le plugins MQTT (pour la récupération de l'état).
- Créer la commande http et l'appeler depuis un scénario ou un bouton
