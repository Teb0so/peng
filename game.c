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

void move_paddle(float *y, float delta, int direction)
{
    *y += direction * PLAYER_SPEED * delta;

    if (*y < 0)
        *y = 0;
    else if (*y + PLAYER_HEIGHT > SCREEN_HEIGHT)
        *y = SCREEN_HEIGHT - PLAYER_HEIGHT;
}

void game_inputhandler(Game *g, float delta) {
    if (IsKeyDown(KEY_K)) move_paddle(&g->p1.y, delta, -1);
    if (IsKeyDown(KEY_J)) move_paddle(&g->p1.y, delta,  1);

    if (IsKeyDown(KEY_D)) move_paddle(&g->p2.y, delta, -1);
    if (IsKeyDown(KEY_F)) move_paddle(&g->p2.y, delta,  1);
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
