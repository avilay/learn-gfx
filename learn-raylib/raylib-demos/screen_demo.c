//
// Created by avilay on 11/30/24.
//
#include <stdio.h>
#include <unistd.h>
#include <raylib.h>

typedef enum GameScreen {
  LOGO = 0,
  TITLE,
  GAMEPLAY,
  ENDING
} GameScreen;

void display_splash(const int seconds) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
  DrawText("WAIT FOR 2 SECONDS...", 290, 220, 20, GRAY);
  EndDrawing();
  sleep(seconds);
}

GameScreen next_screen(const GameScreen curr) {
  GameScreen next = curr;
  switch (curr) {
    case LOGO: {
      next = TITLE;
      break;
    }
    case TITLE: {
      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) next = GAMEPLAY;
      break;
    }
    case GAMEPLAY: {
      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) next = ENDING;
      break;
    }
    case ENDING: {
      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) next = TITLE;
      break;
    }
  }
  return next;
}

void draw_title(const int width, const int height) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawRectangle(0, 0, width, height, GREEN);
  DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
  DrawText("PRESS [ENTER] OR [TAP] TO JUMP TO GAMEPLAY", 120, 220, 20, DARKGREEN);
  EndDrawing();
}

void draw_gameplay(const int width, const int height) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawRectangle(0, 0, width, height, PURPLE);
  DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
  DrawText("PRESS [ENTER] OR [TAP] TO JUMP TO ENDING", 120, 220, 20, MAROON);
  EndDrawing();
}

void draw_ending(const int width, const int height) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawRectangle(0, 0, width, height, BLUE);
  DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
  DrawText("PRESS [ENTER] OR [TAP] TO RETURN TO TITLE", 120, 220, 20, DARKBLUE);
  EndDrawing();
}

void screen_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Basic Screen Manager Demo");

  SetTargetFPS(60);

  display_splash(2);
  GameScreen screen = LOGO;

  while (!WindowShouldClose()) {
    screen = next_screen(screen);
    switch (screen) {
      case LOGO: {}
      case TITLE: {
        draw_title(screen_width, screen_height);
        break;
      }
      case GAMEPLAY: {
        draw_gameplay(screen_width, screen_height);
        break;
      }
      case ENDING: {
        draw_ending(screen_width, screen_height);
        break;
      }
    }
  }

  CloseWindow();
}