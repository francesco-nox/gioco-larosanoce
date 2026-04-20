#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef enum 
{
    DIR_S = 0,
    DIR_W,
    DIR_E,
    DIR_N,
    DIR_SW,
    DIR_NW,
    DIR_SE,
    DIR_NE
} Direction8;

typedef struct Player 
{
    Vector2 position;
    float speed;
    Texture2D spriteSheet;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    float frameTime;
    float frameCounter;
    Direction8 direction;
    bool isMoving;
} Player;

void InitPlayer(Player* p, Vector2 startPos, const char* spriteSheetPath, int frameWidth, int frameHeight);
void UpdatePlayer(Player* p, float dt);
void DrawPlayer(Player* p);
void UnloadPlayer(Player* p);

#endif
