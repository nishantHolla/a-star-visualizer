#include "asv.h"

const int ASV_GRID_ROW_COUNT = 20;
const int ASV_GRID_COLUMN_COUNT = 40;
asv_cell_state **asv_grid = NULL;
asv_status asv_app_status;
asv_state asv_app_state;
asv_item_select asv_item_selected;
asv_tool_select asv_tool_selected;
asv_speed_select asv_speed_selected;
Vector2 asv_source_cell;
Vector2 asv_destination_cell;
pthread_t asv_thread;
int asv_thread_created = 0;

void asv_init_grid(void) {
  asv_grid = (asv_cell_state **) malloc(ASV_GRID_COLUMN_COUNT * sizeof(asv_cell_state *));
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    asv_grid[i] = (asv_cell_state *) malloc(ASV_GRID_ROW_COUNT * sizeof(asv_cell_state));
    for (int j = 0; j < ASV_GRID_ROW_COUNT; j++) {
      asv_grid[i][j] =ASV_CELL_FREE;
    }
  }
}

void asv_init_state(void) {
  asv_set_state(ASV_STATE_IDLE);
}

void asv_init_status(void) {
  asv_set_status(OBSTACLES_STATUS_TEXT, ASV_MESSAGE_NORMAL);
}

void asv_init_items(void) {
  asv_select_item(ASV_ITEM_SELECT_OBSTACLES);
}

void asv_init_tools(void) {
  asv_select_tool(ASV_TOOL_SELECT_ADD);
}

void asv_init_speed(void) {
  asv_select_speed(ASV_SPEED_SELECT_INSTANT);
}

void asv_init_cells(void) {
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
  if (asv_app_state != ASV_STATE_IDLE) {
    return;
  }

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
  if (asv_app_state != ASV_STATE_IDLE) {
    return;
  }

  asv_tool_selected = tool;
}

void asv_select_speed(asv_speed_select speed) {
  asv_speed_selected = speed;
}

void asv_select_cell(int column_index, int row_index) {
  if (asv_app_state != ASV_STATE_IDLE) {
    return;
  }

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

void asv_cycle_speed(void) {
  int speed = asv_speed_selected - 1;
  if (speed < 0) {
    speed = ASV_SPEED_SELECT_SLOW;
  }

  asv_select_speed((asv_speed_select) speed);
}

void asv_play(void) {
  if (asv_app_state == ASV_STATE_PLAYING) {
    asv_set_state(ASV_STATE_PAUSED);
    return;
  }
  else if (asv_app_state == ASV_STATE_PAUSED) {
    asv_set_state(ASV_STATE_PLAYING);
    return;
  }

  if (asv_source_cell.x == -1 || asv_source_cell.y == -1) {
    asv_set_status(SELECT_SOURCE_TEXT, ASV_MESSAGE_ERROR);
    return;
  }

  if (asv_destination_cell.x == -1 || asv_destination_cell.y == -1) {
    asv_set_status(SELECT_DESTINATION_TEXT, ASV_MESSAGE_ERROR);
    return;
  }

  asv_set_state(ASV_STATE_PLAYING);
  if (pthread_create(&asv_thread, NULL, &asv, NULL) == 0) {
    asv_thread_created = 1;
  };
}

void asv_clear(void) {
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    for (int j = 0; j < ASV_GRID_ROW_COUNT; j++) {
      asv_grid[i][j] = ASV_CELL_FREE;
    }
  }

  if (asv_app_state != ASV_STATE_IDLE) {
    if (pthread_cancel(asv_thread) == 0) {
      asv_thread_created = 0;
    };
  }

  asv_source_cell = (Vector2) { .x = -1, .y = -1};
  asv_destination_cell = (Vector2) { .x = -1, .y = -1};
  asv_set_state(ASV_STATE_IDLE);
  asv_select_tool(ASV_TOOL_SELECT_ADD);
  asv_select_item(ASV_ITEM_SELECT_OBSTACLES);
}

void asv_reset(void) {
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    for (int j = 0; j < ASV_GRID_ROW_COUNT; j++) {
      if (asv_grid[i][j] == ASV_CELL_VISITED || asv_grid[i][j] == ASV_CELL_RESULT) {
        asv_grid[i][j] = ASV_CELL_FREE;
      }
    }
  }

  if (asv_app_state != ASV_STATE_IDLE) {
    if (pthread_cancel(asv_thread) == 0) {
      asv_thread_created = 0;
    };
  }
  asv_set_state(ASV_STATE_IDLE);
  asv_select_tool(ASV_TOOL_SELECT_ADD);
  asv_select_item(ASV_ITEM_SELECT_OBSTACLES);
}

void asv_free_grid(void) {
  for (int i = 0; i < ASV_GRID_COLUMN_COUNT; i++) {
    free(asv_grid[i]);
  }
  free(asv_grid);
}

