#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 100
#define TILE_SIZE 50
#define SPEED 50

void draw_axes() {
  // draw the x-axis from (-5000, 0) to (5000, 0)
  DrawLineEx(
    (Vector2){-GRID_SIZE * TILE_SIZE, .y=0},
    (Vector2){.x=GRID_SIZE * TILE_SIZE, .y=0},
    2,
    BLACK
  );

  // draw the y-axis from (0, -5000) to (0, 5000)
  DrawLineEx(
    (Vector2){.x=0, -GRID_SIZE * TILE_SIZE},
    (Vector2){.x=0, .y=GRID_SIZE * TILE_SIZE},
    2,
    BLACK
  );

  // draw the tick markers
  for (int i = -GRID_SIZE; i < GRID_SIZE; ++i) {
    DrawText(TextFormat("%d", i * TILE_SIZE), i * TILE_SIZE + 5, 5, 10, BLACK);
    DrawText(TextFormat("%d", i * TILE_SIZE), 5, i * TILE_SIZE + 5, 10, BLACK);
  }
}

void draw_grid_lines() {
  for (int i = -GRID_SIZE * TILE_SIZE; i <= GRID_SIZE * TILE_SIZE; i += TILE_SIZE) {
    // printf("APTG DEBUG: i = %d\n", i);
    DrawLineEx(
      (Vector2){.x=-GRID_SIZE * TILE_SIZE, .y=(float)i},
      (Vector2){.x=GRID_SIZE * TILE_SIZE, .y=(float)i},
      1,
      GRAY
    );

    DrawLineEx(
      (Vector2){.x=(float)i, .y=-GRID_SIZE * TILE_SIZE},
      (Vector2){.x=(float)i, .y=GRID_SIZE * TILE_SIZE},
      1,
      GRAY
    );

  }
}

void draw_grid() {
  draw_axes();
  draw_grid_lines();
}

void draw_object(const Vector2 position) {
  DrawRectangle((int)position.x, (int)position.y, 20, 20, MAROON);
}

void update(Vector2* position) {
  const float timespan = GetFrameTime();
  if (IsKeyDown(KEY_UP)) {
    position->y -= timespan * SPEED;
  }
  if (IsKeyDown(KEY_DOWN)) {
    position->y += timespan * SPEED;
  }
  if (IsKeyDown(KEY_LEFT)) {
    position->x -= timespan * SPEED;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    position->x += timespan * SPEED;
  }
  if (IsKeyDown(KEY_R)) {
    position->x = 0.0f;
    position->y = 0.0f;
  }
}

int main() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "my experiments with raylib");
  Vector2 position = {.x=(float)screen_width/2, .y=(float)screen_height/2};
  Vector2 offset = {.x=(float)screen_width/2.0f, .y=(float)screen_height/2.0f};
  Camera2D camera = {0};
  camera.target = position;
  camera.offset = offset;
  camera.zoom = 1.0f;
  camera.rotation = 0.0f;

  SetTargetFPS(60);

  bool position_input_in_progress = false;
  bool camera_input_in_progress = false;
  char buf[16] = {0};
  int buf_idx = 0;
  buf[0] = '\0';

  char* prompt = NULL;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_G)) {
      position_input_in_progress = true;
      asprintf(&prompt, "Enter position coordinates as x y");
    }
    if (IsKeyPressed(KEY_C)) {
      camera_input_in_progress = true;
      asprintf(&prompt, "Enter offset coordinates as x y");
    }
    if (IsKeyPressed(KEY_D)) {
      printf("World Position: (%.02f, %.02f)\n", position.x, position.y);

      Vector2 scr_pos = GetWorldToScreen2D(position, camera);
      printf("Screen Position: (%.02f, %.02f)\n", scr_pos.x, scr_pos.y);

      printf("Camera Offset: (%.02f, %.02f)\n", camera.offset.x, camera.offset.y);
      printf("Camera Target: (%.02f, %.02f)\n", camera.target.x, camera.target.y);

      printf("\n");
    }

    if (position_input_in_progress || camera_input_in_progress) {
      int key = GetCharPressed();
      while (key > 0) {
        if ((key >= 48 && key <= 57) || key == 32 || key == 45) {
          buf[buf_idx] = (char)key;
          buf_idx += 1;
          buf[buf_idx] = '\0';
        }
        key = GetCharPressed();
      }

      if (IsKeyPressed(KEY_ENTER)) {
        char* delim = " ";
        char* scratch;
        const long x = strtol(strtok_r(buf, delim, &scratch), NULL, 10);
        const long y = strtol(strtok_r(NULL, delim, &scratch), NULL, 10);
        if (position_input_in_progress) {
          position.x = (float)x;
          position.y = (float)y;
          position_input_in_progress = false;
        } else if (camera_input_in_progress) {
          offset.x = (float)x;
          offset.y = (float)y;
          camera_input_in_progress = false;
        }
        free(prompt);
        prompt = NULL;
        buf[0] = '\0';
        buf_idx = 0;
      }
    }

    update(&position);

    camera.target = position;
    camera.offset = offset;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (prompt) {
      DrawText(prompt, 450, 25, 20, DARKGREEN);
      DrawText(buf, 450, 50, 20, DARKGREEN);
    }

    BeginMode2D(camera);

    draw_grid();
    draw_object(position);

    EndMode2D();

    EndDrawing();
  }

  CloseWindow();
}