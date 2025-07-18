#include "asv.h"

// UI Assets

const char *ASV_UI_FONT_PATH = "assets/romulus.png";

// UI Fonts

Font fonts[MAX_FONTS] = {0};

// UI Colors

const Color ASV_UI_WINDOW_BG_COLOR = { .r = 9, .g = 9, .b = 11, .a = 255 };
const Color ASV_UI_CONTAINER_BG_COLOR = { .r = 39, .g = 39, .b = 42, .a = 255 };

const Color ASV_UI_TEXT_COLOR = { .r = 212, .g = 212, .b = 216, .a = 255 };
const Color ASV_UI_TEXT_WARNING_COLOR = { .r = 251, .g = 191, .b = 36, .a = 255 };
const Color ASV_UI_TEXT_ERROR_COLOR = { .r = 248, .g = 113, .b = 113, .a = 255 };
const Color ASV_UI_TEXT_SUCCESS_COLOR = { .r = 74, .g = 222, .b = 128, .a = 255 };

const Color ASV_UI_CELL_FREE_COLOR = { .r = 115, .g = 115, .b = 115, .a = 255 };
const Color ASV_UI_CELL_VISITED_COLOR = { .r = 251, .g = 113, .b = 133, .a = 255};
const Color ASV_UI_CELL_RESULT_COLOR = { .r = 74, .g = 222, .b = 128, .a = 255};
const Color ASV_UI_CELL_OBSTACLE_COLOR = { .r = 0, .g = 0, .b = 0, .a = 255};
const Color ASV_UI_CELL_SOURCE_COLOR = { .r = 167, .g = 139, .b = 250, .a = 255};
const Color ASV_UI_CELL_DESTINATION_COLOR = { .r = 251, .g = 191, .b = 36, .a = 255};

const Color ASV_UI_SELECTED_ITEM_COLOR = { .r = 251, .g = 146, .b = 60, .a = 255};
const Color ASV_UI_SELECTED_TOOL_COLOR = { .r = 34, .g = 211, .b = 238, .a = 255};

const Color ASV_UI_DISABLED_COLOR = { .r = 163, .g = 163, .b = 163, .a = 255 };

// UI Values

const float ASV_UI_ROUNDNESS_LG = 0.05f;
const float ASV_UI_ROUNDNESS_SM = 0.01f;

const float ASV_UI_TEXT_SIZE_XL = 5.0f;
const float ASV_UI_TEXT_SPACING_XL = 8.0f;
const float ASV_UI_TEXT_SIZE_MD = 3.0f;
const float ASV_UI_TEXT_SPACING_MD = 4.0f;
const float ASV_UI_TEXT_SIZE_SM = 2.5f;
const float ASV_UI_TEXT_SPACING_SM = 1.0f;

const float ASV_UI_TEXT_ITEM_SIZE = ASV_UI_TEXT_SIZE_SM;
const float ASV_UI_TEXT_ITEM_SPACING = ASV_UI_TEXT_SPACING_SM;

const float ASV_UI_TEXT_TOOL_SIZE = ASV_UI_TEXT_SIZE_SM;
const float ASV_UI_TEXT_TOOL_SPACING = ASV_UI_TEXT_SPACING_SM;

const float ASV_UI_TEXT_ACTION_SIZE = ASV_UI_TEXT_SIZE_SM;
const float ASV_UI_TEXT_ACTION_SPACING = ASV_UI_TEXT_SPACING_SM;

const Vector2 ASV_UI_WINDOW_PADDING = { .x = 20.0f, .y = 20.0f };

const Vector2 ASV_UI_CONTAINER_PADDING = { .x = 20.0f, .y = 10.0f };
const Vector2 ASV_UI_CONTAINER_SPACING = { .x = 20.0f, .y = 20.0f };

const Vector2 ASV_UI_GRID_PADDING = { .x = 12.0f, .y = 7.0f };
const Vector2 ASV_UI_GRID_SPACING = { .x = 7.0f, .y = 7.0f };

const Vector2 ASV_UI_ITEMS_SPACING = { .x = 30.0f, .y = 0.0f };
const Vector2 ASV_UI_TOOLS_SPACING = { .x = 30.0f, .y = 0.0f };
const Vector2 ASV_UI_ACTIONS_SPACING = { .x = 30.0f, .y = 0.0f };

