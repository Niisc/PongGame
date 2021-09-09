#include "include/raylib.h"
#include "include/rlgl.h"
#include <math.h>
#include <time.h>
typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    int radius;
} Ball;

int main(void)
{
    const int screenWidth = 1366;
    const int screenHeight = 768;
    int score1 = 0, score2 = 0;
    InitWindow(screenWidth, screenHeight, "Fps stuff");
    Camera2D camera = {0};
    camera.zoom = 1.f;
    SetTargetFPS(60);
    Rectangle rect1 = {0};
    Rectangle rect2 = {0};
    rect1.x = 5.f;
    rect1.y = screenHeight/2;
    rect1.height = 80;
    rect1.width = 10;

    rect2.x = screenWidth-15.f;
    rect2.y = screenHeight/2;
    rect2.height = 80;
    rect2.width = 10;
    Ball ball = {0};
    ball.speed = (Vector2){GetRandomValue(3,4),GetRandomValue(-4,4)};
    ball.speed.x = ball.speed.x + ball.speed.x * -(GetRandomValue(0,1))*2;
    ball.radius = 15;
    ball.position = (Vector2){screenWidth/2, screenHeight/2};
    ToggleFullscreen();
    while (!WindowShouldClose())
    {
        rect1.y = rect1.y + 8 * (-IsKeyDown(KEY_W)*(rect1.y > 0.f) + IsKeyDown(KEY_S)*(rect1.y > -screenHeight));
        rect2.y = rect2.y + 8 * (-IsKeyDown(KEY_UP)*(rect2.y > 0.f) + IsKeyDown(KEY_DOWN)*(rect2.y > -screenHeight));

        ball.speed.y = ball.speed.y + ((ball.position.y < 0.0f)||(ball.position.y > screenHeight))*2*-ball.speed.y + ((ball.position.x < 0)||(ball.position.x > screenWidth))*(ball.speed.y+GetRandomValue(-5,5));
        ball.speed.x = ball.speed.x + (CheckCollisionCircleRec(ball.position, ball.radius, rect2)||CheckCollisionCircleRec(ball.position, ball.radius, rect1))*2*-(ball.speed.x) + ((ball.position.x < 0)||(ball.position.x > screenWidth))*(ball.speed.x*2*-GetRandomValue(0,1));

        ball.position.x =  (ball.position.x + ball.speed.x)*((ball.position.x > 0)&&(ball.position.x < screenWidth)) + (screenWidth/2)*((ball.position.x < 0)||(ball.position.x > screenWidth));
        ball.position.y =  (ball.position.y + ball.speed.y)*((ball.position.x > 0)&&(ball.position.x < screenWidth)) + (screenHeight/2)*((ball.position.x < 0)||(ball.position.x > screenWidth));
        score1 += (ball.position.x > screenWidth);
        score2 += (ball.position.x < 0);
        BeginDrawing();

            ClearBackground(BLACK);
            BeginMode2D(camera);
            DrawRectangleRec(rect1, WHITE);
            DrawRectangleRec(rect2, WHITE);
            DrawCircleV(ball.position, ball.radius, WHITE);
            DrawText(TextFormat("%d", score1), screenWidth/2-40, 10, 40, WHITE);
            DrawText(TextFormat("%d", score2), screenWidth/2+40, 10, 40, WHITE);
		    EndMode2D();
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
