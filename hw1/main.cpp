#include "define.hpp"

void mouseCallback(int button, int state, int x, int y) {
  y = window_height - y;
  if(button != GLUT_LEFT_BUTTON) return;

  if((is_open_palette_plane || !PaintBoard::isInside(x, y)) && state == GLUT_DOWN){
    if(NavBarPlane->isClickItem(x, y, false)) return;
    if(leftNavPlane->isClickItem(x, y)) return;
    if(ToolBarPlane->isClickItem(x, y)) return;
    if(PalettePlane->isClickItem(x, y)) return;
    PalettePlane->setVisibility(false);
    is_open_palette_plane = false;
    return;
  }

  if(draw_mode != DRAW_MODE::NONE && state == GLUT_DOWN && PaintBoard::isInside(x, y)) {
    is_motion = false;
    switch(draw_mode) {
      case DRAW_MODE::LINE:
        now_draw_object = new LineObject(x, y);
        break;
      case DRAW_MODE::CIRCLE:
        now_draw_object = new CircleObject(x, y);
        break;
      case DRAW_MODE::TRIANGLE:
        now_draw_object = new TriangleObject(x, y);
        break;
      case DRAW_MODE::POLYGON:
        if(polygon == nullptr) {
          polygon = new PolygonObject(x, y);
          draw_state_presistence.add(polygon);
        } 
        else {
          polygon->addPoint(x, y);
          if(polygon->isClosed()) {
            polygon = nullptr;
          }
        }
        break;   
      case DRAW_MODE::TEXT:
        if(is_insert_mode) break;
        is_insert_mode = 1;
        insert_str = new StringObject(x, y);
        draw_state_presistence.add(insert_str);
        break;     
    }
  }
  else if(state == GLUT_UP && now_draw_object != nullptr) {
    if(draw_mode != DRAW_MODE::POLYGON && draw_mode != DRAW_MODE::TEXT && is_motion) {
      draw_state_presistence.add(now_draw_object);
      now_draw_object = nullptr;
    }
  }
}

void motionCallback(int x, int y) {
  y = window_height - y;
  std::pair<float, float> pos = PaintBoard::getCanDrawRange(x, y);
  if(now_draw_object != nullptr && 
    draw_mode != DRAW_MODE::POLYGON &&
    draw_mode != DRAW_MODE::TEXT) {
    is_motion = true;
    now_draw_object->addPoint(pos.first, pos.second);
    draw_state_presistence.addTmpObject(now_draw_object);
  }
}

void passiveMotionCallback(int x, int y) {
  y = window_height - y;
  if(abs(x - pos_x) + abs(y - pos_y) < 4) return;
  if(PaintBoard::isInside(x, y) && draw_mode != DRAW_MODE::NONE && !is_open_palette_plane) {
    if(draw_mode == DRAW_MODE::TEXT) {
      glutSetCursor(GLUT_CURSOR_TEXT);
    }
    else {
      glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    }
  }
  else if(leftNavPlane->isInsideItem(x, y)) {
    glutSetCursor(GLUT_CURSOR_INFO);
  }
  else {
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
  }
  pos_x = x, pos_y = y;
}

void drawMenuCallback(int value) {
  draw_mode = value;
}

void colorMenuCallback(int value) {
  g_now_color = value;
}

void lineWidthMenuCallback(int value) {
  g_line_width = value;
}

void pointSizeMenuCallback(int value) {
  g_point_size = value;
}

void moreMenuCallback(int value) {
  switch(value) {
    case MORE_MENU::CLEAR:
      draw_state_presistence.clear();
      break;
    case MORE_MENU::QUIT:
      exit(0);
      break;
    case MORE_MENU::FULLMODE:
      glutFullScreen(); 
      break;
  }
}

void topMenuCallback(int value) {}

