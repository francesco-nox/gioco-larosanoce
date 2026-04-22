#include "enemy.h"
#include "raymath.h"

void InitEnemy(Enemy *e) {
    e->rect = (Rectangle){ 50, 50, 35, 35 };
    e->speed = 180.0f;
    e->color = RED;
}

void UpdateEnemy(Enemy *e, Vector2 targetPos, Rectangle *obstacles, int obstacleCount, float dt) {
    Vector2 pos = { e->rect.x, e->rect.y };
    Vector2 dir = Vector2Subtract(targetPos, pos);
    if (Vector2Length(dir) > 0) dir = Vector2Normalize(dir);

    // Movimento X
    float nextX = e->rect.x + dir.x * e->speed * dt;
    Rectangle nextRectX = { nextX, e->rect.y, e->rect.width, e->rect.height };
    bool colX = false;
    for (int i = 0; i < obstacleCount; i++) {
        if (CheckCollisionRecs(nextRectX, obstacles[i])) { colX = true; break; }
    }
    if (!colX) e->rect.x = nextX;

    // Movimento Y
    float nextY = e->rect.y + dir.y * e->speed * dt;
    Rectangle nextRectY = { e->rect.x, nextY, e->rect.width, e->rect.height };
    bool colY = false;
    for (int i = 0; i < obstacleCount; i++) {
        if (CheckCollisionRecs(nextRectY, obstacles[i])) { colY = true; break; }
    }
    if (!colY) e->rect.y = nextY;
}

void DrawEnemy(Enemy *e) {
    DrawRectangleRec(e->rect, e->color);
}