//
// Created by avilay on 11/30/24.
//
#include <stdio.h>
#include <raylib.h>

void gesture_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Input Gesture Demo");

  const Rectangle touch_area = {.x=220, .y=10, (float)screen_width-230.0f, (float)screen_height-20.0f};

  int gesture_count = 0;

  int curr_gesture = GESTURE_NONE;
  int prev_gesture = GESTURE_NONE;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    const int history_len = 20;
    char gesture_history[history_len][32];
    prev_gesture = curr_gesture;
    curr_gesture = GetGestureDetected();
    const Vector2 touch_position = GetTouchPosition(0);

    if (CheckCollisionPointRec(touch_position, touch_area) && (curr_gesture != GESTURE_NONE)) {
      if (curr_gesture != prev_gesture) {
        switch (curr_gesture) {
          case GESTURE_TAP: TextCopy(gesture_history[gesture_count], "GESTURE TAP"); break;
          case GESTURE_DOUBLETAP: TextCopy(gesture_history[gesture_count], "GESTURE DOUBLE TAP"); break;
          case GESTURE_HOLD: TextCopy(gesture_history[gesture_count], "GESTURE HOLD"); break;
          case GESTURE_DRAG: TextCopy(gesture_history[gesture_count], "GESTURE DRAG"); break;
          case GESTURE_SWIPE_RIGHT: TextCopy(gesture_history[gesture_count], "GESTURE SWIPE RIGHT"); break;
          case GESTURE_SWIPE_LEFT: TextCopy(gesture_history[gesture_count], "GESTURE SWIPE LEFT"); break;
          case GESTURE_SWIPE_UP: TextCopy(gesture_history[gesture_count], "GESTURE SWIPE UP"); break;
          case GESTURE_SWIPE_DOWN: TextCopy(gesture_history[gesture_count], "GESTURE SWIPE DOWN"); break;
          case GESTURE_PINCH_IN: TextCopy(gesture_history[gesture_count], "GESTURE SWIPE PINCH IN"); break;
          case GESTURE_PINCH_OUT: TextCopy(gesture_history[gesture_count], "GESTURE PINCH OUT"); break;
          default: break;
        }

        gesture_count += 1;
        if (gesture_count >= history_len) {
          for (int i = 0; i < history_len; i++) TextCopy(gesture_history[i], '\0');
          gesture_count = 0;
        }
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw a white box with a thick gray border by drawing two rectangles on top of each other
    DrawRectangleRec(touch_area, GRAY);
    DrawRectangle(225, 15, screen_width-240, screen_height-30, RAYWHITE);
    DrawText("GESTURES TEST AREA", screen_width-270, screen_height-40, 20, Fade(GRAY, 0.5f));

    // Draw a gray box with banded rows listing the gesture history
    DrawRectangleLines(10, 29, 200, screen_height-50, GRAY);
    DrawText("DETECTED GESTURES", 50, 15, 10, GRAY);
    for (int i = 0; i < gesture_count; i++) {
      if (i % 2 == 0) DrawRectangle(10, 30+20*i, 200, 20, Fade(LIGHTGRAY, 0.5f));
      else DrawRectangle(10, 30+20*i, 200, 20, Fade(LIGHTGRAY, 0.3f));

      if (i < gesture_count - 1) DrawText(gesture_history[i], 35, 36+20*i, 10, DARKGRAY);
      else DrawText(gesture_history[i], 35, 36+20*i, 10, MAROON);
    }

    if (curr_gesture != GESTURE_NONE) DrawCircleV(touch_position, 30, MAROON);

    EndDrawing();
  }

  CloseWindow();
}