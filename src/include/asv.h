#ifndef ASV_H_
#define ASV_H_

#include <stdio.h>
#include <stdint.h>
#include "raylib.h"

#define MAX_FONTS 8
#define APP_TITLE "A* Visualizer"

// UI Assests

extern const char *ASV_UI_FONT_PATH;

// UI Fonts

extern Font fonts[MAX_FONTS];

// UI Colors

extern const Color ASV_UI_WINDOW_BG_COLOR;
extern const Color ASV_UI_CONTAINER_BG_COLOR;
extern const Color ASV_UI_TEXT_COLOR;

// UI Values

extern const float ASV_UI_ROUNDNESS_LG;
extern const float ASV_UI_ROUNDNESS_SM;

extern const float ASV_UI_TEXT_SIZE_XL;
extern const float ASV_UI_TEXT_SPACING_XL;

extern const Vector2 ASV_UI_WINDOW_PADDING;

extern const Vector2 ASV_UI_CONTAINER_PADDING;
extern const Vector2 ASV_UI_CONTAINER_SPACING;

// UI Elements

extern Rectangle asv_ui_menu_bar;
extern Rectangle asv_ui_status_bar;
extern Rectangle asv_ui_grid;

extern Vector2 asv_ui_title_text;

// UI Functions

void asv_ui_init_fonts();
void asv_ui_calculate();
void asv_ui_draw_containers();
void asv_ui_draw_text();
void asv_ui_free_fonts();

#endif // !ASV_H_
