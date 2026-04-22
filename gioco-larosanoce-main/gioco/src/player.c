#include "player.h"
#include "raymath.h"

void InitPlayer(Player *p) {
    p->rect = (Rectangle){ 400, 300, 30, 30 };
    p->speed = 250.0f;
    p->color = BLUE;
}

void UpdatePlayer(Player *p, Rectangle *obstacles, int obstacleCount, float dt) {
    Vector2 dir = { 0 };
    if (IsKeyDown(KEY_W)) dir.y -= 1;
    if (IsKeyDown(KEY_S)) dir.y += 1;
    if (IsKeyDown(KEY_A)) dir.x -= 1;
    if (IsKeyDown(KEY_D)) dir.x += 1;

    // Impedisce di andare più veloce in diagonale
    if (Vector2Length(dir) > 0) dir = Vector2Normalize(dir);

    // Movimento Orizzontale con collisione
    float nextX = p->rect.x + dir.x * p->speed * dt;
    Rectangle nextRectX = { nextX, p->rect.y, p->rect.width, p->rect.height };
    bool collisionX = false;
    for (int i = 0; i < obstacleCount; i++) {
        if (CheckCollisionRecs(nextRectX, obstacles[i])) {
            collisionX = true;
            break;
        }
    }
    if (!collisionX) p->rect.x = nextX;

    // Movimento Verticale con collisione
    float nextY = p->rect.y + dir.y * p->speed * dt;
    Rectangle nextRectY = { p->rect.x, nextY, p->rect.width, p->rect.height };
    bool collisionY = false;
    for (int i = 0; i < obstacleCount; i++) {
        if (CheckCollisionRecs(nextRectY, obstacles[i])) {
            collisionY = true;
            break;
        }
    }
    if (!collisionY) p->rect.y = nextY;
}

void DrawPlayer(Player *p) {
    DrawRectangleRec(p->rect, p->color);
}