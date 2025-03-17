#include <stdio.h>
#include <raylib.h>
#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

const int screen_width = 800;
const int screen_height = 450;

// Ensure that all the textures are wider than the screen width
// background is 512 x 192
Texture2D background;
float scrolling_back = 0.0f;

// midground is 512 x 192
Texture2D midground;
float scrolling_mid = 0.0f;

// foreground is 704 x 192
Texture2D foreground;
float scrolling_fore = 0.0f;

void update_draw_frame();

void load_textures();

int main() {
  InitWindow(screen_width, screen_height, "Background Demo");
  load_textures();
#ifdef PLATFORM_WEB
  puts("APTG DEBUG: platform web is defined");
  emscripten_set_main_loop(update_draw_frame, 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    update_draw_frame();
  }

  CloseWindow();
#endif

  UnloadTexture(background);
  UnloadTexture(midground);
  UnloadTexture(foreground);

  return 0;
}

void load_textures() {
  background = LoadTexture("/home/avilay/projects/bitbucket/learn/learn-gfx/learn-raylib/web/resources/cyberpunk_street_background.png");
  midground = LoadTexture("/home/avilay/projects/bitbucket/learn/learn-gfx/learn-raylib/web/resources/cyberpunk_street_midground.png");
  foreground = LoadTexture("/home/avilay/projects/bitbucket/learn/learn-gfx/learn-raylib/web/resources/cyberpunk_street_foreground.png");
}

void update_draw_frame() {
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
  DrawTextureEx(
    background,
    (Vector2){.x=(float)background.width * 2 + scrolling_back, .y=20},
    0.0f,
    2.0f,
    WHITE
  );

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