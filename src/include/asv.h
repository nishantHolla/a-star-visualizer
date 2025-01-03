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
#define OBSTACLES_TEXT "Obstacles"
#define SOURCE_TEXT "Source"
#define DESTINATION_TEXT "Destination"
#define OBSTACLES_STATUS_TEXT "Select obstacles"
#define SOURCE_STATUS_TEXT "Select souce"
#define DESTINATION_STATUS_TEXT "Select destination"
#define ADD_TEXT "Add"
#define REMOVE_TEXT "Remove"
#define PLAY_TEXT "Play"
#define RESET_TEXT "Reset"
#define CLEAR_TEXT "Clear"

#define V_CENTER(a,b) a.y+((a.height-b.y)/2)
#define REC2VEC(a) (Vector2) {.x=a.x,.y=a.y}
#define ITEM_COLOR(a,b) a==b ? ASV_UI_SELECTED_ITEM_COLOR : ASV_UI_TEXT_COLOR
#define TOOL_COLOR(a,b) a==b ? ASV_UI_SELECTED_TOOL_COLOR : ASV_UI_TEXT_COLOR

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

typedef enum asv_item_select {
  ASV_ITEM_SELECT_OBSTACLES,
  ASV_ITEM_SELECT_SOURCE,
  ASV_ITEM_SELECT_DESTINATION
} asv_item_select;

typedef enum asv_tool_select {
  ASV_TOOL_SELECT_ADD,
  ASV_TOOL_SELECT_REMOVE
} asv_tool_select;

typedef struct asv_status {
  char message[MAX_MESSAGE_LENGTH];
  asv_message_type message_type;
} asv_status;

// App Values

extern const int ASV_GRID_ROW_COUNT;
extern const int ASV_GRID_COLUMN_COUNT;
extern asv_cell_state **asv_grid;
extern asv_status asv_app_status;
extern asv_item_select asv_item_selected;
extern asv_tool_select asv_tool_selected;

// App Functions

void asv_init_grid();
void asv_init_status();
void asv_init_items();
void asv_init_tools();
void asv_set_status(const char *message, asv_message_type type);
void asv_select_item(asv_item_select item);
void asv_select_tool(asv_tool_select tool);
void asv_free_grid();

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
extern const Color ASV_UI_SELECTED_ITEM_COLOR;
extern const Color ASV_UI_SELECTED_TOOL_COLOR;

// UI Values

extern const float ASV_UI_ROUNDNESS_LG;
extern const float ASV_UI_ROUNDNESS_SM;

extern const float ASV_UI_TEXT_SIZE_XL;
extern const float ASV_UI_TEXT_SPACING_XL;
extern const float ASV_UI_TEXT_SIZE_MD;
extern const float ASV_UI_TEXT_SPACING_MD;
extern const float ASV_UI_TEXT_SIZE_SM;
extern const float ASV_UI_TEXT_SPACING_SM;

extern const float ASV_UI_TEXT_ITEM_SIZE;
extern const float ASV_UI_TEXT_ITEM_SPACING;

extern const float ASV_UI_TEXT_TOOL_SIZE;
extern const float ASV_UI_TEXT_TOOL_SPACING;

extern const float ASV_UI_TEXT_ACTION_SIZE;
extern const float ASV_UI_TEXT_ACTION_SPACING;

extern const Vector2 ASV_UI_WINDOW_PADDING;

extern const Vector2 ASV_UI_CONTAINER_PADDING;
extern const Vector2 ASV_UI_CONTAINER_SPACING;

extern const Vector2 ASV_UI_GRID_PADDING;
extern const Vector2 ASV_UI_GRID_SPACING;

extern const Vector2 ASV_UI_ITEMS_SPACING;
extern const Vector2 ASV_UI_TOOLS_SPACING;
extern const Vector2 ASV_UI_ACTIONS_SPACING;

// UI Elements

extern Rectangle asv_ui_menu_bar;
extern Rectangle asv_ui_status_bar;
extern Rectangle asv_ui_grid;
extern Rectangle asv_ui_obstacles_button;
extern Rectangle asv_ui_source_button;
extern Rectangle asv_ui_destination_button;
extern Rectangle asv_ui_add_button;
extern Rectangle asv_ui_remove_button;
extern Rectangle asv_ui_play_button;
extern Rectangle asv_ui_reset_button;
extern Rectangle asv_ui_clear_button;

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
