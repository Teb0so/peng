#include "raylib/src/raylib.h"

#define PLAYER_SPEED 450.0f
#define PENG_INIT_SPEED 200.0f

#define PENG_SIZE 30

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 100

typedef struct {
    Vector2 pos;
    Vector2 speed;
} Peng;

typedef struct {
    Vector2 p1;
    Vector2 p2;
    Peng peng;
} Game;

extern void game_init(Game *g);
extern void game_draw(Game *g);
extern void game_movePeng(Game *g, float delta);
extern void game_inputhandler(Game *g, float delta);
