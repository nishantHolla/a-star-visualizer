#ifndef ASV_H_
#define ASV_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define MAX_FONTS 8
#define MAX_MESSAGE_LENGTH 100
#define APP_TITLE "A* Visualizer"

// App Definitions

typedef enum asv_cell_state {
  ASV_CELL_FREE,
  ASV_CELL_VISITED,
  ASV_CELL_SOURCE,
  ASV_CELL_DESTINATION,
  ASV_CELL_OBSTACLE
} asv_cell_state;

typedef enum asv_message_type {
  ASV_MESSAGE_NORMAL,
  ASV_MESSAGE_WARNING,
  ASV_MESSAGE_ERROR,
  ASV_MESSAGE_SUCCESS
} asv_message_type;

typedef struct asv_status {
  char message[MAX_MESSAGE_LENGTH];
  asv_message_type message_type;
} asv_status;

// App Values

extern const int ASV_GRID_ROW_COUNT;
extern const int ASV_GRID_COLUMN_COUNT;
extern asv_cell_state **asv_grid;
extern asv_status asv_app_status;

// App Functions

void asv_init_grid();
void asv_init_status();
void asv_free_grid();
void asv_set_status(const char *message, asv_message_type type);

// UI Assests

extern const char *ASV_UI_FONT_PATH;

// UI Fonts

extern Font fonts[MAX_FONTS];

// UI Colors

extern const Color ASV_UI_WINDOW_BG_COLOR;
extern const Color ASV_UI_CONTAINER_BG_COLOR;
extern const Color ASV_UI_TEXT_COLOR;
extern const Color ASV_UI_TEXT_WARNING_COLOR;
extern const Color ASV_UI_TEXT_ERROR_COLOR;
extern const Color ASV_UI_TEXT_SUCCESS_COLOR;
extern const Color ASV_UI_CELL_FREE_COLOR;

// UI Values

extern const float ASV_UI_ROUNDNESS_LG;
extern const float ASV_UI_ROUNDNESS_SM;

extern const float ASV_UI_TEXT_SIZE_XL;
extern const float ASV_UI_TEXT_SPACING_XL;
extern const float ASV_UI_TEXT_SIZE_MD;
extern const float ASV_UI_TEXT_SPACING_MD;

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
extern Vector2 asv_ui_status_position;

// UI Functions

void asv_ui_init_fonts();
void asv_ui_calculate();
Color asv_ui_get_status_color();
void asv_ui_draw_containers();
void asv_ui_draw_text();
void asv_ui_draw_grid();
void asv_ui_free_fonts();

#endif // !ASV_H_
