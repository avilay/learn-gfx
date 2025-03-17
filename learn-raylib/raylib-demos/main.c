#include "demos.h"
#include <stdio.h>
#include <stdlib.h>

typedef void (*Demo)(void);

void print_usage() {
  puts("Usage: raylib-demos [1-10]\n");
  puts("1: log demo");
  puts("2: collision demo");
  puts("3: gesture demo");
  puts("4: screen demo");
  puts("5: loading therad demo");
  puts("6: background demo");
  puts("7: camera demo");
  puts("8: user input demo");
  puts("9: texture demo");
  puts("10: raw texture demo");
  puts("11: anim demo");
  puts("12: button demo");
  puts("13: explosion demo");
}

int main(const int argc, char* argv[]) {
  if (argc < 2) {
    print_usage();
    return 1;
  }

  const Demo demos[] = {
    log_demo,
    collision_demo,
    gesture_demo,
    screen_demo,
    loading_thread_demo,
    background_demo,
    camera_demo,
    user_input_demo,
    texture_demo,
    raw_texture_demo,
    anim_demo,
    button_demo,
    explosion_demo
  };

  const int choice = strtol(argv[1], NULL, 10);
  if (choice < 0 || choice > 13) {
    print_usage();
    return 1;
  }
  demos[choice-1]();
  return 0;
}
