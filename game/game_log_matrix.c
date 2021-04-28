#include "game.h"
#include "game_impl.h"

void game_log_matrix(game* game) {
    if (game->matrices != NULL) {
        fprintf(game->matrices, "Iteration %zu: ", game->iteration);
        size_t i = 0;
        for (;;) {
            for (size_t j = 0; j < game->n; ++j) {
                switch (game->field[i][j]) {
                    case STATE_HEALTHY: fputc('H', game->matrices); break;
                    case STATE_ILL: fputc('I', game->matrices); break;
                    case STATE_DEAD: fputc('D', game->matrices); break;
                }
            }
            ++i;
            if (i == game->m) {
                fputc('\n', game->matrices);
                break;
            } else {
                fputc(',', game->matrices);
            }
        }
    }
}
