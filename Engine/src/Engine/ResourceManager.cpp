#include "ResourceManager.hpp"
#include "FilePaths.hpp"
#include "RenderManager.hpp"

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

ResourceManager& ResourceManager::instance() {
  static ResourceManager instance;
  return instance;
}

void ResourceManager::shutdown() {
  for (auto i = loadedImages.begin(); i != loadedImages.end(); ++i) {
    i->second.reset();
  }
  for (auto i = loadedFonts.begin(); i != loadedFonts.end(); ++i) {
    i->second.reset();
  }
  for (auto i = loadedSounds.begin(); i != loadedSounds.end(); ++i) {
    i->second.reset();
  }
}

std::shared_ptr<SDLTextureWrapper> ResourceManager::LoadImage(
    const std::string& path) {
  auto lookup = loadedImages.find(path);
  if (lookup != loadedImages.end()) {
    return lookup->second;
  }

  SDL_Surface* image = IMG_Load(&path[0]);
  if (image == NULL) {
    SDL_Log("Failed to allocate surface: %s", &path[0]);
    return nullptr;
  } else {
    // Create a texture from our surface
    // Textures run faster and take advantage of hardware acceleration
    std::shared_ptr<SDLTextureWrapper> tex(
        new SDLTextureWrapper(SDL_CreateTextureFromSurface(
            RenderManager::instance().GetRenderer(), image)));
    SDL_FreeSurface(image);
    loadedImages.emplace(path, tex);
    return tex;
  }
}

std::shared_ptr<SDLFontWrapper> ResourceManager::LoadFont(
    const std::string& path, int textSize) {
  auto lookup = loadedFonts.find(path);
  if (lookup != loadedFonts.end()) {
    return lookup->second;
  }

  TTF_Font* f = TTF_OpenFont(path.c_str(), textSize);
  if (f == NULL) {
    SDL_Log("Failed to allocate font: %s", &path[0]);
    return nullptr;
  }

  std::shared_ptr<SDLFontWrapper> wrapped(new SDLFontWrapper(f));
  loadedFonts.emplace(path, wrapped);
  return wrapped;
}

std::shared_ptr<SDLSoundWrapper> ResourceManager::LoadSound(
    const std::string& path) {
  const std::string& fullPath = FullAssetsPath() + path;
  auto lookup = ResourceManager::instance().loadedSounds.find(fullPath);
  if (lookup != ResourceManager::instance().loadedSounds.end()) {
    return lookup->second;
  }

  Mix_Chunk* m = Mix_LoadWAV(fullPath.c_str());
  if (m == NULL) {
    SDL_Log("Failed to allocate sound: %s", &fullPath[0]);
    return nullptr;
  }

  std::shared_ptr<SDLSoundWrapper> wrapped(new SDLSoundWrapper(m));
  ResourceManager::instance().loadedSounds.emplace(fullPath, wrapped);
  return wrapped;
}