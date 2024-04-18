#include <complex.h>
#include <raylib.h>


namespace Game {

struct DrawTextComponent {

  float real;
  float imag;

  DrawTextComponent(float real, float imag) : real{real}, imag{imag} {};

  void Draw() { DrawText("Game", imag / 2, real / 2, 23, Color(RED)); }
};

struct RectangleBoyComponent {

  // position
  float imag = 0;
  float real = 0;
  
  
Rectangle player = {imag/2,real/2, 20 ,20};
  
  // eyesLeftSide
  float eyesLeftX = 2;
  float eyesLeftY = 7;

  // eyesRightSide
  float eyesRightX = 13;
  float eyesRightY = 7;

  RectangleBoyComponent(float imag, float real) : real{real}, imag{imag} {};

  void Draw() {

	   
    DrawRectangleRec(player,Color(RED));

    DrawRectangle(player.x  + eyesLeftX, player.y  + eyesLeftY, 20 - 15, 20 - 13,
                  Color(BLACK));
    DrawRectangle(player.x + eyesRightX, player.y + eyesRightY, 20 - 15,
                  20 - 13, Color(BLACK));

    Update();
  }

  void Update() {

    if (IsKeyDown(KEY_LEFT)) {
      player.x -= 100 * GetFrameTime();
    } else if (IsKeyDown(KEY_RIGHT)) {
      player.x += 100 * GetFrameTime();
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
    }
  }
};
}
int main() {




  auto text = Game::DrawTextComponent(0, 0);

  auto rectanglePlayer = Game::RectangleBoyComponent(800, 500);

  InitWindow(800, 500, "rectangle");

  while (!WindowShouldClose()) {

    BeginDrawing();

    ClearBackground(Color(WHITE));

    text.Draw();

    rectanglePlayer.Draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
