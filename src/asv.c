#include "asv.h"

const int ASV_GRID_ROW_COUNT = 20;
const int ASV_GRID_COLUMN_COUNT = 40;
asv_cell_state **asv_grid = NULL;
asv_status asv_app_status;
asv_state asv_app_state;
asv_item_select asv_item_selected;
asv_tool_select asv_tool_selected;
Vector2 asv_source_cell;
Vector2 asv_destination_cell;

void asv_init_grid() {
  asv_grid = (asv_cell_state **) malloc(ASV_GRID_COLUMN_COUNT * sizeof(asv_cell_state *));
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    asv_grid[i] = (asv_cell_state *) malloc(ASV_GRID_ROW_COUNT * sizeof(asv_cell_state));
    for (int j = 0; j < ASV_GRID_ROW_COUNT; j++) {
      asv_grid[i][j] =ASV_CELL_FREE;
    }
  }
}

void asv_init_state() {
  asv_set_state(ASV_STATE_IDLE);
}

void asv_init_status() {
  asv_set_status(OBSTACLES_STATUS_TEXT, ASV_MESSAGE_NORMAL);
}

void asv_init_items() {
  asv_select_item(ASV_ITEM_SELECT_OBSTACLES);
}

void asv_init_tools() {
  asv_select_tool(ASV_TOOL_SELECT_ADD);
}

void asv_init_cells() {
  asv_source_cell = (Vector2) { .x = -1, .y = -1};
  asv_destination_cell = (Vector2) { .x = -1, .y = -1};
}

void asv_set_state(asv_state state) {
  asv_app_state = state;
}

void asv_set_status(const char *message, asv_message_type type) {
  asv_app_status.message_type = type;
  strncpy(asv_app_status.message, message, MAX_MESSAGE_LENGTH);
}

void asv_select_item(asv_item_select item) {
  asv_item_selected = item;

  if (item == ASV_ITEM_SELECT_OBSTACLES) {
    asv_set_status(OBSTACLES_STATUS_TEXT, ASV_MESSAGE_NORMAL);
  }
  else if (item == ASV_ITEM_SELECT_SOURCE) {
    asv_set_status(SOURCE_STATUS_TEXT, ASV_MESSAGE_NORMAL);
  }
  else if (item == ASV_ITEM_SELECT_DESTINATION) {
    asv_set_status(DESTINATION_STATUS_TEXT, ASV_MESSAGE_NORMAL);
  }
}

void asv_select_tool(asv_tool_select tool) {
  asv_tool_selected = tool;
}

void asv_select_cell(int column_index, int row_index) {
  switch (asv_item_selected) {
    case (ASV_ITEM_SELECT_OBSTACLES):
      if (asv_tool_selected == ASV_TOOL_SELECT_ADD) {
        asv_grid[column_index][row_index] = ASV_CELL_OBSTACLE;
      }
      else if (asv_tool_selected == ASV_TOOL_SELECT_REMOVE && asv_grid[column_index][row_index] == ASV_CELL_OBSTACLE) {
        asv_grid[column_index][row_index] = ASV_CELL_FREE;
      }
      break;

    case (ASV_ITEM_SELECT_SOURCE):
      if (asv_tool_selected == ASV_TOOL_SELECT_ADD && asv_source_cell.x == -1) {
        asv_grid[column_index][row_index] = ASV_CELL_SOURCE;
        asv_source_cell = (Vector2) { .x = column_index, .y = row_index};
      }
      else if (asv_tool_selected == ASV_TOOL_SELECT_REMOVE && asv_grid[column_index][row_index] == ASV_CELL_SOURCE) {
        asv_grid[column_index][row_index] = ASV_CELL_FREE;
        asv_source_cell = (Vector2) { .x = -1, .y = -1};
      }
      break;

    case (ASV_ITEM_SELECT_DESTINATION):
      if (asv_tool_selected == ASV_TOOL_SELECT_ADD && asv_destination_cell.x == -1) {
        asv_grid[column_index][row_index] = ASV_CELL_DESTINATION;
        asv_destination_cell = (Vector2) { .x = column_index, .y = row_index};
      }
      else if (asv_tool_selected == ASV_TOOL_SELECT_REMOVE && asv_grid[column_index][row_index] == ASV_CELL_DESTINATION) {
        asv_grid[column_index][row_index] = ASV_CELL_FREE;
        asv_destination_cell = (Vector2) { .x = -1, .y = -1};
      }
      break;

    default:
      break;
  }
}

void asv_clear() {
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    for (int j = 0; j < ASV_GRID_ROW_COUNT; j++) {
      asv_grid[i][j] = ASV_CELL_FREE;
    }
  }

  asv_select_tool(ASV_TOOL_SELECT_ADD);
  asv_select_item(ASV_ITEM_SELECT_OBSTACLES);
}

void asv_reset() {
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    for (int j = 0; j < ASV_GRID_ROW_COUNT; j++) {
      if (asv_grid[i][j] == ASV_CELL_VISITED) {
        asv_grid[i][j] = ASV_CELL_FREE;
      }
    }
  }

  asv_select_tool(ASV_TOOL_SELECT_ADD);
  asv_select_item(ASV_ITEM_SELECT_OBSTACLES);
}

void asv_free_grid() {
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    free(asv_grid[i]);
  }
  free(asv_grid);
}
