add_library(Game
    game_create.c
    game_free.c
    game_advance.c
    game_print.c
    game_set_logging.c
    game_log_stats.c
    game_log_matrix.c
)
target_link_libraries(Game PUBLIC qc)
target_include_directories(Game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
