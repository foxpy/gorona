add_library(Game
    game_create.c
    game_free.c
    game_advance.c
    game_print.c
)
target_link_libraries(Game PUBLIC qc)
target_include_directories(Game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
