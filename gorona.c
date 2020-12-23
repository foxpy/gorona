#include <stddef.h>
#include <qc.h>
#include "game.h"

int main(int argc, char* argv[]) {
    qc_err* err = qc_err_new();
    qc_args* args = qc_args_new();
    size_t iterations;
    qc_args_unsigned_default(args, "iterations", 100, &iterations,
                             "number of game ticks to calculate");
    size_t m, n;
    qc_args_unsigned_default(args, "m", 20, &m, "field height");
    qc_args_unsigned_default(args, "n", 60, &n, "field width");
    double p_ill, p_death, p_recover;
    qc_args_double_default(args, "ill-probability", 0.1, &p_ill,
                           "probability for neighbor to ill cell to get ill");
    qc_args_double_default(args, "death-probability", 0.01, &p_death,
                           "probability for ill cell to die");
    qc_args_double_default(args, "recover-probability", 0.03, &p_recover,
                           "probability for ill cell to recover");
    if (qc_args_parse(args, argc, argv, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse command line arguments");
    } else {
        game* game = game_create(m, n, p_ill, p_death, p_recover);
        for (size_t i = 0; i < iterations; ++i) {
            game_advance(game);
        }
        game_print(game);
        game_free(game);
    }
    qc_args_free(args);
    qc_err_free(err);
}
