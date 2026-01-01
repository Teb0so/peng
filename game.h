#include "raylib/src/raylib.h"

#define PLAYER_SPEED 600.0f
#define PENG_INIT_SPEED 200.0f

#define PENG_SIZE 30

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 100
#define PLAYER_PADDING 40

enum {
    P1,
    P2,
};


typedef struct {
    int p1;
    int p2;
} Score;

typedef struct {
    Vector2 pos;
    Vector2 speed;
} Peng;

typedef struct {
    Vector2 p1;
    Vector2 p2;
    Peng peng;
    Score score;
    int last;
} Game;

extern void game_init(Game *g);
extern void game_draw(Game *g);
extern void game_movePeng(Game *g, float delta);
extern void game_inputhandler(Game *g, float delta);
