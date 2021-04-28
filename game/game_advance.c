#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <qc.h>
#include "game.h"

static void clear_spread(game* game) {
    for (size_t i = 0; i < game->m; ++i) {
        memset(game->spread[i], 0, game->n);
    }
}

static void apply_spread(game* game) {
    for (size_t i = 0; i < game->m; ++i) {
        for (size_t j = 0; j < game->n; ++j) {
            if (game->spread[i][j] && game->field[i][j] == STATE_HEALTHY) {
                game->field[i][j] = STATE_ILL;
            }
        }
    }
}

static void make_ill(state const* state, bool* spread) {
    if (*state != STATE_DEAD) {
        *spread = true;
    }
}

static void game_spread_disease(game* game, size_t x, size_t y) {
    bool up = y == 0;
    bool down = y == (game->n - 1);
    bool left = x == 0;
    bool right = x == (game->m - 1);
    if (!up && !left && qc_rnd_fp64(&game->rnd) < game->p_ill)
        make_ill(&game->field[x-1][y-1], &game->spread[x-1][y-1]);
    if (!up && qc_rnd_fp64(&game->rnd) < game->p_ill)
        make_ill(&game->field[x][y-1], &game->spread[x][y-1]);
    if (!up && !right && qc_rnd_fp64(&game->rnd) < game->p_ill)
        make_ill(&game->field[x+1][y-1], &game->spread[x+1][y-1]);
    if (!right && qc_rnd_fp64(&game->rnd) < game->p_ill)
        make_ill(&game->field[x+1][y], &game->spread[x+1][y]);
    if (!right && !down && qc_rnd_fp64(&game->rnd) < game->p_ill)
        make_ill(&game->field[x+1][y+1], &game->spread[x+1][y+1]);
    if (!down && qc_rnd_fp64(&game->rnd) < game->p_ill)
        make_ill(&game->field[x][y+1], &game->spread[x][y+1]);
    if (!left && !down && qc_rnd_fp64(&game->rnd) < game->p_ill)
        make_ill(&game->field[x-1][y+1], &game->spread[x-1][y+1]);
    if (!left && qc_rnd_fp64(&game->rnd) < game->p_ill)
        make_ill(&game->field[x-1][y], &game->spread[x-1][y]);
}

void game_advance(game* game) {
    clear_spread(game);
    for (size_t i = 0; i < game->m; ++i) {
        for (size_t j = 0; j < game->n; ++j) {
            if (game->field[i][j] == STATE_ILL) {
                game_spread_disease(game, i, j);
            }
        }
    }
    apply_spread(game);
    for (size_t i = 0; i < game->m; ++i) {
        for (size_t j = 0; j < game->n; ++j) {
            if (game->field[i][j] == STATE_ILL && qc_rnd_fp64(&game->rnd) < game->p_death) {
                game->field[i][j] = STATE_DEAD;
            }
        }
    }
    for (size_t i = 0; i < game->m; ++i) {
        for (size_t j = 0; j < game->n; ++j) {
            if (game->field[i][j] == STATE_ILL && qc_rnd_fp64(&game->rnd) < game->p_recover) {
                game->field[i][j] = STATE_HEALTHY;
            }
        }
    }
}
