#include <raylib.h>
#include <string>
#include <iostream>
#include <deque>
const int WIDTH = 720;
const int HEIGHT = 720;
const float cellsize = 25;
const int cellcount = WIDTH/cellsize;

class Snake{
    public:
        std::deque<Vector2> body;
    Snake(){
        body = {{25, 10}, {26, 10}, {27, 10}};
    }
    void DrawSnake(){
    for(const auto & i: body){
            float x = i.x;
            float y = i.y;
            DrawRectangle(x * cellsize, y*cellsize, cellsize, cellsize, RED);
        }
    }
    void moveSnake(int keyin){
        Vector2 temp = body[0];
        snakeOutOfBounds();
        if(keyin == 1){
            body[0].x += 0.5;
        }else if(keyin == 2){
                body[0].x -= 0.5;
        }else if(keyin == 3){
                body[0].y -= 0.5;
        }else if(keyin == 4){
                body[0].y += 0.5;
        }
        Vector2 temp2;
        for(int i = 1; i < body.size(); i++){
            temp2 = body[i];
            body[i] = temp;
            temp = temp2;
        }
    }
    void growSnake(int keyin){
        Vector2 temp = body.back();
        if(keyin == 1){
            temp = {temp.x-1, temp.y};
            body.push_back(temp);
        }else if(keyin == 2){
             temp = {temp.x+1, temp.y};
            body.push_back(temp);
        }
        else if(keyin == 3){
             temp = {temp.x, temp.y-1};
            body.push_back(temp);
        }
        else if(keyin == 4){
             temp = {temp.x, temp.y+1};
            body.push_back(temp);
        }
    }
    bool checkSnakeCollision() {
    const Vector2& head = body[0];
    for (int i = 1; i < body.size(); i++) {
        if (head.x == body[i].x && head.y == body[i].y) {
            return true;
        }
    }
    return false;
}
    void snakeOutOfBounds(){
        Vector2 head = body[0];
        if(head.x > cellcount){
            body[0].x = 0;
        }else if(head.x  <= 0){
            body[0].x = cellcount;
        }else if(head.y > cellcount){
            body[0].y = 0;
        }else if(head.y <= 0){
            body[0].y = cellcount;
        }

    }
};

    

int main(){

    Snake snake = Snake();
    InitWindow(WIDTH, HEIGHT, "MySnakeGame");
    SetTargetFPS(30);
    Vector2 foodpos;
    int keyin = 0;
    bool food = false;
    int x = GetRandomValue(1, cellcount - 1);
    int y = GetRandomValue(1, cellcount - 1);
        int points = 0;
        Rectangle rect;
    int gameState = 0;
    
    while(WindowShouldClose() == false){
       while(gameState == 0){
            BeginDrawing();
            ClearBackground(GRAY);
            DrawText("Press ENTER To Start", 165, HEIGHT / 2, 35, BLACK);
            if(IsKeyPressed(KEY_ENTER)){
                gameState = 1;
            }
            EndDrawing();
    }
        foodpos = {(float)x, (float)y};
        if(IsKeyPressed(KEY_RIGHT)) {
            if(keyin == 2){
                keyin = 2;
            }else{
            keyin = 1;
            }
            
        }
        if(IsKeyPressed(KEY_LEFT)) {
            if(keyin == 1){
                keyin = 1;
            }else{
            keyin = 2;
            }
        }
        if(IsKeyPressed(KEY_UP)) {
            if(keyin == 4){
                keyin = 4;
            }else{
            keyin = 3;
            }
            
        }
        if(IsKeyPressed(KEY_DOWN)) {
            
            if(keyin == 3){
                keyin = 3;
            }else{
            keyin = 4;
            }
        }
        BeginDrawing();
        ClearBackground(LIME);
        std::string scoreText = "Score: " + std::to_string(points);
        DrawText(scoreText.c_str(), WIDTH/2, 20, 30, BLACK);
        snake.DrawSnake();
        snake.moveSnake(keyin);
        DrawRectangle(foodpos.x * cellsize, foodpos.y * cellsize, cellsize, cellsize, BLUE);
        Rectangle rect1 = {snake.body[0].x * cellsize, snake.body[0].y * cellsize, cellsize, cellsize};
        Rectangle rect2 = {foodpos.x * cellsize, foodpos.y * cellsize, cellsize, cellsize};
        if(CheckCollisionRecs(rect1, rect2)){
            x = GetRandomValue(1, cellcount - 1);
            y = GetRandomValue(1, cellcount -1);
            snake.growSnake(keyin);
            points++;
        }
        if(snake.checkSnakeCollision() && points > 1){
            while(!IsKeyPressed(KEY_ENTER)){
                ClearBackground(RAYWHITE);
                std::string final = "You Got " + std::to_string(points) + " Points\n";
                DrawText(final.c_str(), 185, HEIGHT/2 - 50, 30, BLACK);
                DrawText("Press Enter To Exit !",175, HEIGHT/2 - 10, 30, BLACK);
                EndDrawing();
            }
            CloseWindow();
            
        }
        EndDrawing();

        }
    
        
    
    return 0;
}