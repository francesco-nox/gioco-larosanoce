#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"

typedef struct Enemy {
    Rectangle rect;
    float speed;
    Color color;
} Enemy;

void InitEnemy(Enemy *e);
void UpdateEnemy(Enemy *e, Vector2 targetPos, Rectangle *obstacles, int obstacleCount, float dt);
void DrawEnemy(Enemy *e);

#endif