# Mini RPG (C / SDL2)

Mini RPG au tour par tour en C avec SDL2, développé en équipe de 3 (projet ESGI). Le joueur choisit une classe (Guerrier / Archer / Mage) et affronte des ennemis pour faire le meilleur score possible.

## Fonctionnalités

- Menu principal SDL (Jouer / Highscores / Éditeur / Quitter)
- Sélection de classe dynamique, chargée depuis `assets/classes.json` (HP, Attaque, Défense, Agilité, Portée)
- Combat au tour par tour avec HUD (barres de vie proportionnelles, log de combat, conditions de victoire/défaite)
- Éditeur de cartes intégré : exécutable séparé (`RPG_C_Editor`), sauvegarde dans `assets/maps/map1.map`

## Stack

- **C**
- **SDL2** (libs fournies dans `lib/` pour macOS et Windows)
- **CMake** pour le build

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Génère deux exécutables : `RPG_C` (le jeu) et `RPG_C_Editor` (l'éditeur de cartes).

## Structure

```
src/        ← logique du jeu (interface, combat, classes, moves, scores, map...)
include/    ← headers
assets/     ← cartes, classes.json, moves.json, highscores
lib/        ← SDL2 (macOS / Windows)
```

## Équipe

Projet réalisé à 3 (répartition : scènes SDL & combat, UI & highscores, système de classes & équilibrage — voir `TODO.txt` pour le détail des rôles et de la feuille de route).
