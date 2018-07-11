#include "FilePaths.hpp"
#include "GameManager.hpp"
#include "InputManager.hpp"
#include "PhysicsManager.hpp"
#include "PythonManager.hpp"
#include "RenderManager.hpp"
#include "ResourceManager.hpp"
#include "SoundManager.hpp"
#include "TimeManager.hpp"

int main(int argc, char* argv[]) {
  if (argc > 1 && std::string("default").compare(argv[1]) != 0) {
    ConfigParser::LEVELS_PATH = argv[1];
  }

  bool shouldDisplayFPS = false;
  if (argc > 2 && atoi(argv[2]) == 1) {
    shouldDisplayFPS = true;
  }

  PythonManager::instance().init();
  if (!RenderManager::instance().init(800, 600)) {
    return 1;
  }
  if (!SoundManager::instance().init()) {
    return 1;
  }
  PhysicsManager::instance().init();
  GameManager::instance().init();

  // Set up timer and frame-counter for FPS
  Uint32 start = SDL_GetTicks();
  int frames = 0;

  while (true) {
    Uint32 frameStart = SDL_GetTicks();
    InputManager::instance().PollInput();
    if (InputManager::instance().ShouldQuit()) {
      break;
    }
    PhysicsManager::instance().Step();
    GameManager::instance().Update();
    RenderManager::instance().Render();
    TimeManager::instance().StablizeFramerate();

    // FPS output
    float avgFPS = frames / ((SDL_GetTicks() - start) / 1000.0f);
    ++frames;
    if (shouldDisplayFPS) {
      SDL_Log("FPS: %f", avgFPS);
    }
  }

  GameManager::instance().shutdown();
  PhysicsManager::instance().shutdown();
  ResourceManager::instance().shutdown();
  SoundManager::instance().shutdown();
  RenderManager::instance().shutdown();
  PythonManager::instance().shutdown();

  return 0;
}
