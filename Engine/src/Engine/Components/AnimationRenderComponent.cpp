#include "AnimationRenderComponent.hpp"

#include "ResourceManager.hpp"
#include "TimeManager.hpp"

Animation::Animation(const std::string& spriteSheet, unsigned int srcX,
                     unsigned int srcY, unsigned int srcW, unsigned int srcH,
                     unsigned int numFrames, unsigned int frameDifference,
                     unsigned int FPS)
    : spriteSheet(spriteSheet),
      srcX(srcX),
      srcY(srcY),
      srcW(srcW),
      srcH(srcH),
      numFrames(numFrames),
      frameDifference(frameDifference),
      FPS(FPS) {}

std::shared_ptr<SDL_Rect> Animation::GetRectForFrame(unsigned int frame) {
  if (srcW != 0 && srcH != 0) {
    std::shared_ptr<SDL_Rect> newSrc(new SDL_Rect());
    newSrc->x = srcX + frameDifference * frame;
    newSrc->y = srcY;
    newSrc->w = srcW;
    newSrc->h = srcH;
    return newSrc;
  }
  return std::shared_ptr<SDL_Rect>();
}

AnimationRenderComponent::AnimationRenderComponent(
    std::unordered_map<unsigned int, Animation> map)
    : RenderComponent(), stateMap(map), curState(1), curIndex(0), timer(0) {
  SwitchState(0);
}

void AnimationRenderComponent::SwitchState(unsigned int state) {
  if (state != curState) {
    curState = state;
    curIndex = 0;
    timer = 0;
    texture = ResourceManager::instance().LoadImage(
        stateMap.at(curState).spriteSheet);
    renderSrc = stateMap.at(curState).GetRectForFrame(curIndex);
  }
}

void AnimationRenderComponent::Update() {
  if (stateMap.at(curState).FPS != 0) {
    if (timer >= 1.0 / (float)stateMap.at(curState).FPS) {
      timer = 0;
      if (curIndex < stateMap.at(curState).numFrames - 1) {
        curIndex++;
      } else {
        curIndex = 0;
      }
      renderSrc = stateMap.at(curState).GetRectForFrame(curIndex);
    } else {
      timer += (float)TimeManager::instance().DeltaTime() / 100.0;
    }
  }
}