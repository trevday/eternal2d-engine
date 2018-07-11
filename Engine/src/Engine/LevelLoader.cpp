#include "LevelLoader.hpp"

#include <fstream>
#include <memory>

#include "GameManager.hpp"
#include "RenderManager.hpp"
#include "ScriptComponent.hpp"

void LevelLoader::LoadLevel(std::string path) {
  std::ifstream lvlFile(path, std::ios::in | std::ios::binary);

  if (!lvlFile.is_open()) {
    SDL_Log("Could not load %s\n", path.c_str());
    return;
  }

  int numObjs;
  lvlFile.read((char*)&numObjs, sizeof(int));

  for (int i = 0; i < numObjs; i++) {
    int nameLength;
    lvlFile.read((char*)&nameLength, sizeof(int));
    char ignored[nameLength];
    lvlFile.read(&ignored[0], nameLength);

    int x;
    int y;
    int w;
    int h;
    bool permanent;
    lvlFile.read((char*)&x, sizeof(int));
    lvlFile.read((char*)&y, sizeof(int));
    lvlFile.read((char*)&w, sizeof(int));
    lvlFile.read((char*)&h, sizeof(int));
    lvlFile.read((char*)&permanent, sizeof(bool));
    std::shared_ptr<GameObject> go = GameObject::Create(x, y, w, h, false, permanent);

    int scriptNameLength;
    lvlFile.read((char*)&scriptNameLength, sizeof(int));
    char scriptName[scriptNameLength];
    lvlFile.read(&scriptName[0], scriptNameLength);
    int classNameLength;
    lvlFile.read((char*)&classNameLength, sizeof(int));
    char className[classNameLength];
    lvlFile.read(&className[0], classNameLength);
    // always at least 1 for null terminator
    if (scriptNameLength > 1 && classNameLength > 1) {
      go->AddComponent<ScriptComponent>(std::make_shared<ScriptComponent>(
          std::string(scriptName), std::string(className)));
    }

    int spriteNameLength;
    lvlFile.read((char*)&spriteNameLength, sizeof(int));
    char spriteName[spriteNameLength];
    lvlFile.read(&spriteName[0], spriteNameLength);
    if (spriteNameLength > 1) {
      go->AddComponent<RenderComponent>(
          std::make_shared<ImageRenderComponent>(std::string(spriteName)));
    }
  }
  SDL_Log("Loaded %d GameObjects from %s", numObjs, path.c_str());
}
