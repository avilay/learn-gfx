//
// Created by avilay on 12/1/24.
//
#include <stdio.h>
#include <raylib.h>
#include <stdatomic.h>
#include <pthread.h>

typedef enum LoadingState {
  WAITING,
  LOADING,
  FINISHED
} LoadingState;

static atomic_bool data_loaded = false;
static void* load_data_thread(void* arg);
static atomic_int data_progress = 0;

void loading_thread_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Loading Thread Demo");

  pthread_t thread_id = {0};
  LoadingState loading_state = WAITING;
  int frame_counter = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    switch (loading_state) {
      case WAITING: {
        if (IsKeyPressed(KEY_ENTER)) {
          int error = pthread_create(&thread_id, NULL, load_data_thread, NULL);
          if (error != 0) TraceLog(LOG_ERROR, "Error creating loading thread");
          else TraceLog(LOG_INFO, "Loading thread initialized successfully");
          loading_state = LOADING;
        }
      } break;
      case LOADING: {
        frame_counter += 1;
        if (atomic_load_explicit(&data_loaded, memory_order_relaxed)) {
          frame_counter = 0;
          int error = pthread_join(thread_id, NULL);
          if (error != 0) TraceLog(LOG_ERROR, "Error joining loading thread");
          else TraceLog(LOG_INFO, "Loading thread terminated successfully");
          loading_state = FINISHED;
        }
      } break;
      case FINISHED: {
        if (IsKeyPressed(KEY_ENTER)) {
          atomic_store_explicit(&data_loaded, false, memory_order_relaxed);
          atomic_store_explicit(&data_progress, 0, memory_order_relaxed);
          loading_state = WAITING;
        }
      } break;
      default: break;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (loading_state) {
      case WAITING: DrawText("PRESS ENTER TO START LOADING DATA", 150, 170, 20, DARKGRAY); break;
      case LOADING: {
        DrawRectangle(150, 200, atomic_load_explicit(&data_progress, memory_order_relaxed), 60, SKYBLUE);
        if ((frame_counter/15)%2) DrawText("LOADING DATA...", 240, 210, 40, DARKBLUE);
      } break;
      case FINISHED: {
        DrawRectangle(150, 200, 500, 60, LIME);
        DrawText("DATA LOADED!", 250, 210, 40, GREEN);
      } break;
      default: break;
    }
    DrawRectangleLines(150, 200, 500, 60, DARKGRAY);
    EndDrawing();
  }

  CloseWindow();
}

static void* load_data_thread(void* arg) {
  int time_counter = 0;
  clock_t prev_time = clock();

  while (time_counter < 5000) {
    clock_t current_time = clock() - prev_time;
    time_counter = current_time * 1000 / CLOCKS_PER_SEC;

    atomic_store_explicit(&data_progress, time_counter/10, memory_order_relaxed);
  }

  atomic_store_explicit(&data_loaded, true, memory_order_relaxed);
  return NULL;
}