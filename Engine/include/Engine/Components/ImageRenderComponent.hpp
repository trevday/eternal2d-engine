#ifndef IMAGE_RENDER_COMPONENT_HPP
#define IMAGE_RENDER_COMPONENT_HPP

#include "RenderComponent.hpp"

/**
 * An ImageRenderComponent class. This represents a simple image object within
 * our game, having a position, dimensions, an active state, rect and texture.
 */
class ImageRenderComponent : public RenderComponent {
 public:
  /** Constructs an ImageRenderComponent */
  ImageRenderComponent(/** The path of the image file */
                       const std::string& imgPath);
};

#endif
