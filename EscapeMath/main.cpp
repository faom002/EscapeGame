#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <vector>

namespace Game {


bool collision(Rectangle player, Rectangle box) {
    return CheckCollisionRecs(player, box);
}

struct DrawTextComponent {
    float real;
    float imag;

    DrawTextComponent(float real, float imag) : real{ real }, imag{ imag } {};

    void Draw() { DrawText("EscapeGame", imag / 2, real / 2, 23, Color(RED)); }
};










struct RectangleBoyComponent {
    Rectangle player = { 0 };

    float eyesLeftX = 2;
    float eyesLeftY = 7;
    float eyesRightX = 13;
    float eyesRightY = 7;

    RectangleBoyComponent(Rectangle player) : player{ player } {};

    void Draw() {
        DrawRectangleRec(player, Color(RED));
        DrawRectangle(player.x + eyesLeftX, player.y + eyesLeftY, 20 - 15, 20 - 13, Color(BLACK));
        DrawRectangle(player.x + eyesRightX, player.y + eyesRightY, 20 - 15, 20 - 13, Color(BLACK));
    }

    void Update() {
        if (IsKeyDown(KEY_LEFT)) {
            player.x -= 100 * GetFrameTime();
            eyesLeftX = 0;
            eyesRightX = 11;
        } else if (IsKeyDown(KEY_RIGHT)) {
            player.x += 100 * GetFrameTime();
            eyesLeftX = 4;
            eyesRightX = 15;
        } else if (IsKeyDown(KEY_UP)) {
            player.y -= 100 * GetFrameTime();
            eyesLeftY = -3;
            eyesRightY = -3;
        } else if (IsKeyDown(KEY_DOWN)) {
            player.y += 100 * GetFrameTime();
            eyesLeftY = 14;
            eyesRightY = 14;
        } else {
            eyesLeftY = 7;
            eyesRightY = 7;
            eyesRightX = 13;
            eyesLeftX = 2;
        }
    }
};

struct LevelBoxes {
    std::vector<Rectangle> boxes;
    std::vector<bool> collisionStates; // Store collision state for each box
 
    bool textCollision;


    LevelBoxes(std::vector<Rectangle> boxes) : boxes{boxes} {
        collisionStates.resize(boxes.size(), false); // Initialize collision states for all boxes to false
    }

    void Draw() {
       

      int num1 = 2; 
    int num2 = 3;
    int num3 = 5;
    int num4 = 23;

    std::vector<int> numbers;
    numbers.push_back(num1);
    numbers.push_back(num2);
    numbers.push_back(num3);
    numbers.push_back(num4);

    int correctAnswer = 6;

    bool num2Chosen = false;
    bool num3Chosen = false;
    bool goal = false;

    for (size_t i = 0; i < boxes.size(); ++i) {
        if (collisionStates[i]) {
            if (numbers[i] == 2) {
                num2Chosen = true;
            } else if (numbers[i] == 3) {
                num3Chosen = true;
            }

            if (num2Chosen && num3Chosen) {
                DrawRectangle(800/2 -110, 500/2 + 180,50, 10, Color(WHITE));


		goal = true;

            }


	    if (goal) {

		    DrawText("You Win", 800/2 -100, 500/2, 100, Color(RED));
	    
	    }


                DrawRectangleRec(boxes[i], Color(GREEN));

            DrawText(TextFormat("%d", numbers[i]), boxes[i].x, boxes[i].y, 20, RED);
        } else {
            DrawRectangleRec(boxes[i], Color(BLACK));
            DrawText(TextFormat("%d", numbers[i]), boxes[i].x, boxes[i].y, 20, BLUE);
        }
    }

    // Draw the correct answer
    DrawText(TextFormat("%d", correctAnswer), 800 / 2 - 80, 500 / 2 + 20, 30, BLACK);        
    }

    void UpdateCollisionState(const Rectangle& player) {
        for (size_t i = 0; i < boxes.size(); ++i) {
            if (collision(player, boxes[i])) {
                collisionStates[i] = true;
            }
        }
    }
};

struct LevelComponent {
    

	Rectangle map = {800/2 -190, 500/2 -10 ,200 ,200};

 
	bool collisionState = false;	
	void Draw() {
    
	
	
	
	    DrawRectangleRec(map, Color(GRAY));
    
    
    
    }



    void UpdateCollisionState( Rectangle& player) {
            printf("%d ", collisionState);
	    printf("player x movement %lf ", player.x);
	    printf("player y movement %lf ", player.y);
	    if ( collision(player, map)) {
             

		    collisionState = true;
            }else {
	    
		   player.x = 400;
		   player.y = 255;
		    collisionState = false;
	    
	    }
    }
};

}

int main() {
    Rectangle player = { 800 / 2, 500 / 2, 20, 20 };
    Rectangle box1 = { 800 / 2 - 40, 500 / 2, 16, 16 };
    Rectangle box2 = { 800 / 2 - 40, 500 / 2 + 40, 16, 16 };
    Rectangle box3 = { 800 / 2 - 120, 500 / 2 + 40, 16, 16 };
    Rectangle box4 = { 800 / 2 - 120, 500 / 2, 16, 16 };

    std::vector<Rectangle> boxesToPassOn;
    boxesToPassOn.push_back(box1);
    boxesToPassOn.push_back(box2);
    boxesToPassOn.push_back(box3);
    boxesToPassOn.push_back(box4);

    auto text = Game::DrawTextComponent(0, 0);
    auto rectanglePlayer = Game::RectangleBoyComponent(player);
    auto levelFloor = Game::LevelComponent();
    auto boxes = Game::LevelBoxes(boxesToPassOn);

    InitWindow(800, 500, "rectangle");

    while (!WindowShouldClose()) {
        rectanglePlayer.Update(); // Update player position

        // Update collision state for all boxes
        boxes.UpdateCollisionState(rectanglePlayer.player);
	levelFloor.UpdateCollisionState(rectanglePlayer.player);
        BeginDrawing();
        ClearBackground(Color(WHITE));

        text.Draw();
        levelFloor.Draw();
        boxes.Draw();
        rectanglePlayer.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

