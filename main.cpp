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

    // Initialize the random number generator and game window
    srand((unsigned)time(NULL));
    InitWindow(screenWidth, screenHeight, TITLE);
    SetTargetFPS(FPS);

    // Initial Enemy Position
    enemyX = GetRandomValue(enemyWidth, screenWidth - enemyWidth);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Game Logic Begins
        // Player Spawn
        DrawCircle(playerX, playerY, playerRadius, BLUE);
        // Enemy Spawn
        DrawRectangle(enemyX, enemyY, enemyWidth, enemyHeight, RED);

        // Enemy Movement and Logic
        enemyY += enemySpeed;
        if (enemyY > screenHeight + enemyHeight || enemyY < -enemyHeight)
        {
            score++;

            // Reverse the enemy movement position and bouce torwards the player
            enemySpeed = -enemySpeed;
        }

        // Player Movement Controls
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
