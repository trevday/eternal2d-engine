#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "ImageRenderComponent.hpp"
#include "TextRenderComponent.hpp"

/**
 * This class manages the rendering of images in our
 * game as a singleton.
 */
class RenderManager {
 public:
  /** The singleton instance of the RenderManager */
  static RenderManager& instance();

  /**
   * Initializes the render manager, SDL, and TTF, and creates the SDL_Window
   * and SDL_Renderer.
   * @return Whether or not the RenderManager was properly initialized
   */
  bool init(/** The width of the screen */
            int screenWidth,
            /** The height of the screen */
            int screenHeight);

  /**
   * Shuts down the render manager, SDL, and TTF
   */
  void shutdown();

  /**
   * Render the game
   */ 
  void Render();

  /**
   * Gets the SDL_Renderer
   * @return The SDL_Renderer
   */
  static SDL_Renderer* GetRenderer();

  /** 
   * Gets the current active camera. 
   * @return A shared pointer to the current active camera. 
   */
  static std::shared_ptr<CameraComponent> GetCamera();

  /** Sets the current active camera */
  static void SetActiveCamera(/** The camera to be set as the current active camera */
                              std::shared_ptr<CameraComponent> camera);

  /**
   * Gets the screen width
   * @return The screen width
   */
  static int getWidth();

  /**
   * Gets the screen height
   * @return The screen height
   */
  static int getHeight();

  /** Stop the compiler from generating methods to copy the object */
  RenderManager(const RenderManager&) = delete;

  /** Stop the compiler from generating methods to copy the object */
  RenderManager& operator=(const RenderManager&) = delete;

 private:
  /** Constructs a RenderManager */
  RenderManager();

  /** Destructs a RenderManager */
  ~RenderManager();

  /** The width of the screen */
  int screenWidth_;

  /** The height of the screen */
  int screenHeight_;

  /** The window we'll be rendering to */
  SDL_Window* gWindow;

  /** The SDL_Renderer for this instance */
  SDL_Renderer* gRenderer;

  /** The Camera to use to render game objects*/
  std::shared_ptr<CameraComponent> camera_;
};

#endif
