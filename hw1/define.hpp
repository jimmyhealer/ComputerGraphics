#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <cmath>
#include <functional>
#include <fstream>
#include <chrono>
#include <GL/glut.h>
#include <GL/glext.h>

#define __DEBUG__

#ifdef __DEBUG__
using namespace std;
#define DEBUG(x) std::cerr << #x << " = " << x << ", ";
#define DEBUGN(x) std::cerr << #x << " = " << x << std::endl;
#else
#define DEBUG(x)
#endif

typedef int menu_id;

enum DRAW_MODE {NONE, LINE, CIRCLE, TRIANGLE, POLYGON, TEXT};
enum COLOR {RED, GREEN, BLUE, BLACK, WHITE};
enum MORE_MENU {CLEAR, QUIT, FULLMODE};

#include "Utility/PaintBoard.hpp"
#include "Utility/RGBAColor.hpp"

int window_height = 512;
int window_width = 512;
int draw_mode = DRAW_MODE::NONE;
int g_now_color = COLOR::BLUE;
float g_line_width = 1.0;
float g_point_size = 1.0;
bool is_full_mode = false;
bool is_insert_mode = false;
bool is_full_screen = false;
bool is_changed = true;
bool is_mouse_down = false;

bool is_open_palette_plane = false;

bool is_motion = false;

int pos_x, pos_y;
int origin_window_width = window_width, origin_window_height = window_height;
std::string draw_mode_str[] = {"None", "Line", "Circle", "Triangle", "Polygon", "Text"};
std::string color_str[] = {"Red", "Green", "Blue", "Black", "White"};
std::string more_menu_str[] = {"Clear", "Quit", "Fill Mode"};
RGBAColor g_now_color_rgba = RGBAColor(g_now_color);

#include "Draws/DrawType.hpp"
#include "DrawStates.hpp"
#include "UI/UIType.hpp"

StringObject *insert_str;
PlaneObject *leftNavPlane, *rightNavPlane, *NavBarPlane, *ToolBarPlane, *PalettePlane;
PolygonObject *polygon = nullptr;

menu_id top_menu, draw_menu, color_menu, line_width_menu, point_size_menu, more_menu;

DrawStatePresistence draw_state_presistence;

DrawObject *now_draw_object = nullptr;

TextObject *text_line_width;
ColorObject *now_color_object;