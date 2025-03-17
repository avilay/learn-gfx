//
// Created by avilay on 11/29/24.
//
#include <stdio.h>
#include <raylib.h>

// Valid state transitions are -
// DEFAULT -> ACTIVE
// ACTIVE -> PRESSED
// PRESSED -> ACTIVE
// ACTIVE -> DEFAULT
typedef enum ButtonState {
  DEFAULT,
  ACTIVE,
  PRESSED
} ButtonState;

void button_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Button Demo");
  InitAudioDevice();

  // This texture is a vertical panel of 3 images corresponding to 3 states of the button -
  // - default (not highlighted)
  // - active (lighted - say on mouse hover)
  // - pressed (lighted pressed - say on mouse press)
  Texture2D button_panel = LoadTexture("./resources/button.png");

  // Play this sound when the button is released, i.e., goes back from pressed to released
  Sound fx_button = LoadSound("./resources/buttonfx.wav");

  float button_height = (float)button_panel.height / 3;  // there are 3 states in the panel

  // This is the part of the panel we'll crop to render
  // We will move it one unit down/up as the button state changes
  Rectangle button_rec = {
    .x=0.0f,
    .y=0.0f,
    .width=(float)button_panel.width,
    .height=button_height
  };

  // This is the rectangle where the button will be rendered
  Rectangle button = {
    .x=(float)screen_width/2.0f - (float)button_panel.width/2.0f,
    .y=(float)screen_height/2.0f - button_height/2.0f,
    .width=(float)button_panel.width,
    .height=button_height
  };

  ButtonState btn_state = DEFAULT;
  bool btn_released = false;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    Vector2 mouse_pos = GetMousePosition();

    if (CheckCollisionPointRec(mouse_pos, button)) {
      btn_state = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? PRESSED : ACTIVE;
      btn_released = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    } else {
      btn_state = DEFAULT;
      btn_released = false;
    }

    if (btn_released) {
      PlaySound(fx_button);
      // Do whatever needs to be done on button released
    }

    button_rec.y = (float)btn_state * button_height;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextureRec(button_panel, button_rec, (Vector2){.x=button.x, .y=button.y}, WHITE);
    EndDrawing();
  }

  UnloadSound(fx_button);
  UnloadTexture(button_panel);
  CloseAudioDevice();
  CloseWindow();
}