void *asv(void* args) {
  UNUSED(args);
  int found = 0;

  asv_PQueue open_set;
  asv_pqueue_init(&open_set);
  asv_pqueue_push(&open_set, asv_source_cell, asv_cost(asv_source_cell));

  asv_HashMap came_from;
  asv_hashmap_init(&came_from);

  asv_HashMap g_score;
  asv_hashmap_init(&g_score);
  asv_hashmap_add(&g_score, asv_compress(asv_source_cell), 0);

  asv_HashMap f_score;
  asv_hashmap_init(&f_score);
  asv_hashmap_add(&f_score, asv_compress(asv_source_cell), asv_cost(asv_source_cell));

  asv_HashMap visited;
  asv_hashmap_init(&visited);

  asv_PQueue result;
  asv_pqueue_init(&result);

  while (open_set.size > 0) {
    while (asv_app_state == ASV_STATE_PAUSED) {
      asv_sleep(500);
    }

    Vector2 current = asv_pqueue_pop(&open_set, NULL);
    asv_hashmap_add(&visited, asv_compress(current), 1);

    if (current.x == asv_destination_cell.x && current.y == asv_destination_cell.y) {
      int priority = ASV_GRID_ROW_COUNT * ASV_GRID_COLUMN_COUNT;

      while (1) {
        int check = asv_hashmap_get(&came_from, asv_compress(current));
        if (check == -1) {
          break;
        }

        current = asv_expand(check);
        asv_pqueue_push(&result, current, priority--);
      }

      found = 1;
      break;
    }

    int current_g = asv_hashmap_get(&g_score, asv_compress(current));
    int new_g = current_g + 1;
    int new_f = -1;

    if (current.x != asv_source_cell.x || current.y != asv_source_cell.y) {
      asv_grid[(int) current.x][(int) current.y] = ASV_CELL_VISITED;
    }

    Vector2 neighbors_delta[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i=0; i<4; i++) {
      Vector2 neighbor_cell = {
        .x = current.x + neighbors_delta[i].x,
        .y = current.y + neighbors_delta[i].y
      };

      if (neighbor_cell.x < 0 || neighbor_cell.x >= ASV_GRID_COLUMN_COUNT ||
          neighbor_cell.y < 0 || neighbor_cell.y >= ASV_GRID_ROW_COUNT ||
          asv_grid[(int)neighbor_cell.x][(int)neighbor_cell.y] == ASV_CELL_OBSTACLE) {
        continue;
      }

      new_f = new_g + asv_cost(neighbor_cell);

      int test_g = asv_hashmap_get(&g_score, asv_compress(neighbor_cell));
      if (test_g == -1 || test_g > new_g) {
        asv_hashmap_add(&g_score, asv_compress(neighbor_cell), new_g);
        asv_hashmap_add(&came_from, asv_compress(neighbor_cell), asv_compress(current));
      }

      int test_f = asv_hashmap_get(&f_score, asv_compress(neighbor_cell));
      if (test_f == -1 || test_f > new_f) {
        asv_hashmap_add(&f_score, asv_compress(neighbor_cell), new_f);
      }

      if (asv_hashmap_get(&visited, asv_compress(neighbor_cell)) == -1) {
        asv_pqueue_push(&open_set, neighbor_cell, new_f);
      }
    }

    asv_end_cycle();
  }

  if (found) {
    asv_set_status(FOUND_PATH_TEXT, ASV_MESSAGE_SUCCESS);
    while (result.size > 0) {
      while (asv_app_state == ASV_STATE_PAUSED) {
        asv_sleep(500);
      }
      Vector2 t = asv_pqueue_pop(&result, NULL);
      if (t.x != asv_source_cell.x || t.y != asv_source_cell.y) {
        asv_grid[(int) t.x][(int) t.y] = ASV_CELL_RESULT;
      }

      asv_end_cycle();
    }
  }
  else {
    asv_set_status(NOT_FOUND_PATH_TEXT, ASV_MESSAGE_ERROR);
  }

  asv_pqueue_free(&result);
  asv_pqueue_free(&open_set);
  asv_hashmap_free(&g_score);
  asv_hashmap_free(&f_score);
  asv_hashmap_free(&visited);
  asv_hashmap_free(&came_from);
  return NULL;
}

void asv_end_cycle(void) {
  switch (asv_speed_selected) {
    case ASV_SPEED_SELECT_INSTANT:
      return;

    case ASV_SPEED_SELECT_FAST:
      asv_sleep(FAST_SLEEP_MS);
      return;

    case ASV_SPEED_SELECT_MEDIUM:
      asv_sleep(MEDIUM_SLEEP_MS);
      return;

    case ASV_SPEED_SELECT_SLOW:
      asv_sleep(SLOW_SLEEP_MS);
      return;

    default:
      return;
  }
}

int asv_distance(Vector2 a, Vector2 b) {
  return abs((int)(a.x - b.x)) + abs((int)(a.y - b.y));
}

int asv_compress(Vector2 a) {
  int x = a.x;
  int y = a.y;
  return ((x + y) * (x + y + 1) / 2) + y;
}

Vector2 asv_expand(int a) {
  int w = (sqrt(8*a + 1) - 1) / 2;
  int t = (w * (w + 1)) / 2;
  int y = a - t;
  int x = w - y;
  return (Vector2) { .x = x, .y = y};
}

int asv_cost(Vector2 a) {
  return asv_distance(a, asv_destination_cell);
}

void asv_sleep(int ms) {
  usleep(ms * 1000);
}
