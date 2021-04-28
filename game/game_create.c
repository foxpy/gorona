#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <qc.h>
#include "game.h"

static state** game_create_field(size_t m, size_t n, qc_rnd* rnd) {
    state** ret = qc_malloc(sizeof(state*) * m);
    for (size_t i = 0; i < m; ++i) {
        ret[i] = qc_malloc(sizeof(state) * n);
        for (size_t j = 0; j < n; ++j) {
            ret[i][j] = STATE_HEALTHY;
        }
    }
    ret[qc_rnd64_uniform(rnd, m)][qc_rnd64_uniform(rnd, n)] = STATE_ILL;
    return ret;
}

static bool** game_create_spread(size_t m, size_t n, qc_rnd* rnd) {
    bool** ret = qc_malloc(sizeof(bool*) * m);
    for (size_t i = 0; i < m; ++i) {
        ret[i] = qc_malloc(sizeof(bool) * n);
        memset(ret[i], 0, n);
    }
    return ret;
}

game* game_create(size_t m, size_t n, double p_ill, double p_death, double p_recover) {
    qc_assert(m >= 5 && m <= 100, "m should be in range [5, 100]");
    qc_assert(n >= 5 && n <= 100, "n should be in range [5, 100]");
    qc_assert(p_ill >= 0.0 && p_ill <= 1.0, "probability should be in range [0.0, 1.0]");
    qc_assert(p_death >= 0.0 && p_death <= 1.0, "probability should be in range [0.0, 1.0]");
    qc_assert(p_recover >= 0.0 && p_recover <= 1.0, "probability should be in range [0.0, 1.0]");
    game* ret = qc_malloc(sizeof(game));
    qc_err* err = qc_err_new();
    if (qc_rnd_init(&ret->rnd, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to initialize random number generator");
    }
    qc_err_free(err);
    ret->m = m;
    ret->n = n;
    ret->field = game_create_field(m, n, &ret->rnd);
    ret->spread = game_create_spread(m, n, &ret->rnd);
    ret->p_ill = p_ill;
    ret->p_death = p_death;
    ret->p_recover = p_recover;
    return ret;
}
