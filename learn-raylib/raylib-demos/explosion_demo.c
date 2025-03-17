//
// Created by avilay on 11/30/24.
//
#include <stdio.h>
#include <raylib.h>

typedef struct ExplosionState {
  int row;
  int col;
} ExplosionState;

bool is_state_none(const ExplosionState state) {
  return (state.row == -1 && state.col == -1);
}

ExplosionState get_next_state(const ExplosionState curr) {
  int row = curr.row;
  int col = curr.col + 1;
  if (col > 4) {
    row = curr.row + 1;
    col = 0;
  }
  if (row > 4) {
    row = -1;
    col = -1;
  }
  return (ExplosionState){.row=row, .col=col};
}

ExplosionState new_state() {
  return (ExplosionState){.row=0, .col=0};
}

void explosion_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Explosion Demo");
  InitAudioDevice();

  Sound fx_boom = LoadSound("./resources/boom.wav");

  // A panel with 25 states arranged in a 5 x 5 matrix
  Texture2D explosion_panel = LoadTexture("./resources/explosion.png");

  // This is the part of the panel we'll crop to render
  // We will move it one unit down/up as the explosion state changes
  float explosion_width = (float)explosion_panel.width/5.0f;
  float explosion_height = (float)explosion_panel.height/5.0f;
  ExplosionState curr_state = {0};
  Rectangle explosion_rec = {.x=0, .y=0, .width=explosion_width, .height=explosion_height};

  // The position where explosion will be rendered
  Vector2 position = {0};
  bool exploding = false;

  int frames_count = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !exploding) {
      position = GetMousePosition();
      exploding = true;
      curr_state = new_state();
      position.x -= explosion_width/2.0f;
      position.y -= explosion_height/2.0f;
      PlaySound(fx_boom);
    }

    if (exploding) {
      frames_count += 1;
      // Change the explosion state every 2 frames
      if (frames_count > 2) {
        frames_count = 0;
        curr_state = get_next_state(curr_state);
        exploding = !is_state_none(curr_state);
      }
    }

    if (exploding) {
      explosion_rec.x = explosion_width * (float)curr_state.col;
      explosion_rec.y = explosion_height * (float)curr_state.row;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("CLICK ANYWHERE FOR EXPLOSION", 10, 10, 10, DARKGRAY);
    if (exploding) {
      DrawTextureRec(explosion_panel, explosion_rec, position, WHITE);
    }
    EndDrawing();
  }

  UnloadTexture(explosion_panel);
  UnloadSound(fx_boom);
  CloseAudioDevice();
  CloseWindow();
}
