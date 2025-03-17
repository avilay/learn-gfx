//
// Created by avilay on 11/26/24.
//
#include <stdio.h>
#include <raylib.h>

void background_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Background Demo");

  // Ensure that all the textures are wider than the screen width
  // background is 512 x 192
  const Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");
  float scrolling_back = 0.0f;
  printf("background: %d x %d\n", background.width, background.height);

  // midground is 512 x 192
  const Texture2D midground = LoadTexture("resources/cyberpunk_street_midground.png");
  float scrolling_mid = 0.0f;
  printf("midground: %d x %d\n", midground.width, midground.height);

  // foreground is 704 x 192
  const Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");
  float scrolling_fore = 0.0f;
  printf("foreground: %d x %d\n", foreground.width, foreground.height);

  SetTargetFPS(1);

  while (!WindowShouldClose()) {
    scrolling_back -= 0.01f;
    scrolling_mid -= 0.5f;
    scrolling_fore -= 1.0f;

    // All the textures will be scaled to 2x which is why the width is multiplied by 2
    if (scrolling_back <= (float)-background.width * 2) scrolling_back = 0;
    if (scrolling_mid <= (float)-midground.width * 2) scrolling_mid = 0;
    if (scrolling_fore <= (float)-foreground.width * 2) scrolling_fore = 0;

    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));

    // Stitch two copies of the texture one after the other (along the positive x-axis)
    // Each copy is scaled by 2x
    DrawTextureEx(
      background,
      (Vector2){.x=scrolling_back, 20},
      0.0f,
      2.0f,
      WHITE
    );

    float ext_scrolling_back = (float)background.width * 2 + scrolling_back;
    DrawTextureEx(
      background,
      (Vector2){.x=ext_scrolling_back, .y=20},
      0.0f,
      2.0f,
      WHITE
    );

    printf("background args: scrolling_back=%0.3f, ext scrolling_back=%0.3f\n", scrolling_back, ext_scrolling_back);

    DrawTextureEx(
      midground,
      (Vector2){.x=scrolling_mid, .y=20},
      0.0f,
      2.0f,
      WHITE
    );
    DrawTextureEx(
      midground,
      (Vector2){.x=(float)midground.width * 2 + scrolling_mid, .y=20},
      0.0f,
      2.0f,
      WHITE
    );

    DrawTextureEx(
      foreground,
      (Vector2){.x=scrolling_fore, .y=70},
      0.0f,
      2.0f,
      WHITE
    );
    DrawTextureEx(
      foreground,
      (Vector2){.x=(float)foreground.width * 2 + scrolling_fore, .y=70},
      0.0f,
      2.0f,
      WHITE
    );
    EndDrawing();
  }

  UnloadTexture(background);
  UnloadTexture(midground);
  UnloadTexture(foreground);

  CloseWindow();
}
