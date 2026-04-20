#include "player.h"
#include <math.h>

void InitPlayer(Player* p, Vector2 startPos, const char* spriteSheetPath, int frameWidth, int frameHeight)
{
    p->position = startPos;
    p->speed = 200.0f;
    p->spriteSheet = LoadTexture(carli);
    p->frameWidth = frameWidth;
    p->frameHeight = frameHeight;
    p->currentFrame = 0;
    p->frameTime = 0.1f;  // 10 FPS
    p->frameCounter = 0.0f;
    p->direction = DIR_S;
    p->isMoving = false;
}

void UpdatePlayer(Player* p, float dt)
{
    Vector2 move = { 0.0f, 0.0f };
    p->isMoving = false;

    if (IsKeyDown(KEY_W)) { move.y -= 1; p->isMoving = true; }
    if (IsKeyDown(KEY_S)) { move.y += 1; p->isMoving = true; }
    if (IsKeyDown(KEY_A)) { move.x -= 1; p->isMoving = true; }
    if (IsKeyDown(KEY_D)) { move.x += 1; p->isMoving = true; }

    if (p->isMoving)
    {
        float len = sqrtf(move.x * move.x + move.y * move.y);
        if (len > 0) 
        {
            move.x /= len;
            move.y /= len;
        }

        p->position.x += move.x * p->speed * dt;
        p->position.y += move.y * p->speed * dt;

        if (move.y > 0.5f)
        {
            if (move.x < -0.5f) p->direction = DIR_SW;
            else if (move.x > 0.5f) p->direction = DIR_SE;
            else p->direction = DIR_S;
        }
        else if (move.y < -0.5f)
        {
            if (move.x < -0.5f) p->direction = DIR_NW;
            else if (move.x > 0.5f) p->direction = DIR_NE;
            else p->direction = DIR_N;
        }
        else 
        {
            if (move.x < 0) p->direction = DIR_W;
            else if (move.x > 0) p->direction = DIR_E;
        }

        p->frameCounter += dt;
        if (p->frameCounter >= p->frameTime) 
        {
            p->frameCounter = 0.0f;
            p->currentFrame = (p->currentFrame + 1) % 7 + 1;
        }
    }
    else 
        p->currentFrame = 0;  // idle frame
    
}

void DrawPlayer(Player* p)
{
    Rectangle source = 
    {
        .x = p->frameWidth * p->currentFrame,
        .y = p->frameHeight * p->direction,
        .width = p->frameWidth,
        .height = p->frameHeight
    };

    Vector2 origin = { p->frameWidth / 2.0f, p->frameHeight / 2.0f };
    
    DrawTextureRec(
         p->spriteSheet, 
         source, 
         (Vector2)
         { 
             p->position.x - origin.x, 
             p->position.y - origin.y 
         }, 
         WHITE
    );
}

void UnloadPlayer(Player* p)
{
    UnloadTexture(p->spriteSheet);
}
