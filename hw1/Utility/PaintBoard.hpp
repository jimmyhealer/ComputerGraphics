int paint_board_width = 512;
int paint_board_height = 512;
int paint_board_x = 120;
int paint_board_y = 0;

namespace PaintBoard {
  void update(float width, float height) {
    paint_board_width = width - paint_board_x;
    paint_board_height = height - paint_board_y - 90;
  }

  bool isInside(float x, float y) {
    return x >= paint_board_x && x <= paint_board_x + paint_board_width && y >= paint_board_y && y <= paint_board_y + paint_board_height;
  }

  std::pair<float, float> getCanDrawRange(float x, float y) {
    if(x < paint_board_x) x = paint_board_x;
    if(x > paint_board_x + paint_board_width) x = paint_board_x + paint_board_width;
    if(y < paint_board_y) y = paint_board_y;
    if(y > paint_board_y + paint_board_height) y = paint_board_y + paint_board_height;
    return {x, y};
  }

  float getCanDrawRange(float x, float y, float radius) {
    if(x < paint_board_x) x = paint_board_x;
    if(x > paint_board_x + paint_board_width) x = paint_board_x + paint_board_width;
    if(y < paint_board_y) y = paint_board_y;
    if(y > paint_board_y + paint_board_height) y = paint_board_y + paint_board_height;
    if(x - radius < paint_board_x) radius = x - paint_board_x;
    if(x + radius > paint_board_x + paint_board_width) radius = paint_board_x + paint_board_width - x;
    if(y - radius < paint_board_y) radius = y - paint_board_y;
    if(y + radius > paint_board_y + paint_board_height) radius = paint_board_y + paint_board_height - y;
    return radius;
  }
}