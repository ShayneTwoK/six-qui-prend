# 6-Qui-Prend!

Voici notre projet d'étude pour la matière DEV LOGICEL AVANCÉ, le jeu du carte du 6 qui prend !

Nous avons la possibilité de ne choisir qu'une salle de jeu par partie avec un maximum de 10 Joueurs.

Notre jeu reprend le même système de jeu que le 6 qui prend avec un jeu de 104 cartes avec des symboles de tête de boeuf allant de 1 à 7.

10 cartes par joueur, on choisit une carte, un ordre de passage est défini, on choisit sa rangée,
on comptabilise les points si une rangée est terminé, on place la première carte au début de la rangée terminé,
le jeu continue jusqu'a ce que les joueurs n'ont plus de cartes.

Nous avons implémenter en C++ :

- Renseignez un pseudo
- Rejoindre une salle
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
- Gestion du status de la jeu

**NOTE :**

Les fonctionnalités du jeu listés ci-dessus ne sont pas toutes implémenter en WPF car nous avons prioriser une gestion du BACK
en C++ avec toutes les règles métier du jeu, le FRONT dispose de Binding, gestion des thread, envoie et reçoit au serveur pour le début du jeu mais ils nous manque juste le traitement de l'affichage coté WPF.

La cause est que notre buffer stocke toute notre JSON envoyer par le serveur et que ce problème nous as bloqué pour la suite 
alors que nous avions toute la structure prête pour afficher les données dans la Vue

### Documentation technique

Projet lancer avec le système d'exploitation Windows avec Visual Studio 2022 avec la version net5.0windows.

Client en C# WPF pattern MVVM et Serveur en C++.

Pour commencer à jouer récupérer le projet ``` git clone https://github.com/ShayneTwoK/six-qui-prend.git ```

#### Pour lancer le serveur :
Aller dans ```six-qui-prend > Server > Lancer Server.sln via Visual Studio```

#### Pour lancer le client :
Aller dans ```six-qui-prend > six-qui-prend.sln```

**PS** : Les exécutables sont disponibles dans les dossiers ```six-qui-prend\Server\x64\Debug``` pour le serveur,
```six-qui-prend\bin\Debug\net5.0-windows``` pour le client mais on vous conseille d'utiliser Visual Studio pour le
mode Debug et voir nos traitement JSON.
