#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "ResourceManager.hpp"
#include "SoundManager.hpp"

PYBIND11_EMBEDDED_MODULE(sound, m) {
  pybind11::class_<SDLSoundWrapper, std::shared_ptr<SDLSoundWrapper>>(m,
                                                                      "Sound");

  m.def("PlaySound", &SoundManager::PlaySound);
  m.def("LoadSound", &ResourceManager::LoadSound);
}
