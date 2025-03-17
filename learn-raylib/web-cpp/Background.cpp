//
// Created by avilay on 12/25/24.
//

#include "Background.h"

#include "raylib.h"
#include <stdexcept>


void Background::loadBack(std::string_view path, float speed) {
  back = LoadTexture(path.data());
  backSpeed = speed;
}

void Background::loadMid(std::string_view path, float speed) {
  mid = LoadTexture(path.data());
  midSpeed = speed;
}

void Background::loadFore(std::string_view path, float speed) {
  fore = LoadTexture(path.data());
  foreSpeed = speed;
}

void Background::drawBack() {
  backX -= backSpeed;
  if (backX <= static_cast<float>(-back.width * 2))
    backX = 0;

  DrawTextureEx(back, (Vector2){.x=backX, .y=20}, 0.0f, 2.0f, WHITE);

  auto backX_ = static_cast<float>(back.width) * 2 + backX;
  DrawTextureEx(back, (Vector2){.x=backX_, .y=20}, 0.0f, 2.0f, WHITE);
}

void Background::drawMid() {
  midX -= midSpeed;
  if (midX <= static_cast<float>(-mid.width * 2))
    midX = 0;

  DrawTextureEx(mid, (Vector2){.x=midX, .y=20}, 0.0f, 2.0f, WHITE);

  auto midX_ = static_cast<float>(mid.width) * 2 + midX;
  DrawTextureEx(mid, (Vector2){.x=midX_, .y=20}, 0.0f, 2.0f, WHITE);
}

void Background::drawFore() {
  foreX -= foreSpeed;
  if (foreX <= static_cast<float>(-fore.width * 2))
    foreX = 0;

  DrawTextureEx(fore, (Vector2){.x=foreX, .y=20}, 0.0f, 2.0f, WHITE);

  auto foreX_ = static_cast<float>(fore.width) * 2 + foreX;
  DrawTextureEx(fore, (Vector2){.x=foreX_, .y=20}, 0.0f, 2.0f, WHITE);
}

void Background::render() {
  BeginDrawing();
  ClearBackground(GetColor(0x052c46ff));
  drawBack();
  drawMid();
  drawFore();
  EndDrawing();
}

void Background::load(std::unordered_map<std::string, std::string> pngs) {
  for (const auto&[kind, png] : pngs) {
    if (kind == "background")
      loadBack(png, 0.1);
    else if (kind == "midground")
      loadMid(png, 0.5);
    else if (kind == "foreground")
      loadFore(png, 1.0);
    else
      throw std::runtime_error("Unknown background kind: " + kind);
  }
}

void Background::setScreenDims(int width, int height) {
  screenWidth = width;
  screenHeight = height;
}

Background& Background::getInstance() {
  static Background instance;
  return instance;
}

void Background::printDbg() {
  printf("TODO");
}



