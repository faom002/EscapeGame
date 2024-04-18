#include <complex.h>
#include <iostream>
#include <ostream>
#include <raylib.h>

struct DrawTextComponent {

  float real;
  float imag;

  DrawTextComponent(float real, float imag) : real{real}, imag{imag} {};

  void Draw() { DrawText("Game", imag / 2, real / 2, 23, Color(RED)); }
};

struct RectangleBoyComponent {

  // position
  float imag;
  float real;

  // eyesLeftSide
  float eyesLeftX = 2;
  float eyesLeftY = 7;

  // eyesRightSide
  float eyesRightX = 13;
  float eyesRightY = 7;

  RectangleBoyComponent(float imag, float real) : real{real}, imag{imag} {};

  void Draw() {

    DrawRectangle(imag / 2, real / 2, 20, 20, Color(RED));

    DrawRectangle(imag / 2 + eyesLeftX, real / 2 + eyesLeftY, 20 - 15, 20 - 13,
                  Color(BLACK));
    DrawRectangle(imag / 2 + eyesRightX, real / 2 + eyesRightY, 20 - 15,
                  20 - 13, Color(BLACK));

    Update();
  }

  void Update() {

    if (IsKeyDown(KEY_LEFT)) {
      imag -= 100 * GetFrameTime();
    } else if (IsKeyDown(KEY_RIGHT)) {
      imag += 100 * GetFrameTime();
    } else if (IsKeyDown(KEY_UP)) {
      real -= 100 * GetFrameTime();

      eyesLeftY = -3;

      eyesRightY = -3;

    } else if (IsKeyDown(KEY_DOWN)) {

      real += 100 * GetFrameTime();

      eyesLeftY = 14;

      eyesRightY = 14;
    } else {

      eyesLeftY = 7;

      eyesRightY = 7;
    }
  }
};

int main() {

  auto text = DrawTextComponent(0, 0);

  auto rectanglePlayer = RectangleBoyComponent(800, 500);

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
