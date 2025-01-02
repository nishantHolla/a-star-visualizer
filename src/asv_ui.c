#include "asv.h"

// UI Colors

const Color ASV_UI_WINDOW_BG_COLOR = { .r=24, .g=24, .b=27, .a=255 };
const Color ASV_UI_CONTAINER_BG_COLOR = { .r=63, .g=63, .b=70, .a=255 };

// UI Values

const float ASV_UI_ROUNDNESS_LG = 0.2f;
const float ASV_UI_ROUNDNESS_SM = 0.05f;
const float ASV_UI_WINDOW_PADDING = 20.0f;
const float ASV_UI_CONTAINER_SPACING = 20.0f;

// UI Elements

Rectangle asv_ui_menu_bar;
Rectangle asv_ui_status_bar;
Rectangle asv_ui_grid;

// UI Functions

void asv_ui_calculate() {

  asv_ui_status_bar = (Rectangle) {
    .x=ASV_UI_WINDOW_PADDING,
    .y=ASV_UI_WINDOW_PADDING,
    .width=GetScreenWidth() - (2 * ASV_UI_WINDOW_PADDING),
    .height=80.0f
  };

  asv_ui_menu_bar = (Rectangle) {
    .x=ASV_UI_WINDOW_PADDING,
    .y=GetScreenHeight() - ASV_UI_WINDOW_PADDING - 80.0f,
    .width=GetScreenWidth() - (2 * ASV_UI_WINDOW_PADDING),
    .height=80.0f
  };

  asv_ui_grid = (Rectangle) {
    .x=ASV_UI_WINDOW_PADDING,
    .y=asv_ui_menu_bar.height + ASV_UI_WINDOW_PADDING + ASV_UI_CONTAINER_SPACING,
    .width=GetScreenWidth() - (2 * ASV_UI_WINDOW_PADDING),
    .height=GetScreenHeight() - (2 * ASV_UI_CONTAINER_SPACING) - (2 * ASV_UI_WINDOW_PADDING) - asv_ui_menu_bar.height - asv_ui_status_bar.height
  };
}

void asv_ui_draw_containers() {
  DrawRectangleRounded(asv_ui_status_bar, ASV_UI_ROUNDNESS_LG, 0, ASV_UI_CONTAINER_BG_COLOR);
  DrawRectangleRounded(asv_ui_grid, ASV_UI_ROUNDNESS_SM, 0, ASV_UI_CONTAINER_BG_COLOR);
  DrawRectangleRounded(asv_ui_menu_bar, ASV_UI_ROUNDNESS_LG, 0, ASV_UI_CONTAINER_BG_COLOR);
}