// UI Elements

Rectangle asv_ui_menu_bar;
Rectangle asv_ui_status_bar;
Rectangle asv_ui_grid;
Rectangle asv_ui_obstacles_button;
Rectangle asv_ui_source_button;
Rectangle asv_ui_destination_button;
Rectangle asv_ui_add_button;
Rectangle asv_ui_remove_button;
Rectangle asv_ui_speed_button;
Rectangle asv_ui_play_button;
Rectangle asv_ui_reset_button;
Rectangle asv_ui_clear_button;

Vector2 asv_ui_title_text;
Vector2 asv_ui_cell;
Vector2 asv_ui_status_position;

// UI Functions

void asv_ui_init_fonts(void) {
  fonts[0] = LoadFont(ASV_UI_FONT_PATH);
}

void asv_ui_calculate(void) {

  asv_ui_status_bar = (Rectangle) {
    .x = ASV_UI_WINDOW_PADDING.x,
    .y = ASV_UI_WINDOW_PADDING.y,
    .width = GetScreenWidth() - (2 * ASV_UI_WINDOW_PADDING.x),
    .height = 80.0f
  };

  asv_ui_menu_bar = (Rectangle) {
    .x = ASV_UI_WINDOW_PADDING.x,
    .y = GetScreenHeight() - ASV_UI_WINDOW_PADDING.y - 80.0f,
    .width = GetScreenWidth() - (2 * ASV_UI_WINDOW_PADDING.x),
    .height = 80.0f
  };

  asv_ui_grid = (Rectangle) {
    .x = ASV_UI_WINDOW_PADDING.x,
    .y = asv_ui_menu_bar.height + ASV_UI_WINDOW_PADDING.y + ASV_UI_CONTAINER_SPACING.y,
    .width = GetScreenWidth() - (2 * ASV_UI_WINDOW_PADDING.x),
    .height = GetScreenHeight() - (2 * ASV_UI_CONTAINER_SPACING.y) - (2 * ASV_UI_WINDOW_PADDING.y) - asv_ui_menu_bar.height - asv_ui_status_bar.height
  };

  asv_ui_title_text = (Vector2) {
    .x = ASV_UI_WINDOW_PADDING.x + ASV_UI_CONTAINER_PADDING.x,
    .y = ASV_UI_WINDOW_PADDING.y + ASV_UI_CONTAINER_PADDING.y,
  };

  asv_ui_cell = (Vector2) {
    .x = (asv_ui_grid.width - ASV_UI_CONTAINER_PADDING.x - (ASV_UI_GRID_SPACING.x * ASV_GRID_COLUMN_COUNT)) / ASV_GRID_COLUMN_COUNT,
    .y = (asv_ui_grid.height - ASV_UI_CONTAINER_PADDING.y - (ASV_UI_GRID_SPACING.y * ASV_GRID_ROW_COUNT)) / ASV_GRID_ROW_COUNT,
  };

  Vector2 status_measure = MeasureTextEx(fonts[0], asv_app_status.message, fonts[0].baseSize * ASV_UI_TEXT_SIZE_MD, ASV_UI_TEXT_SPACING_MD);
  asv_ui_status_position = (Vector2) {
    .x = (asv_ui_status_bar.x + asv_ui_status_bar.width) - status_measure.x - ASV_UI_CONTAINER_PADDING.x,
    /*.y = asv_ui_status_bar.y + ((asv_ui_status_bar.height - status_measure.y) / 2)*/
    .y = V_CENTER(asv_ui_status_bar,status_measure)
  };

  Vector2 obstacle_measure = MeasureTextEx(fonts[0], OBSTACLES_TEXT, fonts[0].baseSize * ASV_UI_TEXT_ITEM_SIZE, ASV_UI_TEXT_ITEM_SPACING);
  asv_ui_obstacles_button = (Rectangle) {
    .x = asv_ui_menu_bar.x + ASV_UI_CONTAINER_PADDING.x,
    .y = V_CENTER(asv_ui_menu_bar,obstacle_measure),
    .width = obstacle_measure.x,
    .height = obstacle_measure.y
  };

  Vector2 source_measure = MeasureTextEx(fonts[0], SOURCE_TEXT, fonts[0].baseSize * ASV_UI_TEXT_ITEM_SIZE, ASV_UI_TEXT_ITEM_SPACING);
  asv_ui_source_button = (Rectangle) {
    .x = asv_ui_obstacles_button.x + asv_ui_obstacles_button.width + ASV_UI_ITEMS_SPACING.x,
    .y = V_CENTER(asv_ui_menu_bar,source_measure),
    .width = source_measure.x,
    .height = source_measure.y
  };

  Vector2 destination_measure = MeasureTextEx(fonts[0], DESTINATION_TEXT, fonts[0].baseSize * ASV_UI_TEXT_ITEM_SIZE, ASV_UI_TEXT_ITEM_SPACING);
  asv_ui_destination_button = (Rectangle) {
    .x = asv_ui_source_button.x + asv_ui_source_button.width + ASV_UI_ITEMS_SPACING.x,
    .y = V_CENTER(asv_ui_menu_bar,destination_measure),
    .width = destination_measure.x,
    .height = destination_measure.y
  };

  Vector2 add_measure = MeasureTextEx(fonts[0], ADD_TEXT, fonts[0].baseSize * ASV_UI_TEXT_TOOL_SIZE, ASV_UI_TEXT_TOOL_SPACING);
  Vector2 remove_measure = MeasureTextEx(fonts[0], REMOVE_TEXT, fonts[0].baseSize * ASV_UI_TEXT_TOOL_SIZE, ASV_UI_TEXT_TOOL_SPACING);
  Vector2 toolbar_measure = {
    .x = (asv_ui_menu_bar.width/2) - ((add_measure.x + remove_measure.x + ASV_UI_TOOLS_SPACING.x)/2),
    .y = (add_measure.y +remove_measure.y) / 2
  };
  asv_ui_add_button = (Rectangle) {
    .x = toolbar_measure.x,
    .y = V_CENTER(asv_ui_menu_bar,toolbar_measure),
    .width = add_measure.x,
    .height = add_measure.y
  };
  asv_ui_remove_button = (Rectangle) {
    .x = asv_ui_add_button.x + asv_ui_add_button.width + ASV_UI_TOOLS_SPACING.x,
    .y = V_CENTER(asv_ui_menu_bar,toolbar_measure),
    .width = remove_measure.x,
    .height = remove_measure.y
  };

  Vector2 clear_measure = MeasureTextEx(fonts[0], CLEAR_TEXT, fonts[0].baseSize * ASV_UI_TEXT_ACTION_SIZE, ASV_UI_TEXT_ACTION_SPACING);
  asv_ui_clear_button = (Rectangle) {
    .x = (asv_ui_menu_bar.x + asv_ui_menu_bar.width) - ASV_UI_CONTAINER_PADDING.x - clear_measure.x,
    .y = V_CENTER(asv_ui_menu_bar,clear_measure),
    .width = clear_measure.x,
    .height = clear_measure.y
  };

  Vector2 reset_measure = MeasureTextEx(fonts[0], RESET_TEXT, fonts[0].baseSize * ASV_UI_TEXT_ACTION_SIZE, ASV_UI_TEXT_ACTION_SPACING);
  asv_ui_reset_button = (Rectangle) {
    .x = asv_ui_clear_button.x - ASV_UI_ACTIONS_SPACING.x - reset_measure.x,
    .y = V_CENTER(asv_ui_menu_bar,reset_measure),
    .width = reset_measure.x,
    .height = reset_measure.y
  };

  Vector2 play_measure = MeasureTextEx(fonts[0], asv_app_state == ASV_STATE_PLAYING ? PAUSE_TEXT : PLAY_TEXT, fonts[0].baseSize * ASV_UI_TEXT_ACTION_SIZE, ASV_UI_TEXT_ACTION_SPACING);
  asv_ui_play_button = (Rectangle) {
    .x = asv_ui_reset_button.x - ASV_UI_ACTIONS_SPACING.x - play_measure.x,
    .y = V_CENTER(asv_ui_menu_bar,play_measure),
    .width = play_measure.x,
    .height = play_measure.y
  };

  char speed_text[100];
  asv_ui_get_speed_text(asv_speed_selected, speed_text);
  Vector2 speed_measure = MeasureTextEx(fonts[0], speed_text, fonts[0].baseSize * ASV_UI_TEXT_ACTION_SIZE, ASV_UI_TEXT_ACTION_SPACING);
  asv_ui_speed_button = (Rectangle) {
    .x = asv_ui_play_button.x - ASV_UI_ACTIONS_SPACING.x - speed_measure.x,
    .y = V_CENTER(asv_ui_menu_bar,speed_measure),
    .width = speed_measure.x,
    .height = speed_measure.y
  };
}

