#include "asv.h"

int main(void) {

  // Init game

  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "A* Visualizer");
  SetTargetFPS(60);

  asv_init_grid();
  asv_init_status();
  asv_init_items();
  asv_init_tools();
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

    Vector2 MousePoint = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (CheckCollisionPointRec(MousePoint, asv_ui_obstacles_button)) {
        asv_select_item(ASV_ITEM_SELECT_OBSTACLES);
        asv_item_selected = ASV_ITEM_SELECT_OBSTACLES;
      }
      else if (CheckCollisionPointRec(MousePoint, asv_ui_source_button)) {
        asv_select_item(ASV_ITEM_SELECT_SOURCE);
      }
      else if (CheckCollisionPointRec(MousePoint, asv_ui_destination_button)) {
        asv_select_item(ASV_ITEM_SELECT_DESTINATION);
      }
      else if (CheckCollisionPointRec(MousePoint, asv_ui_add_button)) {
        asv_select_tool(ASV_TOOL_SELECT_ADD);
      }
      else if (CheckCollisionPointRec(MousePoint, asv_ui_remove_button)) {
        asv_select_tool(ASV_TOOL_SELECT_REMOVE);
      }
    }
  }

  // Clean game

  CloseWindow();
  asv_ui_free_fonts();
  asv_free_grid();

  return 0;
}
