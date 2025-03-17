#include <iostream>
#include <unordered_map>

#include "Background.h"
#include "raylib.h"
#ifdef PLATFORM_WEB
#include <emscripten.h>
#endif
using namespace std::string_literals;

void drawFrame() {
  Background& bg = Background::getInstance();
  // bg.printDbg();
  bg.render();
}


int main() {
  std::string resRoot = "/home/avilay/projects/bitbucket/learn/learn-gfx/learn-raylib/web-cpp/resources";
  auto pngs = std::unordered_map<std::string, std::string>{
    {"background", resRoot + "/cyberpunk_street_background.png"},
    {"midground", resRoot + "/cyberpunk_street_midground.png"},
    {"foreground", resRoot + "/cyberpunk_street_foreground.png"}
  };
  InitWindow(800, 450, "Cookie");
  Background& bg = Background::getInstance();
  bg.setScreenDims(800, 450);
  bg.load(pngs);
#ifdef PLATFORM_WEB
  emscripten_set_main_loop(drawFrame, 0, 1);
#else
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    drawFrame();
  }

  CloseWindow();
#endif
}