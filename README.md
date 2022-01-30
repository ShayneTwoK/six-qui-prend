# 6-Qui-Prend!

Voici notre projet d'étude pour la matière DEV LOGICEL AVANCÉ, le jeu du carte du 6 qui prend !

Nous avons la possibilité de ne choisir qu'une salle ou jouer avec un maximum de 10 Joueurs.

Notre jeu reprend le même système de jeu que le 6 qui prend avec un jeu de 104 cartes avec des symboles de tête de boeuf allant de 1 à 7.

10 cartes par joueur, on choisit une carte, un ordre de passage est défini, on choisit sa rangée,
on comptabilise les points si une rangée est terminé, on place la première carte au début de la rangée terminé,
le jeu continue jusqu'a ce que les joueurs n'ont plus de cartes.

Nous avons implémenter :

- Renseignez un pseudo
- Créé ou Rejoindre une salle
- Confirmer le lancement de la partie si on est l'hôte
- Distribution de 10 cartes à chaque joueur
- Affichage de la main du joueur
- Affichage de 4 rangées de cartes
- Choix de la carte à posé
- Choix de la rangée de carte
- Ordre de passage des joueurs
- Comptage des points de chaque joueur
- Rangée de carte qui atteint 6 cartes
- Tour terminé

### Documentation technique

Projet lancer avec le système d'exploitation Windows avec Visual Studio 2022 avec la version net5.0windows.

Client en C# WPF et Serveur en C++.

Pour commencer à jouer récupérer les projet ``` git clone https://github.com/ShayneTwoK/six-qui-prend.git ```

#### Pour lancer le serveur :
Aller dans le Lancer ```six-qui-prend > Server > x64 > Debug et lancer Server.exe```

#### Pour lancer le client :
Aller dans le Lancer ```six-qui-prend > bin > Debug > net5.0-windows et lancer six-qui-prend.exe```
