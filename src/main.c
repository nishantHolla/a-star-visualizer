#include "asv.h"

int main(void) {

  // Init game

  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "A* Visualizer");
  SetTargetFPS(60);

  asv_init_grid();
  asv_init_status();
  asv_ui_init_fonts();

  // Game loop

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(ASV_UI_WINDOW_BG_COLOR);

    asv_ui_calculate();
    asv_ui_draw_containers();
    asv_ui_draw_text();
    asv_ui_draw_grid();

    EndDrawing();
  }

  // Clean game

  CloseWindow();
  asv_ui_free_fonts();
  asv_free_grid();

  return 0;
}
