#include "raylib/src/raylib.h"
#include "game.h"

static void main_loop(Game *g) {
    while (!WindowShouldClose()) {
        game_inputhandler(g);
        game_draw(g);
    }
}

int main(void) {

    Game g;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "peng");

    SetTargetFPS(60);

    game_init(&g);
    main_loop(&g);

    CloseWindow();

    return 0;
}
