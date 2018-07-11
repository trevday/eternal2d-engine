#ifndef CAMERA_COMPONENT_HPP
#define CAMERA_COMPONENT_HPP

#include <SDL2/SDL.h>

#include "Component.hpp"

/** A class representing a camera within our game */
class CameraComponent : public Component {
 public:
 /** Constructs a new CameraComponent that renders the whole screen. */
  CameraComponent();

  /** Constructs a new CameraComponent that renders to the whole screen. */
  CameraComponent(/** The area of the game world to capture, defined by its center */
                  SDL_Rect renderView);

  /** Constructs a new CameraComponent.*/
  CameraComponent(/** The area of the game world to capture, defined by its center */
                  SDL_Rect renderView,
                  /** The render area on the screen for this camera */
                  SDL_Rect renderArea);

  void Update() override;

  /** Translates the given SDL_Rect based on this camera */
  void Translate(SDL_Rect& dest);

  /** Set this camera as the active camera */
  void SetActive();

  /** Sets the area viewed by the camera to the given rect */
  void SetCaptureArea(SDL_Rect r);

 private:
  /** The area of the game world to capture */
  SDL_Rect renderView;
  /** The render area for this camera */
  SDL_Rect renderArea;
};

#endif