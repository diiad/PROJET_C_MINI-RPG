# Mini RPG (C / SDL2)

Turn-based mini RPG written in C with SDL2, built as a team of 3 (ESGI school project). The player picks a class (Warrior / Archer / Mage) and fights enemies to reach the best possible score.

## Features

- SDL main menu (Play / Highscores / Editor / Quit)
- Dynamic class selection, loaded from `assets/classes.json` (HP, Attack, Defense, Agility, Range)
- Turn-based combat with HUD (proportional health bars, combat log, win/lose conditions)
- Built-in map editor: separate executable (`RPG_C_Editor`), saves to `assets/maps/map1.map`

## Stack

- **C**
- **SDL2** (libraries bundled in `lib/` for macOS and Windows)
- **CMake** for the build

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Produces two executables: `RPG_C` (the game) and `RPG_C_Editor` (map editor).

## Structure

```
src/        ← game logic (interface, combat, classes, moves, scores, map...)
include/    ← headers
assets/     ← maps, classes.json, moves.json, highscores
lib/        ← SDL2 (macOS / Windows)
```

## Team

Built by a team of 3 (split: SDL scenes & combat, UI & highscores, class system & balancing — see `TODO.txt` for the detailed roadmap and role breakdown).

---

## Version française

Mini RPG au tour par tour en C avec SDL2, développé en équipe de 3 (projet ESGI). Le joueur choisit une classe (Guerrier / Archer / Mage) et affronte des ennemis pour faire le meilleur score possible.

### Fonctionnalités

- Menu principal SDL, sélection de classe dynamique (JSON), combat au tour par tour avec HUD, éditeur de cartes intégré.

### Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```
