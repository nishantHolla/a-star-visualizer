#include "asv.h"

// UI Assets

const char *ASV_UI_FONT_PATH = "assets/alpha_beta.png";

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

// UI Values

const float ASV_UI_ROUNDNESS_LG = 0.05f;
const float ASV_UI_ROUNDNESS_SM = 0.01f;

const float ASV_UI_TEXT_SIZE_XL = 5.0f;
const float ASV_UI_TEXT_SPACING_XL = 8.0f;
const float ASV_UI_TEXT_SIZE_MD = 3.0f;
const float ASV_UI_TEXT_SPACING_MD = 4.0f;

const Vector2 ASV_UI_WINDOW_PADDING = { .x = 20.0f, .y = 20.0f };

const Vector2 ASV_UI_CONTAINER_PADDING = { .x = 20.0f, .y = 10.0f };
const Vector2 ASV_UI_CONTAINER_SPACING = { .x = 20.0f, .y = 20.0f };

const Vector2 ASV_UI_GRID_PADDING = { .x = 12.0f, .y = 7.0f };
const Vector2 ASV_UI_GRID_SPACING = { .x = 7.0f, .y = 7.0f };

// UI Elements

Rectangle asv_ui_menu_bar;
Rectangle asv_ui_status_bar;
Rectangle asv_ui_grid;

Vector2 asv_ui_title_text;
Vector2 asv_ui_cell;
Vector2 asv_ui_status_position;

// UI Functions

void asv_ui_init_fonts() {
  fonts[0] = LoadFont(ASV_UI_FONT_PATH);
}

void asv_ui_calculate() {

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
    .y = asv_ui_status_bar.y + ((asv_ui_status_bar.height - status_measure.y) / 2)
  };
}

Color asv_ui_get_status_color() {
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

void asv_ui_draw_containers() {
  DrawRectangleRounded(asv_ui_status_bar, ASV_UI_ROUNDNESS_LG, 0, ASV_UI_CONTAINER_BG_COLOR);
  DrawRectangleRounded(asv_ui_grid, ASV_UI_ROUNDNESS_SM, 0, ASV_UI_CONTAINER_BG_COLOR);
  DrawRectangleRounded(asv_ui_menu_bar, ASV_UI_ROUNDNESS_LG, 0, ASV_UI_CONTAINER_BG_COLOR);
}

void asv_ui_draw_text() {
  DrawTextEx(fonts[0], APP_TITLE, asv_ui_title_text, fonts[0].baseSize * ASV_UI_TEXT_SIZE_XL, ASV_UI_TEXT_SPACING_XL, ASV_UI_TEXT_COLOR);
  DrawTextEx(fonts[0], asv_app_status.message, asv_ui_status_position, fonts[0].baseSize * ASV_UI_TEXT_SIZE_MD, ASV_UI_TEXT_SPACING_MD, asv_ui_get_status_color());
}

void asv_ui_draw_grid() {
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    for (int j = 0; j < ASV_GRID_ROW_COUNT; j++) {
      Rectangle cell = {
        .x = asv_ui_grid.x + ASV_UI_GRID_PADDING.x + (i * ASV_UI_GRID_SPACING.x) + (i * asv_ui_cell.x),
        .y = asv_ui_grid.y + ASV_UI_GRID_PADDING.y + (j * ASV_UI_GRID_SPACING.y) + (j * asv_ui_cell.y),
        .width = asv_ui_cell.x,
        .height = asv_ui_cell.y
      };
      DrawRectangleRounded(cell, 0.15f, 0, ASV_UI_CELL_FREE_COLOR);
    }
  }
}

void asv_ui_free_fonts() {
  for (int i = 0; i < MAX_FONTS; i++) {
    UnloadFont(fonts[i]);
  }
}