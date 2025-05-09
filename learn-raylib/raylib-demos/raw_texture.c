//
// Created by avilay on 11/29/24.
//
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

void raw_texture_demo() {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "texture from raw data");

  Image fudesumi_raw = LoadImageRaw("./resources/fudesumi.raw", 384, 512, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 0);
  Texture2D fudesumi = LoadTextureFromImage(fudesumi_raw);
  UnloadImage(fudesumi_raw);

  int width = 960;
  int height = 480;

  // pixels in row-major format
  Color* pixels = malloc(width*height*sizeof(Color));
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      // 32+32 pixels are alteratingly orange and gold
      if ((x/32 + y/32) % 2 ==0) pixels[y*width + x] = ORANGE;
      else pixels[y*width + x] = GOLD;
    }
  }

  Image checked_img = {
    .data=pixels,
    .width=width,
    .height=height,
    .format=PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
    .mipmaps=1
  };
  Texture2D checked = LoadTextureFromImage(checked_img);
  UnloadImage(checked_img);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    DrawTexture(checked, screen_width/2 - checked.width/2, screen_height/2 - checked.height/2, Fade(WHITE, 0.5f));
    DrawTexture(fudesumi, 430, -30, WHITE);

    DrawText("CHECKED TEXTURE", 84, 85, 30, BROWN);
    DrawText("GENERATED by CODE", 72, 148, 30, BROWN);
    DrawText("and RAW IMAGE LOADING", 46, 210, 30, BROWN);

    DrawText("(c) Fudesumi sprite by Eiden Marsal", 310, screen_height-20, 10, BROWN);
    EndDrawing();
  }

  UnloadTexture(fudesumi);
  UnloadTexture(checked);
  free(pixels);

  CloseWindow();
}
