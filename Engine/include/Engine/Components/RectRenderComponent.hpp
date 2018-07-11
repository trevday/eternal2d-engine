#ifndef RECTRENDERCOMPONENT_HPP
#define RECTRENDERCOMPONENT_HPP

#include "RenderComponent.hpp"

/** A component class for rendering rects as solid colors */
class RectRenderComponent : public RenderComponent {
 public:
  /** Constructs a new RectRenderComponent of the given color */
  RectRenderComponent(/** The color of the component */
                      SDL_Color color);

  virtual void Render() override;

 private:
  /** The color of this RectRenderComponent */
  SDL_Color color;
};

#endif
