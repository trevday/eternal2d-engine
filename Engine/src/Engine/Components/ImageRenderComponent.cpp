#include "ImageRenderComponent.hpp"

#include "FilePaths.hpp"
#include "ResourceManager.hpp"

ImageRenderComponent::ImageRenderComponent(const std::string& imgPath)
    : RenderComponent() {
  texture = ResourceManager::instance().LoadImage(FullAssetsPath() +
                                                  "Sprites/" + imgPath);
}
