#include "raylib.h"
#include <stdlib.h>
#include <ctime>

// Configuration Constants
#define TITLE "Axe Game"
#define FPS 60
#define GAMEPAD 0

int main()
{
    // Window dimensions
    int screenWidth  = 1270;
    int screenHeight = 768;

    // Player Configuration
    int playerX = screenWidth / 2;
    int playerY = screenHeight - 100;
    int playerRadius = 50;
    int playerSpeed = 15;

    // Enemy Configuration
    int enemyWidth = 50;
    int enemyHeight = 50;
    int enemySpeed = 10;
    int enemyX;
    int enemyY = -enemyHeight;

    // Other Game Configurations
    int score = 0;

    // Inicializa o gerador de números e a janela
    srand((unsigned)time(NULL));
    InitWindow(screenWidth, screenHeight, TITLE);
    SetTargetFPS(FPS);

    // Sorteia a posição inicial do inimigo
    enemyX = GetRandomValue(enemyWidth, screenWidth - enemyWidth);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Game Logic Begins
        DrawCircle(playerX, playerY, playerRadius, BLUE);
        DrawRectangle(enemyX, enemyY, enemyWidth, enemyHeight, RED);
        enemyY += enemySpeed;
        if (enemyY > screenHeight + enemyHeight)
        {
            score++;

            // Reset enemy position
            enemyY = -enemyHeight;
            enemyX = GetRandomValue(enemyWidth, screenWidth - enemyWidth);
        }

        // Movement Controls
        if ((IsKeyDown(KEY_D) || 
             IsKeyDown(KEY_RIGHT) || 
             IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
             (GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_X) > 0.5f)) &&
            playerX < screenWidth - playerRadius)
        {
            playerX += playerSpeed;
        }

        if ((IsKeyDown(KEY_A) || 
             IsKeyDown(KEY_LEFT) || 
             IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
             (GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_X) < -0.5f)) &&
            playerX > 0 + playerRadius)
        {
            playerX -= playerSpeed;
        }

        // Display Score
        DrawText(TextFormat("Score: %04d", score), 10, 10, 30, BLACK);
        EndDrawing();
    }
}
