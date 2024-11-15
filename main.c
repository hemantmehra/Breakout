#include <stdio.h>
#include <raylib.h>

struct _box {
    Rectangle rec;
    int alive;
};

typedef struct _box Box;

#define BOX_COUNT 36

int main()
{
    int screenWidth = 800;
    int screenHeight = 600;
    int score = 0;

    InitWindow(screenWidth, screenHeight, "Breakout");
    SetTargetFPS(40);

    Rectangle box1 = {400, 500, 10, 10};
    Rectangle paddle = {400, 550, 60, 10};
    Vector2 speed = {6.0f, -5.0f};
    bool collision = false;

    Box boxes[BOX_COUNT];
    int start_x = 50;
    int start_y = 50;

    for(int i=0; i < BOX_COUNT/3; i++) {
        Box b = {{start_x + (i * 50), start_y, 60, 40}, 1};
        boxes[i] = b;
    }

    for(int i=BOX_COUNT/3,j=0; i < (2 * BOX_COUNT)/3; i++,j++) {
        Box b = {{start_x + (j * 50), start_y + 40 + 5, 60, 40}, 1};
        boxes[i] = b;
    }

    for(int i=(2 * BOX_COUNT)/3, j=0; i < BOX_COUNT; i++, j++) {
        Box b = {{start_x + (j * 50), start_y + 80 + 10, 60, 40}, 1};
        boxes[i] = b;
    }

    while(!WindowShouldClose())
    {
        box1.x += speed.x;
        box1.y += speed.y;

        if (box1.x < 0 || box1.x > GetScreenWidth()) speed.x *= -1.0f;
        if (box1.y < 0 || box1.y > GetScreenHeight()) {
            speed.y *= -1.0f;
        }
        if (box1.y > GetScreenHeight()) score--;

        collision = CheckCollisionRecs(box1, paddle);
        if (collision) {
            speed.y *= -1.0f;
        }

        for (int i = 0; i < BOX_COUNT; i++) {
            Rectangle target_rec = boxes[i].rec;
            collision = CheckCollisionRecs(box1, boxes[i].rec);
            if (collision && boxes[i].alive) {
                boxes[i].alive = 0;
                score++;
                Rectangle rec = GetCollisionRec(box1, boxes[i].rec);

                int x1 = target_rec.x;
                int y1 = target_rec.y;
                int x2 = target_rec.x + target_rec.width;
                int y2 = target_rec.y + target_rec.height;

                int _x1 = rec.x;
                int _y1 = rec.y;
                int _x2 = rec.x + rec.width;
                int _y2 = rec.y + rec.height;

                if ((y1 < _y1 && _y2 < y2)) {
                    speed.x *= -1.0f;
                }
                else if (x1 < _x1 && _x2 < x2) {
                    speed.y *= -1.0f;
                }
                else {
                    speed.x *= -1.0f;
                    speed.y *= -1.0f;
                }
            }
        }
        
        if (IsKeyDown(KEY_RIGHT)) {
            paddle.x += 5;
        }

        if (IsKeyDown(KEY_LEFT)) {
            paddle.x -= 5;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextFormat("SCORE: %d", score), 10, 10, 20, WHITE);
        DrawRectangleRec(box1, ORANGE);
        DrawRectangleRec(paddle, WHITE);
        for (int i = 0; i < BOX_COUNT; i++) {
            if (boxes[i].alive && i > 0 && i < BOX_COUNT/3)
                DrawRectangleRec(boxes[i].rec, BLUE);
            else if (boxes[i].alive && i > BOX_COUNT/3 && i < (2 * BOX_COUNT)/3)
                DrawRectangleRec(boxes[i].rec, RED);
            else if (boxes[i].alive && i > (2 * BOX_COUNT)/3 && i < BOX_COUNT)
                DrawRectangleRec(boxes[i].rec, GREEN);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
