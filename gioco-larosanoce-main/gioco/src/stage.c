#include "stage.h"
#include <stdlib.h>

void InitStageManager(StageManager *sm) {
    // Caricamento Texture
    sm->bgs[0].texture = LoadTexture("background.jpg");
    sm->bgs[1].texture = LoadTexture("background1.jpg");
    sm->bgs[2].texture = LoadTexture("background2.jpg");
    sm->bgs[3].texture = LoadTexture("background3.jpg");
    sm->bgs[4].texture = LoadTexture("background4.jpg");
    sm->bgs[5].texture = LoadTexture("background5.jpg");
    sm->bgs[6].texture = LoadTexture("background6.jpg");

    // Definizione Hitbox Generiche (Bordi sopra e sotto)
    for(int i = 0; i < 7; i++) {
        sm->bgs[i].obstacles[0] = (Rectangle){ 0, -10, 800, 20 }; // Sopra
        sm->bgs[i].obstacles[1] = (Rectangle){ 0, 590, 800, 20 }; // Sotto
        sm->bgs[i].obstacleCount = 2;
    }

    // Aggiungi hitbox specifiche per i quadrati (Esempio per background1)
    // Qui dovresti inserire le coordinate reali dei quadrati neri visibili nell'immagine
    sm->bgs[1].obstacles[2] = (Rectangle){ 200, 150, 100, 100 }; 
    sm->bgs[1].obstacles[3] = (Rectangle){ 500, 350, 100, 100 };
    sm->bgs[1].obstacleCount = 4;

    // Configurazione ordine: 0 poi 1 fisse
    sm->order[0] = 0;
    sm->order[1] = 1;
    
    // Riempimento casuale per gli altri 10 slot (utilizzando 1-6 max 2 volte)
    int counts[7] = {0}; counts[1] = 1; // background1 è già usato una volta
    for (int i = 2; i < MAX_STAGES; i++) {
        int r;
        do { r = GetRandomValue(1, 6); } while (counts[r] >= 2);
        sm->order[i] = r;
        counts[r]++;
    }

    sm->currentIdx = 0;
    sm->timer = 0;
}

void UpdateStage(StageManager *sm, float dt, bool *levelChanged) {
    sm->timer += dt;
    *levelChanged = false;
    if (sm->timer > 7.0f) { // Cambia ogni 7 secondi
        sm->timer = 0;
        sm->currentIdx++;
        *levelChanged = true;
    }
}

void DrawStage(StageManager *sm) {
    DrawTexture(sm->bgs[sm->order[sm->currentIdx]].texture, 0, 0, WHITE);
    // Opzionale: decommenta per vedere le hitbox per debug
    /*
    for(int i=0; i<sm->bgs[sm->order[sm->currentIdx]].obstacleCount; i++)
        DrawRectangleLinesEx(sm->bgs[sm->order[sm->currentIdx]].obstacles[i], 2, GREEN);
    */
}

void UnloadStageManager(StageManager *sm) {
    for(int i=0; i<7; i++) UnloadTexture(sm->bgs[i].texture);
}