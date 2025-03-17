//
// Created by avilay on 11/26/24.
//
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void log(const int msg_type, const char* text, va_list args) {
  char time_str[64] = {0};
  const time_t now = time(NULL);
  const struct tm* tm_info = localtime(&now);
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
  printf("[%s] ", time_str);

  switch (msg_type) {
    case LOG_INFO:
      printf("[INFO] : ");
      break;
    case LOG_ERROR:
      printf("[ERROR] : ");
      break;
    case LOG_WARNING:
      printf("[WARN] : ");
      break;
    case LOG_DEBUG:
      printf("[DEBUG] : ");
      break;
    default:
      break;
  }

  vprintf(text, args);
  printf("\n");
}

void log_demo() {
  const int screen_width = 800;
  const int screen_height = 450;
  SetTraceLogCallback(log);

  InitWindow(screen_width, screen_height, "Raylib Scratch");

  SetTargetFPS(60);
  int frame_count = 0;
  while (!WindowShouldClose()) {
    BeginDrawing();
    frame_count += 1;
    ClearBackground(RAYWHITE);
    DrawRectangle(screen_width/2, screen_height/2, 50, 50, MAROON);
    DrawText(
      "Check the console output to see the custom logger in action",
      60,
      200,
      20,
      LIGHTGRAY
    );
    if (frame_count % 100 == 0) {
      TraceLog(LOG_ERROR, "%d - This is a test error log", frame_count);
    }
    EndDrawing();
  }
}