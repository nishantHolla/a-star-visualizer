#include <stdio.h>

#include "raylib.h"
#include "asv.h"

int main(void) {

  // Init game

  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "A* Visualizer");
  SetTargetFPS(60);

  // Game loop

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  // Clean game

  CloseWindow();

  return 0;
}
