#include "ConfigParser.hpp"

#include <fstream>

#include "FilePaths.hpp"
#include "RenderManager.hpp"

std::string ConfigParser::LEVELS_PATH = "levels.txt";

void ConfigParser::ParseLevelPaths(std::vector<std::string>& levelPaths) {
  std::string basePath = FullAssetsPath() + "Levels/";

  std::string lvlsPath = FullConfigPath() + LEVELS_PATH;
  std::ifstream infile(lvlsPath);

  if (infile.is_open()) {
    std::string line;
    while (std::getline(infile, line)) {
      levelPaths.push_back(basePath + line);
    }
    infile.close();
  } else {
    SDL_Log("Could not open levels file %s", lvlsPath.c_str());
    SDL_Log("Falling back to an empty level.");
    levelPaths.push_back(basePath + "empty.lvl");
  }
}

std::unordered_map<std::string, std::string> ConfigParser::ParseLocale(
    std::string locale) {
  std::unordered_map<std::string, std::string> strs;

  std::ifstream infile(FullAssetsPath() + "Locales/" + locale + ".txt");
  std::string line;
  std::string key, text;

  while (std::getline(infile, line)) {
    key = line.substr(0, line.find(":"));
    text = line.substr(line.find(":")).substr(1);
    strs[key] = text;
  }
  infile.close();
  return strs;
}

std::string ConfigParser::DefaultLocale() {
  std::ifstream infile(FullConfigPath() + "lang.txt");
  std::string line;
  std::getline(infile, line);
  infile.close();
  return line;
}
