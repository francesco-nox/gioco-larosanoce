#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

typedef struct Player {
    Rectangle rect;
    float speed;
    Color color;
} Player;

void InitPlayer(Player *p);
void UpdatePlayer(Player *p, Rectangle *obstacles, int obstacleCount, float dt);
void DrawPlayer(Player *p);

#endif