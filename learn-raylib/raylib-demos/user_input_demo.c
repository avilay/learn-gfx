//
// Created by avilay on 11/30/24.
//
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

void user_input_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "User Input");

  bool input_in_progress = false;
  char buf[64] = {0};
  buf[0] = '\0';
  int buf_idx = 0;

  char* prompt = NULL;

  int frame_count = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    frame_count += 1;

    if (IsKeyPressed(KEY_G)) {
      input_in_progress = true;
      asprintf(&prompt, "Enter something below and press [ENTER]:");
      GetCharPressed();  // Get G out of the event queue
    }

    if (input_in_progress) {
      int key = GetCharPressed();
      while (key > 0) {
        buf[buf_idx] = (char)key;
        buf_idx += 1;
        buf[buf_idx] = '\0';
        key = GetCharPressed();
      }

      if (IsKeyPressed(KEY_ENTER)) {
        printf("You entered: %s\n", buf);

        // Clean up
        free(prompt);
        prompt = NULL;
        buf[0] = '\0';
        buf_idx = 0;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (prompt) {
      DrawText(prompt, 10, 10, 20, DARKGREEN);
      DrawText(buf, 10, 60, 20, DARKGREEN);

      // Every 40 frames show/no-show the cursor
      if ((frame_count / 40) %2 == 0) {
        DrawText("_", 15 + MeasureText(buf, 20), 60, 20, DARKGREEN);
      }
    }
    DrawRectangle(screen_width/2, screen_height/2, 20, 20, MAROON);
    DrawText("PRESS G TO START INPUT", 10, screen_height-50, 10, DARKGRAY);
    EndDrawing();
  }

}