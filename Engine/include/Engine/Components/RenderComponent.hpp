#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include "CameraComponent.hpp"
#include "SDLTextureWrapper.hpp"

#include <memory>

/**
 * A RenderComponent class. This represents a simple renderable component within
 * our game, having a rect and texture.
 */
class RenderComponent : public Component {
 public:
  /** Constructs a new RenderComponent */
  RenderComponent();

  virtual void Update() override;

  /** Renders this component based on the given camera */
  virtual void Render();

  /** Whether the renderer should be flipped */
  SDL_RendererFlip renderFlip = SDL_FLIP_NONE;

 protected:
  /** The texture for this RenderComponent */
  std::shared_ptr<SDLTextureWrapper> texture;

  /** The source rect to be used, null if the whole texture is used */
  std::shared_ptr<SDL_Rect> renderSrc;
};

#endif
