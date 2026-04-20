#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "raymath.h"
#include "player.h"   //per Direction8

typedef struct Enemy {
    Vector2 position;
    float speed;

    Direction8 direction;
    bool isMoving;

    float moveTimer;
    float moveDuration;

    Texture2D spriteSheet;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    float frameTime;
    float frameCounter;

} Enemy;

void InitEnemy(Enemy* e, Vector2 startPos, const char* spriteSheetPath, int frameWidth, int frameHeight);
void UpdateEnemy(Enemy* e, float dt);
void DrawEnemy(Enemy* e);
void UnloadEnemy(Enemy* e);

#endif
