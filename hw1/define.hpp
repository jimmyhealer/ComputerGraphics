#include <iostream>
#include <vector>
#include <utility>
#include <GL/glut.h>

typedef int menu_id;

enum COLOR {RED, GREEN, BLUE, BLACK, WHITE};
int window_height = 512;
int window_width = 512;
int now_color = COLOR::BLUE;
float line_width = 1.0;
bool is_mouse_down = false;

int pos_x, pos_y;

#include "Utility/RGBAColor.hpp"
#include "Draws/DrawType.hpp"
#include "DrawStates.hpp"

PaintBoardObject *paint_board;
