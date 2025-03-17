//
// Created by avilay on 11/30/24.
//
#include "utils.h"
#include <stdio.h>
#include <raylib.h>

void camera_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Camera Demo");

  // background is 512 x 192
  const Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");

  Rectangle player = {.x=400, .y=200, .width=40, .height=40};

  Camera2D camera = {0};
  camera.target = (Vector2){.x=player.x+20.0f, .y=player.y+20.0f};
  camera.offset = (Vector2){.x=(float)screen_width/2.0f, .y=(float)screen_height/2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_RIGHT)) player.x += 2;
    else if (IsKeyDown(KEY_LEFT)) player.x -= 2;
    camera.target = (Vector2){.x=player.x+20, .y=player.y+20};

    if (IsKeyDown(KEY_A)) camera.rotation = min(camera.rotation+1, 40);
    else if (IsKeyDown(KEY_S)) camera.rotation = max(camera.rotation-1, -40);

    float scroll = GetMouseWheelMove();
    camera.zoom = max(min(camera.zoom+scroll*0.05f, 3.0f), 0.1f);

    if (IsKeyPressed(KEY_R)) {
      camera.zoom = 1.0f;
      camera.rotation = 0.0f;
    }

    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));

    BeginMode2D(camera);
    // Draw the background from (-1000, 20) to (1000, 20)
    // The background will be scaled by 2x
    for (int x = -1000; x <= 1000; x += background.width*2) {
      DrawTextureEx(background, (Vector2){.x=(float)x, .y=20}, 0.0f, 2.0f, WHITE);
    }
    DrawRectangleRec(player, RED);
    EndMode2D();

    DrawText("PRESS <-/-> TO MOVE", 10, 10, 10, LIGHTGRAY);
    DrawText("PRESS A/S TO ROTATE", 10, 40, 10, LIGHTGRAY);
    DrawText("SCROLL UP/DOWN TO ZOOM", 10, 70, 10, LIGHTGRAY);
    DrawText("PRESS R TO RESET", 10, 100, 10, LIGHTGRAY);
    DrawText(TextFormat("PLAYER (%0.0f, %0.0f)", player.x, player.y), 10, screen_height-50, 20, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();
}