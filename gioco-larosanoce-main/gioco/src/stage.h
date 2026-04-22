#ifndef STAGE_H
#define STAGE_H
#include "raylib.h"

#define MAX_STAGES 12
#define MAX_OBSTACLES_PER_STAGE 20

typedef struct Stage {
    Texture2D texture;
    Rectangle obstacles[MAX_OBSTACLES_PER_STAGE];
    int obstacleCount;
} Stage;

typedef struct StageManager {
    Stage bgs[7]; // background.png (0) + background1-6.jpg
    int order[MAX_STAGES];
    int currentIdx;
    float timer;
} StageManager;

void InitStageManager(StageManager *sm);
void UpdateStage(StageManager *sm, float dt, bool *levelChanged);
void DrawStage(StageManager *sm);
void UnloadStageManager(StageManager *sm);

#endif