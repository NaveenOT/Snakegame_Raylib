#include <raylib.h>
#include <string>
typedef struct head{
    Vector2 headpos;
    Vector2 size;
    struct head* next;
}Head;
void addbody(Head* snake){
    Head* temp = new Head();
    Head* ptr = snake;
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    temp->headpos = {ptr->headpos.x,ptr->headpos.y};
    ptr->next = temp;
    temp->next = NULL;
    temp->size = ptr->size;
}
void moveSnake(Head* snake, int keyin){
    Head* head = snake;
    Head* ptr = snake;
    Vector2 prevpos = head->headpos;
    while(ptr!= NULL){
        Vector2 currpos = ptr->headpos;
        ptr->headpos = prevpos;
        prevpos = currpos;
        ptr = ptr->next;
    }
     if(keyin == 1){
                head->headpos.x += 2;
                
        }else if(keyin == 2){
                head->headpos.x -= 2;
        }else if(keyin == 3){
                head->headpos.y -= 2;
        }else if(keyin == 4){
                head->headpos.y += 2;
        }
   
   
}
bool checkCollision(Head* snake){
    Head* ptr = snake;
    Head* temp = snake;
    Rectangle rect1 = {temp->headpos.x,temp->headpos.y, temp->size.x, temp->size.x};
    Rectangle rect2;
    if(ptr->next == NULL){
        return false;
    }
    ptr = ptr->next;
    while(ptr != NULL){
        rect2 ={ptr->headpos.x,ptr->headpos.y, ptr->size.x, ptr->size.x};
        ptr = ptr->next;
        if(CheckCollisionRecs(rect1, rect2)){
            return true;
        }else{
            return false;
        }
    }
}
void drawSnake(Head* snake){
    Head* ptr = snake;
    while(ptr != NULL){
       
        DrawRectangleV(ptr->headpos, ptr->size, RED);
        ptr = ptr->next;
    }
        
}
int main(){
    const int WIDTH = 360;
    const int HEIGHT = 360;
    InitWindow(WIDTH, HEIGHT, "MySnakeGame");
    SetTargetFPS(60);
    struct head snake;
    Vector2 headpos = {(float)WIDTH/2, (float)HEIGHT/2};
    snake.headpos = headpos;
    snake.size = {20, 20};
    snake.next = NULL;
    Vector2 foodpos;
    int keyin = 0;
    bool food = false;
    int x = GetRandomValue(50, 300);
    int y = GetRandomValue(50, 300);
        int points = 0;
        Rectangle rect;
    while(WindowShouldClose() == false){
        
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
        moveSnake(&snake, keyin);
        drawSnake(&snake);
        DrawCircleV(foodpos, 15, BLUE);
        rect = {snake.headpos.x, snake.headpos.y, snake.size.x, snake.size.y};
        if(CheckCollisionCircleRec(foodpos, 15, rect)){
            x = GetRandomValue(50, 300);
            y = GetRandomValue(50, 300);
            addbody(&snake);
            points++;
        }
        bool collide = checkCollision(&snake);
        //if(collide){
          //  points = 0;
        //}
        EndDrawing();

    }
    CloseWindow();
    return 0;
}