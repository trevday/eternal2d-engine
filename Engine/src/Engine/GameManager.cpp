#include "GameManager.hpp"

#include "ConfigParser.hpp"
#include "FilePaths.hpp"
#include "LevelLoader.hpp"
#include "RenderManager.hpp"
#include "ResourceManager.hpp"
#include "SoundManager.hpp"

GameManager::GameManager() : curLevel(0), shouldLoadLevel(false) {}
GameManager::~GameManager() {}

GameManager& GameManager::instance() {
  static GameManager instance;

  return instance;
}

void GameManager::init() { LoadLevels(); }

void GameManager::shutdown() {
  permanentObjs_.clear();
  curWorld_.reset();
}

void GameManager::LoadLevels() {
  ConfigParser::ParseLevelPaths(levelPaths);
  shouldLoadLevel = true;
}

void GameManager::LoadLevel(const std::string& path) {
  curWorld_ = std::shared_ptr<GameWorld>(new GameWorld());
  LevelLoader::LoadLevel(path);
}

void GameManager::LoadNextLevel() {
  if (GameManager::instance().curLevel <
      GameManager::instance().levelPaths.size() - 1) {
    GameManager::instance().curLevel++;
  } else {
    GameManager::instance().curLevel = 0;
  }
  GameManager::instance().shouldLoadLevel = true;
}

void GameManager::ReloadLevel() {
  GameManager::instance().shouldLoadLevel = true;
}

void GameManager::Update() {
  if (shouldLoadLevel) {
    shouldLoadLevel = false;
    LoadLevel(levelPaths[curLevel]);
  }

  for (auto i = permanentObjs_.begin(); i != permanentObjs_.end(); ++i) {
    if ((*i)->IsActive()) {
      (*i)->Update();
    }
  }
  curWorld_->Update();
}

std::vector<std::shared_ptr<GameObject>> GameManager::GetActiveObjects() {
  auto objs = GameManager::instance().curWorld_->GetActiveObjects();
  for (auto it = GameManager::instance().permanentObjs_.begin();
       it != GameManager::instance().permanentObjs_.end(); it++) {
    if ((*it)->IsActive()) {
      objs.push_back(*it);
    }
  }
  return objs;
}

void GameManager::RegisterObject(std::shared_ptr<GameObject> obj,
                                 bool isPermanent) {
  if (isPermanent) {
    permanentObjs_.push_back(obj);
  } else {
    curWorld_->RegisterObject(obj);
  }
}