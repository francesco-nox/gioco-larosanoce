#include "raylib.h"

int main(){
	InitWindow(800, 450, "Hello raylib!");
	SetTargetFPS(60);

    Texture2D backgrounds[6];
    backgrounds[0] = LoadTexture("background1.jpg");
    backgrounds[1] = LoadTexture("background2.jpg");
    backgrounds[2] = LoadTexture("background3.jpg");
    backgrounds[3] = LoadTexture("background4.jpg");
    backgrounds[4] = LoadTexture("background5.jpg");
    backgrounds[5] = LoadTexture("background6.jpg");
    
    float positions[6] = {0, 1100, 2200, 3300, 4400, 5500};
	while(!WindowShouldClose){
    
    float dt = GetFrameTime();
    for (int i = 0; i < 6; i++)
{
    positions[i] -= speed * dt;

    // se esce a sinistra, rimetti a destra dell'ultima
    if (positions[i] <= -backgrounds[i].width)
    {
        // trova il più a destra
        float maxX = positions[0];
        for (int j = 1; j < 6; j++)
            if (positions[j] > maxX) maxX = positions[j];

        positions[i] = maxX + backgrounds[i].width;
    }

    DrawTexture(backgrounds[i], positions[i], 0, WHITE);
}

	}
}
