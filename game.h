#include "raylib/src/raylib.h"

#define PLAYER_SPEED 450.0f

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 100

typedef struct {
    Vector2 p1;
    Vector2 p2;
} Game;

extern void game_init(Game *g);
extern void game_draw(Game *g);
extern void game_inputhandler(Game *g, float delta);
