#include <cstdio>
#include <raylib.h>

namespace Game {



struct CollisionState {

	bool collisionState = false;

};	


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
            Update();
        }

        void Update() {
            if (IsKeyDown(KEY_LEFT)) {
                player.x -= 100 * GetFrameTime();
                eyesLeftX = 0;
                eyesRightX = 11;
            }
            else if (IsKeyDown(KEY_RIGHT)) {
                player.x += 100 * GetFrameTime();
                eyesLeftX = 4;
                eyesRightX = 15;
            }
            else if (IsKeyDown(KEY_UP)) {
                player.y -= 100 * GetFrameTime();
                eyesLeftY = -3;
                eyesRightY = -3;
            }
            else if (IsKeyDown(KEY_DOWN)) {
                player.y += 100 * GetFrameTime();
                eyesLeftY = 14;
                eyesRightY = 14;
            }
            else {
                eyesLeftY = 7;
                eyesRightY = 7;
                eyesRightX = 13;
                eyesLeftX = 2;
            }
        }
    };

    struct LevelComponent {
        Rectangle box = { 0 };

	struct Game::CollisionState *collisionState;
	LevelComponent(Rectangle box , struct Game::CollisionState *collisionState) : box{ box },  collisionState{collisionState} {};

        void Draw() {

	printf("%d ", collisionState->collisionState);
            DrawRectangle(800 / 2 - 190, 500 / 2 - 10, 400, 400, Color(GRAY));
        
	
	if(collisionState->collisionState){
	    DrawRectangleRec(box, Color(GREEN));
	}else {
	
	    DrawRectangleRec(box, Color(BLACK));
	}
	
	}
    };

}

int main() {
    Rectangle player = { 800 / 2, 500 / 2, 20, 20 };
    Rectangle box = { 800 / 2 - 40, 500 / 2, 16, 16 };

    struct Game::CollisionState *collisionState, collisionState1;
    collisionState = & collisionState1;
    auto text = Game::DrawTextComponent(0, 0);
    auto rectanglePlayer = Game::RectangleBoyComponent(player);
    auto levelFloor = Game::LevelComponent(box, collisionState);

    InitWindow(800, 500, "rectangle");

    while (!WindowShouldClose()) {
        rectanglePlayer.Update(); // Update player position

        bool collisions = Game::collision(rectanglePlayer.player, box); // Check collision with updated player position

        BeginDrawing();
        ClearBackground(Color(WHITE));

        text.Draw();
        levelFloor.Draw();

        if (collisions) {
	    collisionState->collisionState = true;
        }


        rectanglePlayer.Draw();

        EndDrawing();
    }

    CloseWindow();
   
    
   
    return 0;
}

