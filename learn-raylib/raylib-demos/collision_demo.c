//
// Created by avilay on 11/30/24.
//
#include <stdio.h>
#include <raylib.h>

void collision_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Collision Demo");

  // Box A: Moving box
  Rectangle box_a = {
    .x=10,
    .y=(float)GetScreenHeight()/2.0f-50,
    .width=200,
    .height=100
  };
  int box_a_speed_x = 4;

  // Box B: Mouse moved box
  Rectangle box_b = {
    .x=(float)GetScreenWidth()/2.0f-30,
    (float)GetScreenHeight()/2.0f-30,
    .width=60,
    .height=60
  };

  Rectangle overlap = {0};

  bool paused = false;
  bool is_colliding = false;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (!paused) box_a.x += (float)box_a_speed_x;

    // Bounce box A on horizontal screen limits
    float right_edge = box_a.x + box_a.width;
    float left_edge = box_a.x;
    if (right_edge >= (float)GetScreenWidth() || left_edge <= 0) box_a_speed_x *= -1;

    // Update player controlled box
    box_b.x = (float)GetMouseX() - box_b.width / 2;
    box_b.y = (float)GetMouseY() - box_b.height / 2;

    // Make sure box B does not go out of the screen
    right_edge = box_b.x + box_b.width;
    if (right_edge >= (float)GetScreenWidth()) box_b.x = (float)GetScreenWidth() - box_b.width;

    left_edge = box_b.x;
    if (left_edge <= 0) box_b.x = 0;

    float top_edge = box_b.y;
    if (top_edge <= 0) box_b.y = 0;

    float bottom_edge = box_b.y + box_b.height;
    if (bottom_edge >= (float)GetScreenHeight()) box_b.y = (float)GetScreenHeight() - box_b.height;

    // Check for collision
    is_colliding = CheckCollisionRecs(box_a, box_b);
    if (is_colliding) overlap = GetCollisionRec(box_a, box_b);

    if (IsKeyPressed(KEY_SPACE)) paused = !paused;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw a red border if the boxes are colliding
    // otherwise draw a black border
    DrawRectangleLines(
      0,
      0,
      GetScreenWidth(),
      GetScreenHeight(),
      is_colliding? RED : BLACK
    );

    DrawRectangleRec(box_a, GOLD);
    DrawRectangleRec(box_b, BLUE);

    if (is_colliding) {
      DrawRectangleRec(overlap, LIME);
      printf("Collision! Collision area = %0.02f\n", overlap.width * overlap.height);
    }
    DrawText("Press SPACE to pause/resume", 10, 10, 10, DARKGRAY);

    EndDrawing();
  }

  CloseWindow();
}