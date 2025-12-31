#include "raylib/src/raylib.h"
#include "game.h"

void init_players(Game *g) {
    g->p1.x = (float) SCREEN_WIDTH - 60;
    g->p1.y = (float) SCREEN_HEIGHT / 2 - (float) PLAYER_HEIGHT / 2;

    g->p2.x = (float) 60 - PLAYER_WIDTH;
    g->p2.y = (float) SCREEN_HEIGHT / 2 - (float) PLAYER_HEIGHT / 2;
}

void game_init(Game *g) {
    init_players(g);
}

void game_inputhandler(Game *g) {
    if (IsKeyDown(KEY_K)) g->p1.y -= GetFrameTime() * PLAYER_SPEED;
    if (IsKeyDown(KEY_J)) g->p1.y += GetFrameTime() * PLAYER_SPEED;
    if (IsKeyDown(KEY_D)) g->p2.y -= GetFrameTime() * PLAYER_SPEED;
    if (IsKeyDown(KEY_F)) g->p2.y += GetFrameTime() * PLAYER_SPEED;
}

void draw_line(void) {
    const int SIZE = 10;
    int n = 0;
    while (n < SCREEN_HEIGHT) {
        DrawRectangle(SCREEN_WIDTH / 2 - SIZE / 2,
                      n,
                      SIZE,
                      SIZE,
                      WHITE);
        n += 2 * SIZE;
    }
}

void game_draw(Game *g) {
    BeginDrawing();

    ClearBackground(BLACK);

    draw_line();

    DrawRectangle(g->p1.x, g->p1.y, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
    DrawRectangle(g->p2.x, g->p2.y, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);

    EndDrawing();
}
