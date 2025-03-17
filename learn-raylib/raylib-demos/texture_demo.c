//
// Created by avilay on 11/28/24.
//
#include "demos.h"
#include <raylib.h>

void texture_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "raylib texture demo");
  Texture2D texture = LoadTexture("./resources/raylib_logo.png");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(texture, screen_width/2 - texture.width/2, screen_height/2 - texture.height/2, WHITE);
    DrawText("This is a texture!", 360, 370, 10, GRAY);
    EndDrawing();
  }

  UnloadTexture(texture);
  CloseWindow();
}