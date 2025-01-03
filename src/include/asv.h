#ifndef ASV_H_
#define ASV_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "raylib.h"

#define MAX_FONTS 8
#define APP_TITLE "A* Visualizer"

// App Definitions

typedef enum asv_cell_state {
  ASV_CELL_FREE,
  ASV_CELL_VISITED,
  ASV_CELL_SOURCE,
  ASV_CELL_DESTINATION,
  ASV_CELL_OBSTACLE
} asv_cell_state;

// App Values

extern const int ASV_GRID_ROW_COUNT;
extern const int ASV_GRID_COLUMN_COUNT;
extern asv_cell_state **asv_grid;

// App Functions

void asv_init_grid();
void asv_free_grid();

// UI Assests

extern const char *ASV_UI_FONT_PATH;

// UI Fonts

extern Font fonts[MAX_FONTS];

// UI Colors

extern const Color ASV_UI_WINDOW_BG_COLOR;
extern const Color ASV_UI_CONTAINER_BG_COLOR;
extern const Color ASV_UI_TEXT_COLOR;
extern const Color ASV_UI_CELL_FREE_COLOR;

// UI Values

extern const float ASV_UI_ROUNDNESS_LG;
extern const float ASV_UI_ROUNDNESS_SM;

extern const float ASV_UI_TEXT_SIZE_XL;
extern const float ASV_UI_TEXT_SPACING_XL;

extern const Vector2 ASV_UI_WINDOW_PADDING;

extern const Vector2 ASV_UI_CONTAINER_PADDING;
extern const Vector2 ASV_UI_CONTAINER_SPACING;

extern const Vector2 ASV_UI_GRID_PADDING;
extern const Vector2 ASV_UI_GRID_SPACING;

// UI Elements

extern Rectangle asv_ui_menu_bar;
extern Rectangle asv_ui_status_bar;
extern Rectangle asv_ui_grid;

extern Vector2 asv_ui_title_text;
extern Vector2 asv_ui_cell;

// UI Functions

void asv_ui_init_fonts();
void asv_ui_calculate();
void asv_ui_draw_containers();
void asv_ui_draw_text();
void asv_ui_draw_grid();
void asv_ui_free_fonts();

#endif // !ASV_H_
