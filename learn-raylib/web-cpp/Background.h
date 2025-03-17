//
// Created by avilay on 12/25/24.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "raylib.h"
#include <string>
#include <unordered_map>


class Background {
  Texture2D back = {};
  float backSpeed = 0;
  float backX = 0;

  Texture2D mid = {};
  float midSpeed = 0;
  float midX = 0;

  Texture2D fore = {};
  float foreSpeed = 0;
  float foreX = 0;

  int screenWidth = 0;
  int screenHeight = 0;

  void drawBack();
  void drawMid();
  void drawFore();

  Background() = default;
public:
  static Background& getInstance();
  void setScreenDims(int width, int height);
  void render();
  void load(std::unordered_map<std::string, std::string> pngs);
  void loadBack(std::string_view path, float speed);
  void loadMid(std::string_view path, float speed);
  void loadFore(std::string_view path, float speed);
  void printDbg();
};



#endif //BACKGROUND_H
