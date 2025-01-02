#include "asv.h"

int main(void) {

  // Init game

  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "A* Visualizer");
  SetTargetFPS(60);

  // Game loop

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(ASV_UI_WINDOW_BG_COLOR);

    asv_ui_calculate();
    asv_ui_draw_containers();

    EndDrawing();
  }

  // Clean game

  CloseWindow();

  return 0;
}