Color asv_ui_get_status_color(void) {
  switch (asv_app_status.message_type) {
    case (ASV_MESSAGE_NORMAL):
      return ASV_UI_TEXT_COLOR;

    case (ASV_MESSAGE_WARNING):
      return ASV_UI_TEXT_WARNING_COLOR;

    case (ASV_MESSAGE_ERROR):
      return ASV_UI_TEXT_ERROR_COLOR;

    case (ASV_MESSAGE_SUCCESS):
      return ASV_UI_TEXT_SUCCESS_COLOR;

    default:
      return ASV_UI_TEXT_COLOR;
  }
}

Color asv_ui_get_cell_color(int column_index, int row_index) {
  switch (asv_grid[column_index][row_index]) {
    case (ASV_CELL_FREE):
      return ASV_UI_CELL_FREE_COLOR;

    case (ASV_CELL_OBSTACLE):
      return ASV_UI_CELL_OBSTACLE_COLOR;

    case (ASV_CELL_SOURCE):
      return ASV_UI_CELL_SOURCE_COLOR;

    case (ASV_CELL_DESTINATION):
      return ASV_UI_CELL_DESTINATION_COLOR;

    case (ASV_CELL_VISITED):
      return ASV_UI_CELL_VISITED_COLOR;

    case (ASV_CELL_RESULT):
      return ASV_UI_CELL_RESULT_COLOR;

    default:
      return ASV_UI_CELL_FREE_COLOR;
  }
}

