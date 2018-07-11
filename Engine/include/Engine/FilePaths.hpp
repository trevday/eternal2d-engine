#ifndef FILE_PATHS_HPP
#define FILE_PATHS_HPP

#include <string>

#if defined(MINGW)
// Do nothing
#elif defined(__linux__)
#include <limits.h>
#include <unistd.h>
#else
#include <limits.h>
#include <mach-o/dyld.h>
#endif

#define ASSETS_PATH "../Assets/"
#define CONFIG_PATH "../Config/"

inline std::string FullPath() {
  std::string path;
#if defined(MINGW)
// Do nothing for now
#elif defined(__linux__)
  char buf[PATH_MAX];
  ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
  if (len != -1) {
    buf[len] = '\0';
    path = std::string(buf);
  } else {
    path = "";
  }
#else
  char buf[PATH_MAX];
  uint32_t bufsize = PATH_MAX;
  if (!_NSGetExecutablePath(buf, &bufsize)) {
    path = std::string(buf);
  } else {
    path = "";
  }
#endif

  size_t lastSlash = path.find_last_of('/');
  if (lastSlash == std::string::npos) {
    return "";
  }
  return path.substr(0, lastSlash + 1);
}

/** The full assets path. */
inline std::string FullAssetsPath() { return FullPath() + ASSETS_PATH; }

/** The full config path. */
inline std::string FullConfigPath() { return FullPath() + CONFIG_PATH; }

#endif