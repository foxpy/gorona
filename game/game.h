#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <qc.h>

enum {
    STATE_HEALTHY = 0,
    STATE_ILL = 1,
    STATE_DEAD = 2,
};
typedef unsigned char state;

typedef struct {
    size_t m, n;
    state** field;
    bool** spread;
    qc_rnd rnd;
    double p_ill, p_death, p_recover;
} game;

game* game_create(size_t m, size_t n, double p_ill, double p_death, double p_recover);
void game_free(game* game);
void game_advance(game* game);
void game_print(game* game);
