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
    int screenWidth = 1270;
    int screenHeight = 768;

    // Player Configuration
    int playerX = screenWidth / 2;
    int playerY = screenHeight - 100;
    int playerRadius = 50;
    int playerSpeed = 15;
    // Player Edges
    int playerXEdgeLeft = playerX - playerRadius;
    int playerXEdgeRight = playerX + playerRadius;
    int playerYEdgeTop = playerY - playerRadius;
    int playerYEdgeBottom = playerY + playerRadius;

    // Enemy Configuration
    int enemyWidth = 50;
    int enemyHeight = 50;
    int enemySpeed = 10;
    int enemyX;
    int enemyY = -enemyHeight;
    // Enemy Edges
    int enemyXEdgeLeft = enemyX;
    int enemyXEdgeRight = enemyX + enemyWidth;
    int enemyYEdgeTop = enemyY;
    int enemyYEdgeBottom = enemyY + enemyHeight;

    // Other Game Configurations
    bool gameOver = false;
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

        if (gameOver)
        {
            DrawText("Game Over!", screenWidth / 2 - MeasureText("Game Over!", 50) / 2, screenHeight / 2 - 25, 50, RED);
            DrawText(TextFormat("Final Score: %04d", score), screenWidth / 2 - MeasureText(TextFormat("Final Score: %04d", score), 30) / 2, screenHeight / 2 + 40, 30, BLACK);
            DrawText("Press R or (Start) to Restart", screenWidth / 2 - MeasureText("Press ENTER or (A) to Restart", 20) / 2, screenHeight / 2 + 80, 20, DARKGRAY);

            // Restart Game Logic
            if ((IsKeyPressed(KEY_R) || 
                IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_MIDDLE_RIGHT)))
            {
                score = 0;
                enemyY = -enemyHeight;
                enemyX = GetRandomValue(enemyWidth, screenWidth - enemyWidth);
                playerX = screenWidth / 2;
                playerY = screenHeight - 100;
                gameOver = false;
            }
        } else {
            // Player Spawn
            DrawCircle(playerX, playerY, playerRadius, BLUE);
            // Enemy Spawn
            DrawRectangle(enemyX, enemyY, enemyWidth, enemyHeight, RED);

            // Enemy Movement and Logic
            enemyY += enemySpeed;
            if (enemyY > screenHeight + enemyHeight || enemyY < -enemyHeight)
            {
                score++;
                DrawRectangle(enemyX, enemyY, enemyWidth, enemyHeight, RED);

                // Reverse the enemy movement position
                // to do: bounce towards the player
                enemySpeed = -enemySpeed;
            }

            // Updates Edges Positions
            // Player Edges
            playerXEdgeLeft = playerX - playerRadius;
            playerXEdgeRight = playerX + playerRadius;
            playerYEdgeTop = playerY - playerRadius;
            playerYEdgeBottom = playerY + playerRadius;
            
            // Enemy Edges
            enemyXEdgeLeft = enemyX;
            enemyXEdgeRight = enemyX + enemyWidth;
            enemyYEdgeTop = enemyY;
            enemyYEdgeBottom = enemyY + enemyHeight;

            // Check for collision
            if ((enemyXEdgeRight >= playerXEdgeLeft) &&
                (enemyXEdgeLeft <= playerXEdgeRight) &&
                (enemyYEdgeBottom >= playerYEdgeTop) &&
                (enemyYEdgeTop <= playerYEdgeBottom))
            {
                gameOver = true;
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
        }
        EndDrawing();
    }
}
