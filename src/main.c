#include "asv.h"

int main(void) {

  // Init game

  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "A* Visualizer");
  SetTargetFPS(60);

  asv_init_grid();
  asv_init_state();
  asv_init_status();
  asv_init_items();
  asv_init_tools();
  asv_init_speed();
  asv_init_cells();
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

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      if (CheckCollisionPointRec(MousePoint, asv_ui_grid)) {
        int mx = MousePoint.x - asv_ui_grid.x - ASV_UI_GRID_PADDING.x;
        int my = MousePoint.y - asv_ui_grid.y - ASV_UI_GRID_PADDING.y;
        mx = mx < 0 ? 0 : mx;
        my = my < 0 ? 0 : my;
        int column_index = mx / (asv_ui_cell.x + ASV_UI_GRID_SPACING.x);
        int row_index = my / (asv_ui_cell.y + ASV_UI_GRID_SPACING.y);
        asv_select_cell(column_index, row_index);
      }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (CheckCollisionPointRec(MousePoint, asv_ui_obstacles_button)) {
        asv_select_item(ASV_ITEM_SELECT_OBSTACLES);
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
      else if (CheckCollisionPointRec(MousePoint, asv_ui_speed_button)) {
        asv_cycle_speed();
      }
      else if (CheckCollisionPointRec(MousePoint, asv_ui_play_button)) {
        asv_play();
      }
      else if (CheckCollisionPointRec(MousePoint, asv_ui_reset_button)) {
        asv_reset();
      }
      else if (CheckCollisionPointRec(MousePoint, asv_ui_clear_button)) {
        asv_clear();
      }
    }
  }

  // Clean game

  CloseWindow();
  asv_ui_free_fonts();
  if (asv_thread_created) {
    pthread_cancel(asv_thread);
    pthread_join(asv_thread, NULL);
  }
  asv_free_grid();

  return 0;
}
