#include "game_impl.h"
#include <stddef.h>

static size_t count_cells(game* game, state const target) {
    size_t ret = 0;
    for (size_t i = 0; i < game->m; ++i) {
        for (size_t j = 0; j < game->n; ++j) {
            if (game->field[i][j] == target) {
                ++ret;
            }
        }
    }
    return ret;
}

void game_log_stats(game* game) {
    if (game->stats != NULL) {
        size_t healthy = count_cells(game, STATE_HEALTHY);
        size_t ill = count_cells(game, STATE_ILL);
        size_t dead = count_cells(game, STATE_DEAD);
        fprintf(game->stats, "Iteration %zu: H: %zu, I: %zu, D: %zu\n",
                game->iteration, healthy, ill, dead);
    }
}
