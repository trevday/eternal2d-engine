#include "SDLFontWrapper.hpp"

SDLFontWrapper::SDLFontWrapper(TTF_Font* f) : font(f) {}
SDLFontWrapper::~SDLFontWrapper() { TTF_CloseFont(font); }

TTF_Font* SDLFontWrapper::GetFont() const { return font; }