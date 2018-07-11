#ifndef ANIMATION_RENDER_COMPONENT_HPP
#define ANIMATION_RENDER_COMPONENT_HPP

#include <unordered_map>
#include <vector>

#include "FilePaths.hpp"
#include "RenderComponent.hpp"

/** Struct for a single animation. */
struct Animation {
  /** The spritesheet for this animation */
  std::string spriteSheet;

  /** The source rect's x coordinate for this animation */
  unsigned int srcX;
  /** The source rect's y coordinate for this animation */
  unsigned int srcY;
  /** The source rect's width for this animation */
  unsigned int srcW;
  /** The source rect's height for this animation */
  unsigned int srcH;

  /** The number of frames of this animation */
  unsigned int numFrames;

  /** The x-axis distance between each frame of the animation */
  unsigned int frameDifference;

  /** The frames per second of this animation */
  unsigned int FPS;

  /** Constructs a new animation */
  Animation(/** The spritesheet for this animation */
            const std::string& spriteSheet,
            /** The source rect's x coordinate for this animation */
            unsigned int srcX,
            /** The source rect's y coordinate for this animation */
            unsigned int srcY,
            /** The source rect's width for this animation */
            unsigned int srcW,
            /** The source rect's height for this animation */
            unsigned int srcH,
            /** The number of frames of this animation */
            unsigned int numFrames,
            /** The x-axis distance between each frame of the animation */
            unsigned int frameDifference,
            /** The frames per second of this animation */
            unsigned int FPS);

  /** Gets the rect of the spritesheet representing the current frame */
  std::shared_ptr<SDL_Rect> GetRectForFrame(/** The frame of the rect needed */
                                            unsigned int frame);
};

/**
 * An AnimationRenderComponent class. This represents an animation object within
 * our game, which has multiple states and spritesheets.
 */
class AnimationRenderComponent : public RenderComponent {
 public:
  /** Constructs a new AnimationRenderComponent */
  AnimationRenderComponent(/** The map of state IDs to animations */
                           std::unordered_map<unsigned int, Animation> map);

  /** Switches the current animation state */
  void SwitchState(/** The state to be switched to */
                   unsigned int state);

  void Update() override;

 private:
  /** The map of state IDs to animations */
  std::unordered_map<unsigned int, Animation> stateMap;

  /** The current state of this animation eg: running */
  unsigned int curState;

  /** The current frame of the animation */
  unsigned int curIndex;

  /** Times when the next frame of the animation is needed */
  float timer;
};

#endif