Color asv_ui_get_item_color(asv_item_select item) {
  if (asv_app_state != ASV_STATE_IDLE) {
    return ASV_UI_DISABLED_COLOR;
  }

  if (asv_item_selected == item) {
    return ASV_UI_SELECTED_ITEM_COLOR;
  }

  return ASV_UI_TEXT_COLOR;
}

Color asv_ui_get_tool_color(asv_tool_select tool) {
  if (asv_app_state != ASV_STATE_IDLE) {
    return ASV_UI_DISABLED_COLOR;
  }

  if (asv_tool_selected == tool) {
    return ASV_UI_SELECTED_TOOL_COLOR;
  }

  return ASV_UI_TEXT_COLOR;
}

void asv_ui_get_speed_text(asv_speed_select speed, char *text) {
  strncpy(text, SPEED_PRETEXT, 20);

  switch (speed) {
    case ASV_SPEED_SELECT_INSTANT:
      strncat(text, SPEED_INSTANT_TEXT, 20);
      return;

    case ASV_SPEED_SELECT_FAST:
      strncat(text, SPEED_FAST_TEXT, 20);
      return;

    case ASV_SPEED_SELECT_MEDIUM:
      strncat(text, SPEED_MEDIUM_TEXT, 20);
      return;

    case ASV_SPEED_SELECT_SLOW:
      strncat(text, SPEED_SLOW_TEXT, 20);
      return;

    default:
      strncat(text, SPEED_MEDIUM_TEXT, 20);
      return;
  }
}

void asv_ui_draw_containers(void) {
  DrawRectangleRounded(asv_ui_status_bar, ASV_UI_ROUNDNESS_LG, 0, ASV_UI_CONTAINER_BG_COLOR);
  DrawRectangleRounded(asv_ui_grid, ASV_UI_ROUNDNESS_SM, 0, ASV_UI_CONTAINER_BG_COLOR);
  DrawRectangleRounded(asv_ui_menu_bar, ASV_UI_ROUNDNESS_LG, 0, ASV_UI_CONTAINER_BG_COLOR);
}

