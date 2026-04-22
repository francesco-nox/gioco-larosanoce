#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "stage.h"

typedef enum { MENU, PLAYING, WIN, LOSE } GameState;

int main() {
    InitWindow(800, 600, "Survival - Modulo Extra");
    SetTargetFPS(60);

    GameState state = MENU;
    Player p;
    Enemy e;
    StageManager sm;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (state == MENU) {
            if (IsKeyPressed(KEY_ENTER)) {
                InitPlayer(&p);
                InitEnemy(&e);
                InitStageManager(&sm);
                state = PLAYING;
            }
        } 
        else if (state == PLAYING) {
            bool levelChanged;
            UpdateStage(&sm, dt, &levelChanged);
            
            if (levelChanged) {
                if (sm.currentIdx >= MAX_STAGES) state = WIN;
                // Opzionale: reset posizioni al cambio livello
            }

            int curBg = sm.order[sm.currentIdx];
            UpdatePlayer(&p, sm.bgs[curBg].obstacles, sm.bgs[curBg].obstacleCount, dt);
            UpdateEnemy(&e, (Vector2){p.rect.x, p.rect.y}, sm.bgs[curBg].obstacles, sm.bgs[curBg].obstacleCount, dt);

            if (CheckCollisionRecs(p.rect, e.rect)) state = LOSE;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (state == MENU) {
            DrawText("PREMI INVIO PER GIOCARE", 200, 280, 20, RAYWHITE);
        } else if (state == PLAYING) {
            DrawStage(&sm);
            DrawPlayer(&p);
            DrawEnemy(&e);
            DrawText(TextFormat("Stage: %d/12", sm.currentIdx + 1), 10, 20, 20, YELLOW);
        } else if (state == WIN) {
            DrawText("HAI VINTO!", 320, 280, 40, GREEN);
        } else if (state == LOSE) {
            DrawText("HAI PERSO!", 320, 280, 40, RED);
        }

        EndDrawing();
    }

    UnloadStageManager(&sm);
    CloseWindow();
    return 0;
}