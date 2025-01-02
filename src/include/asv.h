#ifndef ASV_H_
#define ASV_H_

#include <stdio.h>
#include <stdint.h>
#include "raylib.h"

// UI Colors

extern const Color ASV_UI_WINDOW_BG_COLOR;
extern const Color ASV_UI_CONTAINER_BG_COLOR;

// UI Values

extern const float ASV_UI_ROUNDNESS_LG;
extern const float ASV_UI_ROUNDNESS_SM;
extern const float ASV_UI_WINDOW_PADDING;
extern const float ASV_UI_CONTAINER_SPACING;

// UI Elements

extern Rectangle asv_ui_menu_bar;
extern Rectangle asv_ui_status_bar;
extern Rectangle asv_ui_grid;

// UI Functions

void asv_ui_calculate();
void asv_ui_draw_containers();

#endif // !ASV_H_