void createMenu() {
  draw_menu = glutCreateMenu(drawMenuCallback);
  glutAddMenuEntry("None", DRAW_MODE::NONE);
  glutAddMenuEntry("Line", DRAW_MODE::LINE);
  glutAddMenuEntry("Circle", DRAW_MODE::CIRCLE);
  glutAddMenuEntry("Triangle", DRAW_MODE::TRIANGLE);
  glutAddMenuEntry("Polygon", DRAW_MODE::POLYGON);
  glutAddMenuEntry("Text", DRAW_MODE::TEXT);

  color_menu = glutCreateMenu(colorMenuCallback);
  glutAddMenuEntry("Red", COLOR::RED);
  glutAddMenuEntry("Green", COLOR::GREEN);
  glutAddMenuEntry("Blue", COLOR::BLUE);
  glutAddMenuEntry("Black", COLOR::BLACK);
  glutAddMenuEntry("White", COLOR::WHITE);

  line_width_menu = glutCreateMenu(lineWidthMenuCallback);
  glutAddMenuEntry(" 1 ", 1);
  glutAddMenuEntry(" 2 ", 2);
  glutAddMenuEntry(" 4 ", 4);
  glutAddMenuEntry(" 8 ", 8);

  point_size_menu = glutCreateMenu(pointSizeMenuCallback);
  glutAddMenuEntry(" 1 ", 1);
  glutAddMenuEntry(" 2 ", 2);
  glutAddMenuEntry(" 4 ", 4);
  glutAddMenuEntry(" 8 ", 8);

  more_menu = glutCreateMenu(moreMenuCallback);
  glutAddMenuEntry("Clear", MORE_MENU::CLEAR);
  glutAddMenuEntry("Quit", MORE_MENU::QUIT);
  glutAddMenuEntry("Fill Mode", MORE_MENU::FULLMODE);

  top_menu = glutCreateMenu(topMenuCallback);
  glutAddSubMenu("Draw", draw_menu);
  glutAddSubMenu("Color", color_menu);
  glutAddSubMenu("Line Width", line_width_menu);
  glutAddSubMenu("Point Size", point_size_menu);
  glutAddSubMenu("More", more_menu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void initData() {
  glReadBuffer(GL_FRONT);
  glDrawBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  void *font = GLUT_BITMAP_HELVETICA_18;

  // paint_board = new PaintBoardObject(120.0, 0.0, window_width, window_height);
  // draw_state_presistence.addPaintBoardObject(paint_board);
  // draw_state_presistence.add(paint_board);

  leftNavPlane = new PlaneObject(
    0.0, 0.0, 120.0, window_height - 90, RGBAColor(204.0 / 255,  204.0 / 255,  204.0 / 255,  1.0));
  draw_state_presistence.add(leftNavPlane, true);

  int leftNavPlaneItemY = window_height - 90;

  {
    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 50, 100.0, 30.0, 
        "Line",
        [&](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::LINE;
        },
        RGBAColor(COLOR::BLUE),
        RGBAColor(COLOR::BLACK)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 90, 100.0, 30.0, 
        "Circle",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::CIRCLE;
        },
        RGBAColor(COLOR::BLUE),
        RGBAColor(COLOR::BLACK)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 130, 100.0, 30.0, 
        "Triangle",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::TRIANGLE;
        },
        RGBAColor(COLOR::BLUE),
        RGBAColor(COLOR::BLACK)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 170, 100.0, 30.0, 
        "Polygon",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::POLYGON;
        },
        RGBAColor(COLOR::BLUE),
        RGBAColor(COLOR::BLACK)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 210, 100.0, 30.0, 
        "Text",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::TEXT;
        },
        RGBAColor(COLOR::BLUE),
        RGBAColor(COLOR::BLACK)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 250, 100.0, 30.0, 
        "Noraml",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::NONE;
        },
        RGBAColor(COLOR::BLUE),
        RGBAColor(COLOR::BLACK)
      ), true
    );
  }


  NavBarPlane = new PlaneObject(
    0.0, window_height - 40, window_width, 40, RGBAColor(80.0 / 255,  80.0 / 255,  80.0 / 255,  1.0));
  draw_state_presistence.add(NavBarPlane, true);

  {
    NavBarPlane->addItem(
      new ButtonObject(
        0.0, window_height - 40, 120.0, 40.0, 
        "Save",
        [](ButtonObject *self) -> void {
          PaintBoard::save();
        },
        RGBAColor(COLOR::BLACK)      
      )
    );

    NavBarPlane->addItem(
      new ButtonObject(
        120.0, window_height - 40, 120.0, 40.0, 
        "Clear",
        [](ButtonObject *self) -> void {
          draw_state_presistence.clear();
        },
        RGBAColor(COLOR::BLACK)      
      )
    );

    NavBarPlane->addItem(
      new ButtonObject(
        240.0, window_height - 40, 120.0, 40.0, 
        "Undo",
        [](ButtonObject *self) -> void {
          draw_state_presistence.undo();
        },
        RGBAColor(COLOR::BLACK)      
      )
    );

    NavBarPlane->addItem(
      new ButtonObject(
        360.0, window_height - 40, 120.0, 40.0, 
        "Redo",
        [](ButtonObject *self) -> void {
          draw_state_presistence.redo();
        },
        RGBAColor(COLOR::BLACK)      
      )
    );

    NavBarPlane->addItem(
      new ButtonObject(
        window_width - 120, window_height - 40, 120.0, 40.0, 
        "Quit",
        [](ButtonObject *self) -> void {
          exit(0);
        },
        RGBAColor(COLOR::BLACK)      
      )
    );
  }

  ToolBarPlane = new PlaneObject(
    0.0, window_height - 90, window_width, 50, RGBAColor(204.0 / 255,  204.0 / 255,  204.0 / 255,  1.0));
  draw_state_presistence.add(ToolBarPlane, true);

  {
    ToolBarPlane->addItem(
      new TextObject(
        125.0, window_height - 90 + 20,
        "Line Width:",
        RGBAColor(COLOR::BLACK)
      )
    );

    ToolBarPlane->addItem(
      new ButtonObject(
        230.0, window_height - 90 + 9, 30.0, 30.0, 
        "-",
        [](ButtonObject *self) -> void {
          if (g_line_width > 1) {
            g_line_width--;
            text_line_width->update(std::to_string((int)g_line_width));
          }
        },
        RGBAColor(COLOR::BLACK),
        RGBAColor(COLOR::BLACK)
      )
    );

    text_line_width = new TextObject(
      270.0, window_height - 90 + 20,
      std::to_string((int)g_line_width),
      RGBAColor(COLOR::BLACK)
    );

    ToolBarPlane->addItem(text_line_width);

    ToolBarPlane->addItem(
      new ButtonObject(
        290.0, window_height - 90 + 9, 30.0, 30.0, 
        "+",
        [](ButtonObject *self) -> void {
          if(g_line_width < 8){
            g_line_width++;
            text_line_width->update(std::to_string((int)g_line_width));
          }
        },
        RGBAColor(COLOR::BLACK),
        RGBAColor(COLOR::BLACK) 
      )
    );

    ToolBarPlane->addItem(
      new TextObject(
        350.0, window_height - 90 + 20,
        "Color:",
        RGBAColor(COLOR::BLACK)
      )
    );

    now_color_object = new ColorObject(410.0, window_height - 90 + 9, 30.0, 30.0,
      [&](ColorObject *self) -> void {
        PalettePlane->toggleVisibility();
        is_open_palette_plane = PalettePlane->isVisible();
      });

    ToolBarPlane->addItem(now_color_object);

    ToolBarPlane->addItem(
      new TextObject(
        450.0, window_height - 90 + 20,
        "Fill:",
        RGBAColor(COLOR::BLACK)
      )
    );

    ToolBarPlane->addItem(
      new ButtonObject(
        500.0, window_height - 90 + 9, 40.0, 30.0, 
        "OFF",
        [](ButtonObject *self) -> void {
          is_full_mode = !is_full_mode;
          if (is_full_mode) {
            self->updateText("ON");
          } else {
            self->updateText("OFF");
          }
        },
        RGBAColor(COLOR::BLACK),
        RGBAColor(COLOR::BLACK) 
      )
    );
  }

  PalettePlane = new PlaneObject(
    325, window_height - 290, 200, 200, RGBAColor(204.0 / 255,  204.0 / 255,  204.0 / 255,  1.0));
  draw_state_presistence.add(PalettePlane, true);

  {
    PalettePlane->addItem(
      new PaletteTriangleObject(350, window_height - 235,
      [&](PaletteTriangleObject *self, float x, float y) -> void {
        float r, g, b;
        std::function<float(std::pair<float, float>, std::pair<float, float>)> getDis = 
          [](std::pair<float, float> a, std::pair<float, float> b) -> float {
            return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
          };
        b = 1 - max(getDis(self->vertices_pair[2], {x, y}) - 75 * sqrt(3) / 2, 0.0) / 75 * sqrt(3) / 2;
        g = 1 - max(getDis(self->vertices_pair[1], {x, y}) - 75 * sqrt(3) / 2, 0.0) / 75 * sqrt(3) / 2;
        r = 1 - max(getDis(self->vertices_pair[0], {x, y}) - 75 * sqrt(3) / 2, 0.0) / 75 * sqrt(3) / 2;
        g_now_color_rgba = RGBAColor(r, g, b, 1.0);
        now_color_object->setColor(g_now_color_rgba);
      })
    );

    PalettePlane->addItem(
      new ColorObject(350, window_height - 275, 30, 30,
      [&](ColorObject *self) -> void {
        g_now_color_rgba = self->getColor();
        now_color_object->setColor(g_now_color_rgba);
      },RGBAColor(COLOR::WHITE))
    );

    PalettePlane->addItem(
      new ColorObject(380, window_height - 275, 30, 30,
      [&](ColorObject *self) -> void {
        g_now_color_rgba = self->getColor();
        now_color_object->setColor(g_now_color_rgba);
      },RGBAColor(COLOR::BLACK))
    );

    PalettePlane->addItem(
      new ColorObject(410, window_height - 275, 30, 30,
      [&](ColorObject *self) -> void {
        g_now_color_rgba = self->getColor();
        now_color_object->setColor(g_now_color_rgba);
      },RGBAColor(COLOR::RED))
    );

    PalettePlane->addItem(
      new ColorObject(440, window_height - 275, 30, 30,
      [&](ColorObject *self) -> void {
        g_now_color_rgba = self->getColor();
        now_color_object->setColor(g_now_color_rgba);
      },RGBAColor(COLOR::GREEN))
    );

    PalettePlane->addItem(
      new ColorObject(470, window_height - 275, 30, 30,
      [&](ColorObject *self) -> void {
        g_now_color_rgba = self->getColor();
        now_color_object->setColor(g_now_color_rgba);
      },RGBAColor(COLOR::BLUE))
    );
  }
  PalettePlane->setVisibility(false);

  is_changed = true;
}

