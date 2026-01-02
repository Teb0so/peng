#include <stdio.h>

#include "raylib/src/raylib.h"
#include "game.h"

void init_players(Game *g) {
    g->p1.x = (float) SCREEN_WIDTH - PLAYER_PADDING;
    g->p1.y = (float) SCREEN_HEIGHT / 2 - (float) PLAYER_HEIGHT / 2;

    g->p2.x = (float) PLAYER_PADDING - PLAYER_WIDTH;
    g->p2.y = (float) SCREEN_HEIGHT / 2 - (float) PLAYER_HEIGHT / 2;
}

void init_peng(Peng *p, Score *s, int last) {
    p->pos.x = (float) SCREEN_WIDTH / 2 - (float) PENG_SIZE / 2;

    if ((s->p1 + s->p2) % 2 == 0 ) 
        p->pos.y = (float) SCREEN_HEIGHT / 4 - (float) PENG_SIZE / 2;
    else
        p->pos.y = (float) SCREEN_HEIGHT - (float)SCREEN_HEIGHT / 4 - (float) PENG_SIZE / 2;

    p->speed.y = PENG_INIT_SPEED;

    if(last == P2)
        p->speed.x = PENG_INIT_SPEED;
    else
        p->speed.x = PENG_INIT_SPEED * - 1;
}

void game_init(Game *g) {
    g->running = false;
    g->last = P2;
    g->score.p1 = 0;
    g->score.p2 = 0;
    init_players(g);
    init_peng(&g->peng, &g->score, g->last);
}

void draw_score(Score *s) {
    char p1_score[10];
    char p2_score[10];
    int font_size = 50;
    sprintf(p1_score, "%02d", s->p1);
    sprintf(p2_score, "%02d", s->p2);

    DrawText(p1_score, PLAYER_PADDING, 0, font_size, BLACK);
    DrawText(p2_score, SCREEN_WIDTH - 2 * font_size, 0, font_size, BLACK);
}

void move_paddle(float *y, float delta, int direction) {
    *y += direction * PLAYER_SPEED * delta;

    if (*y < 0)
        *y = 0;
    else if (*y + PLAYER_HEIGHT > SCREEN_HEIGHT)
        *y = SCREEN_HEIGHT - PLAYER_HEIGHT;
}

void peng_colisionHandler(Peng *p) {
    const int n = 50;
    if (p->speed.x >=0 ) p->speed.x += n; else p->speed.x -= n;
    // if (p->speed.y >=0 ) p->speed.y += n; else p->speed.y -= n;
    p->speed.x = p->speed.x * - 1;
}

void game_movePeng(Game *g, float delta) {
    if (g->running) {
        g->peng.rotation += g->peng.speed.x / 100;

        g->peng.pos.x += g->peng.speed.x * delta;
        g->peng.pos.y += g->peng.speed.y * delta;

        // Top / bottom collision
        if (g->peng.pos.y < 0 || g->peng.pos.y + PENG_SIZE > SCREEN_HEIGHT) {
            g->peng.speed.y = g->peng.speed.y * - 1;
        }
        // P2 score
        else if (g->peng.pos.x < 0) {
            g->score.p2++;
            init_peng(&g->peng, &g->score, g->last);
        }
        // P1 score
        else if (g->peng.pos.x + PENG_SIZE > SCREEN_WIDTH) {
            g->score.p1++;
            init_peng(&g->peng, &g->score, g->last);
        }
        // P1 collision
        else if (g->peng.pos.x + (float)PENG_SIZE > g->p1.x && g->last == P2) {
            if (g->peng.pos.y + (float)PENG_SIZE > g->p1.y && g->peng.pos.y < g->p1.y + PLAYER_HEIGHT) {
                g->last = P1;
                peng_colisionHandler(&g->peng);
            }
        }
        // P2 collision
        else if (g->peng.pos.x - PLAYER_WIDTH < g->p2.x && g->last == P1) {
            if (g->peng.pos.y + (float)PENG_SIZE > g->p2.y && g->peng.pos.y < g->p2.y + PLAYER_HEIGHT) {
                g->last = P2;
                peng_colisionHandler(&g->peng);
            }
        }
    }
}

void game_inputhandler(Game *g, float delta) {
    if (IsKeyPressed(KEY_SPACE)) {
        g->running = !g->running;
    }

    if (!g->running) return;

    if (IsKeyDown(KEY_I)) move_paddle(&g->p1.y, delta, -1);
    if (IsKeyDown(KEY_U)) move_paddle(&g->p1.y, delta,  1);

    if (IsKeyDown(KEY_E)) move_paddle(&g->p2.y, delta, -1);
    if (IsKeyDown(KEY_R)) move_paddle(&g->p2.y, delta,  1);
}

void draw_peng(Peng *p) {
    // DrawRectangle(p->pos.x, p->pos.y, PENG_SIZE, PENG_SIZE, LIME);

    Rectangle sourceRec = { 0.0f, 0.0f, (float)p->texture.width, (float)p->texture.height};
    Rectangle destRec = { p->pos.x + 16, p->pos.y + 16, PENG_SIZE, PENG_SIZE};
    Vector2 origin = { (float)p->texture.width/2.0f, (float)p->texture.height / 2.0f};

    DrawTexturePro(p->texture, sourceRec, destRec, origin, p->rotation, WHITE);
}

void draw_line(void) {
    const int SIZE = 10;
    int n = 0;
    while (n < SCREEN_HEIGHT) {
        DrawRectangle(SCREEN_WIDTH / 2 - SIZE / 2,
                      n,
                      SIZE,
                      SIZE,
                      BLACK);
        n += 2 * SIZE;
    }
}

void game_draw(Game *g) {
    BeginDrawing();

    ClearBackground(LIGHTGRAY);

    draw_line();

    draw_score(&g->score);

    DrawRectangle(g->p1.x, g->p1.y, PLAYER_WIDTH, PLAYER_HEIGHT, BLACK);
    DrawRectangle(g->p2.x, g->p2.y, PLAYER_WIDTH, PLAYER_HEIGHT, BLACK);

    draw_peng(&g->peng);

    EndDrawing();
}
