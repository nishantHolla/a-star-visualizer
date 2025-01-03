#include "asv.h"

const int ASV_GRID_ROW_COUNT = 20;
const int ASV_GRID_COLUMN_COUNT = 40;
asv_cell_state **asv_grid = NULL;
asv_status asv_app_status;

void asv_init_grid() {
  asv_grid = (asv_cell_state **) malloc(ASV_GRID_COLUMN_COUNT * sizeof(asv_cell_state *));
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    asv_grid[i] = (asv_cell_state *) malloc(ASV_GRID_ROW_COUNT * sizeof(asv_cell_state));
    for (int j = 0; j < ASV_GRID_ROW_COUNT; j++) {
      asv_grid[i][j] =ASV_CELL_FREE;
    }
  }
}

void asv_init_status() {
  asv_set_status("Select obstacles", ASV_MESSAGE_NORMAL);
}

void asv_set_status(const char *message, asv_message_type type) {
  asv_app_status.message_type = type;
  strncpy(asv_app_status.message, message, MAX_MESSAGE_LENGTH);
}

void asv_free_grid() {
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    free(asv_grid[i]);
  }
  free(asv_grid);
}
