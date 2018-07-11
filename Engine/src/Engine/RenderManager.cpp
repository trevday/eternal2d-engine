#include "RenderManager.hpp"

#include <iostream>
#include <sstream>

#include "CameraComponent.hpp"
#include "GameManager.hpp"

RenderManager::RenderManager() {}
RenderManager::~RenderManager() {}

RenderManager& RenderManager::instance() {
  static RenderManager instance;

  return instance;
}

bool RenderManager::init(int screenWidth, int screenHeight) {
  screenWidth_ = screenWidth;
  screenHeight_ = screenHeight;
  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  gWindow = NULL;
  // Render flag

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError()
                << "\n";
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("Eternal2D", 100, 100, screenWidth,
                               screenHeight, SDL_WINDOW_SHOWN);

    // Check if Window did not create.
    if (gWindow == NULL) {
      errorStream << "Window could not be created! SDL Error: "
                  << SDL_GetError() << "\n";
      success = false;
    } else {
      int flags = IMG_INIT_PNG | IMG_INIT_JPG;
      if ((IMG_Init(flags) & flags) != flags) {
        errorStream << "SDL_image could not initialize! SDL_image Error: "
                    << IMG_GetError();
        success = false;
      }
    }
    // Create a Renderer to draw on
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    // Check if Renderer did not create.
    if (gRenderer == NULL) {
      errorStream << "Renderer could not be created! SDL Error: "
                  << SDL_GetError() << "\n";
      success = false;
    }
  }

  // Init TTF
  if (TTF_Init() < 0) {
    errorStream << "TTF could not initialize! TTF Error: " << TTF_GetError()
                << "\n";
    success = false;
  }

  // If initialization did not work, then print out a list of errors in the
  // constructor.
  if (!success) {
    errorStream << "Failed to initialize!\n";
    std::string errors = errorStream.str();
    std::cout << errors << "\n";
  }
  return success;
}

void RenderManager::shutdown() {
  // Destroy Renderer
  SDL_DestroyRenderer(gRenderer);
  // Destroy window
  SDL_DestroyWindow(gWindow);
  // Point gWindow to NULL to ensure it points to nothing.
  gRenderer = NULL;
  gWindow = NULL;
  // Quit SDL subsystems
  TTF_Quit();
  SDL_Quit();
}

int RenderManager::getWidth() { return RenderManager::instance().screenWidth_; }

int RenderManager::getHeight() { return RenderManager::instance().screenHeight_; }

SDL_Renderer* RenderManager::GetRenderer() { return RenderManager::instance().gRenderer; }

std::shared_ptr<CameraComponent> RenderManager::GetCamera() {
  return RenderManager::instance().camera_;
}
void RenderManager::SetActiveCamera(std::shared_ptr<CameraComponent> camera) {
  RenderManager::instance().camera_ = camera;
}


void RenderManager::Render() {
  SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(gRenderer);

  std::vector<std::shared_ptr<GameObject>> objs =
      GameManager::instance().GetActiveObjects();

  for (auto it = objs.begin(); it != objs.end(); ++it) {
    if ((*it)->GetComponent<RenderComponent>()) {
      (*it)->GetComponent<RenderComponent>()->Render();
    }
  }

  SDL_RenderPresent(gRenderer);
}