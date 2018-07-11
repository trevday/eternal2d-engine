# Eternal2D Engine

## Background
The Eternal2D Engine is a simple 2D engine with support for a number of basic game creation features. It was developed in collaboration with [Chris Juchem](https://github.com/chrisjuchem) and [Alex Zilbersher](https://github.com/zilby) as a project for a Game Engines course. For more in-depth information on the engine's features, documentation of the code, and a video demonstration, please visit https://zilby.github.io/GameBuildingEngine/.

## Resources Used
There are a number of external resources that are redistributed with this project:
- Music: https://www.bensound.com/royalty-free-music
- Raleway Font: license can be found at http://scripts.sil.org/OFL
- Additional Sound FX: https://assetstore.unity.com/packages/templates/packs/2d-breakout-example-project-107757
- Brick texture: https://opengameart.org/content/bricks-tiled-texture-64x64
- Code Libraries:
  - SDL2: https://www.libsdl.org/
    - SDL2 Image: https://www.libsdl.org/projects/SDL_image/
    - SDL2 Mixer: https://www.libsdl.org/projects/SDL_mixer/
    - SDL2 TTF: https://www.libsdl.org/projects/SDL_ttf/
  - pybind11: https://github.com/pybind/pybind11
  - Box2D: https://github.com/erincatto/Box2D
  - Pillow: https://python-pillow.org/
  - appJar: http://appjar.info/

## Included Sample Projects
- Minesweeper
  - Script: Eternal2D/Assets/Scripts/minesweeper.py
  - Level File: Eternal2D/Assets/Levels/Minesweeper.lvl
  - To run, pass the argument 'minesweeper.txt' to the engine executable
- Pong
  - Script: Eternal2D/Assets/Scripts/Pong.py, Eternal2D/Assets/Scripts/winlose.py
  - Level File: Eternal2D/Assets/Levels/Pong.lvl, Eternal2D/Assets/Levels/win.lvl, Eternal2D/Assets/Levels/lose.lvl
  - Simply run the executable without any arguments, or optionally pass 'levels.txt' ('levels.txt' is the default levels      config file)