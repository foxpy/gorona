#include <stddef.h>
#include <stdio.h>
#include <qc.h>
#include "game.h"

void game_print(game* game) {
    for (size_t i = 0; i < game->m; ++i) {
        for (size_t j = 0; j < game->n; ++j) {
            switch(game->field[i][j]) {
                case STATE_ILL: putchar('I'); break;
                case STATE_HEALTHY: putchar('H'); break;
                case STATE_DEAD: putchar('D'); break;
                default: QC_UNREACHABLE_CODE();
            }
        }
        putchar('\n');
    }
}