void display() {
  draw_state_presistence.display();
}

void idleCallback() {
  if (is_changed) {
    glutPostRedisplay();
    is_changed = false;
  }
}

void windowReshape(int _new_width, int _new_height) {
  window_width = _new_width;
  window_height = _new_height;
  if(is_full_screen == 0) {
    origin_window_width = _new_width;
    origin_window_height = _new_height;
  }
  glViewport(0, 0, _new_width, _new_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, _new_width, 0, _new_height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  PaintBoard::update(window_width, window_height);
  leftNavPlane->update(120.0, window_height - 90);
  NavBarPlane->update(0.0, window_height - 40, window_width, 40);
  ToolBarPlane->update(0.0, window_height - 90, window_width, 50);
  draw_state_presistence.display();
}

void keyboardEvent(unsigned char key, int x, int y) {
  if(is_insert_mode == 1 && (32 <= key && key <= 126)) {
    insert_str->add(key);
  }
  else if(is_insert_mode == 1 && key == 8) { //backspacew
    insert_str->del();
  }
  else if(is_insert_mode == 1 && key == 13) { //enter
    insert_str->exit();
    insert_str = nullptr;
  }
  else if(is_insert_mode == 0){
    switch(key) {
      case 14: //ctrl + n
        draw_state_presistence.clear();
        break;
      case 26: // ctrl + z
        draw_state_presistence.undo();
        break;
      case 18: // ctrl + r
        draw_state_presistence.redo();
        break;
      case 27:
        glutReshapeWindow(origin_window_width, origin_window_height);
        is_full_screen = 0;
        break;
      case 19: // ctrl + s
        PaintBoard::save();
        break;
      case 17:
      case 'q':
      case 'Q':
        exit(0);
        break;
      case 'c':
      case 'C':
        is_mouse_down = 0;
        draw_state_presistence.clear();
        break;
      case 'f':
      case 'F':
        if(is_full_screen) {
          glutReshapeWindow(origin_window_width, origin_window_height);
          is_full_screen = 0;
        } 
        else {
          is_full_screen = 1;
          glutFullScreen();
        }
        break;
    }
  }
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  window_width = glutGet(GLUT_SCREEN_WIDTH);
  window_height = glutGet(GLUT_SCREEN_HEIGHT) - 71;

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(window_width, window_height);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  
  initData();

  glutCreateWindow("Drawing Panel");

  glutDisplayFunc(display);
  glutReshapeFunc(windowReshape);

  glutKeyboardFunc(keyboardEvent);
  glutMouseFunc(mouseCallback);
  glutMotionFunc(motionCallback);  
  glutPassiveMotionFunc(passiveMotionCallback);

  createMenu();

  glutIdleFunc(idleCallback);
  glutMainLoop();
}
