#include "SDLTextureWrapper.hpp"

SDLTextureWrapper::SDLTextureWrapper(SDL_Texture* tex) : tex_(tex) {}

SDLTextureWrapper::~SDLTextureWrapper() { SDL_DestroyTexture(tex_); }

SDL_Texture* SDLTextureWrapper::GetTex() const { return tex_; }