void asv_ui_draw_text(void) {
  char speed_text[100];
  asv_ui_get_speed_text(asv_speed_selected, speed_text);

  DrawTextEx(fonts[0], APP_TITLE, asv_ui_title_text, fonts[0].baseSize * ASV_UI_TEXT_SIZE_XL, ASV_UI_TEXT_SPACING_XL, ASV_UI_TEXT_COLOR);
  DrawTextEx(fonts[0], asv_app_status.message, asv_ui_status_position, fonts[0].baseSize * ASV_UI_TEXT_SIZE_MD, ASV_UI_TEXT_SPACING_MD, asv_ui_get_status_color());
  DrawTextEx(fonts[0], OBSTACLES_TEXT, REC2VEC(asv_ui_obstacles_button), fonts[0].baseSize * ASV_UI_TEXT_ITEM_SIZE, ASV_UI_TEXT_ITEM_SPACING, asv_ui_get_item_color(ASV_ITEM_SELECT_OBSTACLES));
  DrawTextEx(fonts[0], SOURCE_TEXT, REC2VEC(asv_ui_source_button), fonts[0].baseSize * ASV_UI_TEXT_ITEM_SIZE, ASV_UI_TEXT_ITEM_SPACING, asv_ui_get_item_color(ASV_ITEM_SELECT_SOURCE));
  DrawTextEx(fonts[0], DESTINATION_TEXT, REC2VEC(asv_ui_destination_button), fonts[0].baseSize * ASV_UI_TEXT_ITEM_SIZE, ASV_UI_TEXT_ITEM_SPACING, asv_ui_get_item_color(ASV_ITEM_SELECT_DESTINATION));
  DrawTextEx(fonts[0], ADD_TEXT, REC2VEC(asv_ui_add_button), fonts[0].baseSize * ASV_UI_TEXT_TOOL_SIZE, ASV_UI_TEXT_TOOL_SPACING, asv_ui_get_tool_color(ASV_TOOL_SELECT_ADD));
  DrawTextEx(fonts[0], REMOVE_TEXT, REC2VEC(asv_ui_remove_button), fonts[0].baseSize * ASV_UI_TEXT_TOOL_SIZE, ASV_UI_TEXT_TOOL_SPACING, asv_ui_get_tool_color(ASV_TOOL_SELECT_REMOVE));
  DrawTextEx(fonts[0], CLEAR_TEXT, REC2VEC(asv_ui_clear_button), fonts[0].baseSize * ASV_UI_TEXT_ACTION_SIZE, ASV_UI_TEXT_ACTION_SPACING, ASV_UI_TEXT_COLOR);
  DrawTextEx(fonts[0], RESET_TEXT, REC2VEC(asv_ui_reset_button), fonts[0].baseSize * ASV_UI_TEXT_ACTION_SIZE, ASV_UI_TEXT_ACTION_SPACING, ASV_UI_TEXT_COLOR);
  DrawTextEx(fonts[0], asv_app_state == ASV_STATE_PLAYING ? PAUSE_TEXT : PLAY_TEXT, REC2VEC(asv_ui_play_button), fonts[0].baseSize * ASV_UI_TEXT_ACTION_SIZE, ASV_UI_TEXT_ACTION_SPACING, ASV_UI_TEXT_COLOR);
  DrawTextEx(fonts[0], speed_text, REC2VEC(asv_ui_speed_button), fonts[0].baseSize * ASV_UI_TEXT_ACTION_SIZE, ASV_UI_TEXT_ACTION_SPACING, ASV_UI_TEXT_COLOR);
}

void asv_ui_draw_grid(void) {
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    for (int j = 0; j < ASV_GRID_ROW_COUNT; j++) {
      Rectangle cell = {
        .x = asv_ui_grid.x + ASV_UI_GRID_PADDING.x + (i * ASV_UI_GRID_SPACING.x) + (i * asv_ui_cell.x),
        .y = asv_ui_grid.y + ASV_UI_GRID_PADDING.y + (j * ASV_UI_GRID_SPACING.y) + (j * asv_ui_cell.y),
        .width = asv_ui_cell.x,
        .height = asv_ui_cell.y
      };
      DrawRectangleRounded(cell, 0.15f, 0, asv_ui_get_cell_color(i, j));
    }
  }
}

void asv_ui_free_fonts(void) {
  for (int i = 0; i < MAX_FONTS; i++) {
    UnloadFont(fonts[i]);
  }
}
