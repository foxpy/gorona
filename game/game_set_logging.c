#include <stdio.h>
#include "game.h"

void game_set_logging(game* game, FILE* stats, FILE* matrices) {
    game->stats = stats;
    game->matrices = matrices;
}
