#include "raylib.h"

// Configuration Constants
#define TITLE "Axe Game"
#define FPS 60
#define GAMEPAD 0

int main()
{
    // Window dimensions
    int width  = 1270;
    int height = 768;

    // Circle Coordinates
    int circleX = width /2;
    int circleY = height/2;
    int circleRadius = 50;
    int circleSpeed = 5;

    InitWindow(width, height, TITLE);
    SetTargetFPS(FPS);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Game Logic Begins
        DrawCircle(circleX, circleY, circleRadius, BLUE);

        // Movement Controls
        if (IsKeyDown(KEY_D) || 
            IsKeyDown(KEY_RIGHT) || 
            IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
            (GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_X) > 0.5f))
        {
            circleX += circleSpeed;
        }

        if (IsKeyDown(KEY_A) || 
            IsKeyDown(KEY_LEFT) || 
            IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
            (GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_X) < -0.5f))
        {
            circleX -= circleSpeed;
        }

        // Game Logic Ends
        EndDrawing();
    }
}
