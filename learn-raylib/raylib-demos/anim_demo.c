//
// Created by avilay on 11/29/24.
//
#include "utils.h"
#include <stdio.h>
#include <raylib.h>

#define MAX_SPEED 15
#define MIN_SPEED 1

void anim_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Anim Demo");

  // This is a panel of 6 poses of scarfy running
  Texture2D scarfy = LoadTexture("./resources/scarfy.png");

  // This is the position on the screen where we'll show scarfy running
  // Yes, he will be running in place
  Vector2 position = {.x=350.0f, .y=280.0f};

  // This is the part of the panel we'll crop to render
  // It is 1/6 the width to render a single pose
  // We'll move this rectangle horizontally every few frames
  Rectangle pose_rec = {.x=0.0f, .y=0.0f, .width=(float)scarfy.width/6, .height=(float)scarfy.height};

  // The current pose being rendered
  int curr_pose = 0;

  // The number of poses to render per second
  // This means that I'll need to change the pose every FPS/nps frames
  // E.g., if pps is 10 and FPS is 60, I'll have to change the pose every 6 frames
  // That way in 1 second I'll cycle through 10 poses.
  int pps = 10;

  SetTargetFPS(60);
  int frames_count = 0;

  while (!WindowShouldClose()) {
    frames_count += 1;
    if (frames_count >= (60/pps)) {
      frames_count = 0;

      // Change the pose by moving the pose rectangle 1 unit
      curr_pose = (curr_pose + 1) % 6;  // 0 <= curr_pose <= 5
      pose_rec.x = (float)curr_pose * (float)scarfy.width/6;
    }

    if (IsKeyPressed(KEY_RIGHT)) pps = (int)min((float)pps+1, MAX_SPEED);
    else if (IsKeyPressed(KEY_LEFT)) pps = (int)max((float)pps-1, MIN_SPEED);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText(TextFormat("CURRENT SPEED: %02i poses per second", pps), 10, 10, 10, DARKGRAY);
    DrawText("PRESS <- / -> TO INCREASE/DECREASE SPEED.", 10, 50, 10, DARKGRAY);
    DrawTextureRec(scarfy, pose_rec, position, WHITE);

    EndDrawing();
  }
}