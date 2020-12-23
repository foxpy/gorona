#include <stddef.h>
#include <stdlib.h>
#include "game.h"

void game_free(game* game) {
    for (size_t i = 0; i < game->m; ++i) {
        free(game->field[i]);
    }
    free(game->field);
    free(game);
}
