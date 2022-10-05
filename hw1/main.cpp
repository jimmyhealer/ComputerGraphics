#include "define.hpp"

void mouseCallback(int button, int state, int x, int y) {
  y = window_height - y;
  if(button != GLUT_LEFT_BUTTON) return;

  // if(state == GLUT_DOWN)
  //   NavBarPlane->isClickItem(x, y);
  if(!paint_board->isInside(x, y) && state == GLUT_DOWN)
    leftNavPlane->isClickItem(x, y);

  if(draw_mode != DRAW_MODE::NONE && state == GLUT_DOWN && paint_board->isInside(x, y)) {
    pos_x = x, pos_y = y;
    is_mouse_down = 1;
  }
  else if(state == GLUT_UP && is_mouse_down == 1) {
    is_changed = true;
    is_mouse_down = false;
    std::pair<float, float> pos, pos2;
    pos = paint_board->getCanDrawRange(x, y);
    switch(draw_mode) {
      case DRAW_MODE::LINE:
        draw_state_presistence.add(
          new LineObject(
            pos_x, pos_y,
            pos.first, pos.second,
            line_width,
            RGBAColor(now_color)
          ), false
        );
        break;
      case DRAW_MODE::CIRCLE:
        draw_state_presistence.add(
          new CircleObject(
            pos_x, pos_y,
            paint_board->getCanDrawRange(
              pos_x, pos_y, sqrt(pow(pos_x - pos.first, 2) + pow(pos_y - pos.second, 2))
            ),
            line_width,
            RGBAColor(now_color)
          ), false
        );
        break;
      case DRAW_MODE::TRIANGLE:
        pos2 = paint_board->getCanDrawRange(2 * pos_x - pos.first, pos.second);
        draw_state_presistence.add(
          new TriangleObject(
            pos_x, pos_y,
            2 * pos_x - pos2.first, pos.second,
            pos2.first, pos2.second,
            line_width,
            RGBAColor(now_color)
          ), false
        );
        break;
      case DRAW_MODE::POLYGON:
        if(polygon == nullptr) {
          polygon = new PolygonObject(pos_x, pos_y, line_width, RGBAColor(now_color));
          draw_state_presistence.add(polygon, false);
        }
        else if(!polygon->checkClosed(pos_x, pos_y)) {
          polygon->add(pos_x, pos_y);
        }
        else {
          polygon->add(pos_x, pos_y, true);
          polygon = nullptr;
        }
        break;
      case DRAW_MODE::TEXT:
        if(is_insert_mode == 1) break;
        is_insert_mode = 1;
        insert_str = new StringObject(
          pos_x, pos_y,
          GLUT_BITMAP_HELVETICA_18,
          "",
          RGBAColor(now_color)
        );
        draw_state_presistence.add(insert_str);
        break;
      default:
        break;
    }
  }
}

void motionCallback(int x, int y) {
  y = window_height - y;
  std::pair<float, float> pos = paint_board->getCanDrawRange(x, y), pos2;
  if(is_mouse_down) {
    switch(draw_mode) {
      case DRAW_MODE::LINE:
        draw_state_presistence.addTmpObject(
          new LineObject(
            pos_x, pos_y,
            pos.first, pos.second,
            line_width,
            RGBAColor(now_color)
          )
        );
        break;
      case DRAW_MODE::CIRCLE:
        draw_state_presistence.addTmpObject(
          new CircleObject(
            pos_x, pos_y,
            paint_board->getCanDrawRange(
              pos_x, pos_y, sqrt(pow(pos_x - pos.first, 2) + pow(pos_y - pos.second, 2))
            ),
            line_width,
            RGBAColor(now_color)
          )
        );
        break;
      case DRAW_MODE::TRIANGLE:
        pos2 = paint_board->getCanDrawRange(2 * pos_x - pos.first, pos.second);
        draw_state_presistence.addTmpObject(
          new TriangleObject(
            pos_x, pos_y,
            2 * pos_x - pos2.first, pos.second,
            pos2.first, pos2.second,
            line_width,
            RGBAColor(now_color)
          )
        );
        break;
    }
  }
}

void passiveMotionCallback(int x, int y) {
  y = window_height - y;
  if(abs(x - pos_x) + abs(y - pos_y) < 4) return;
  if(paint_board->isInside(x, y) && draw_mode != DRAW_MODE::NONE) {
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
  // str_draw_mode->update("Draw Mode: " + draw_mode_str[draw_mode]);
}

void colorMenuCallback(int value) {
  now_color = value;
  // str_now_color->update("Now Color: " + color_str[now_color]);
}

void lineWidthMenuCallback(int value) {
  line_width = value;
  // str_line_width->update("Line Width: " + std::to_string((int)line_width));
}

void pointSizeMenuCallback(int value) {
  point_size = value;
  // str_point_size->update("Point Size: " + std::to_string((int)point_size));
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

  paint_board = new PaintBoardObject(120.0, 0.0, window_width, window_height);
  draw_state_presistence.add(paint_board, true);

  // str_draw_mode = new StringObject(10.0, 10.0, font, "Draw Mode: " + draw_mode_str[draw_mode], RGBAColor(COLOR::BLUE));
  // draw_state_presistence.add(str_draw_mode, true);
  
  // str_now_color = new StringObject(10.0, 30.0, font, "Now Color: " + color_str[now_color], RGBAColor(COLOR::BLUE));
  // draw_state_presistence.add(str_now_color, true);

  // str_line_width = new StringObject(10.0, 50.0, font, "Line Width: " + std::to_string((int)line_width), RGBAColor(COLOR::BLUE));
  // draw_state_presistence.add(str_line_width, true);

  // str_point_size = new StringObject(10.0, 70.0, font, "Point Size: " + std::to_string((int)point_size), RGBAColor(COLOR::BLUE));
  // draw_state_presistence.add(str_point_size, true);


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
        RGBAColor(COLOR::BLUE)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 90, 100.0, 30.0, 
        "Circle",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::CIRCLE;
        },
        RGBAColor(COLOR::BLUE)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 130, 100.0, 30.0, 
        "Triangle",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::TRIANGLE;
        },
        RGBAColor(COLOR::BLUE)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 170, 100.0, 30.0, 
        "Polygon",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::POLYGON;
        },
        RGBAColor(COLOR::BLUE)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 210, 100.0, 30.0, 
        "Text",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::TEXT;
        },
        RGBAColor(COLOR::BLUE)
      )
    );

    leftNavPlane->addItem(
      new ButtonObject(
        10.0, leftNavPlaneItemY - 250, 100.0, 30.0, 
        "Noraml",
        [](ButtonObject *self) -> void {
          draw_mode = DRAW_MODE::NONE;
        },
        RGBAColor(COLOR::BLUE)
      ), true
    );
  }

  NavBarPlane = new PlaneObject(
    0.0, window_height - 45, window_width, 45, RGBAColor(80.0 / 255,  80.0 / 255,  80.0 / 255,  1.0));
  draw_state_presistence.add(NavBarPlane, true);

  NavBarPlane->addItem(
    new ButtonObject(
      0.0, window_height - 45, 120.0, 45.0, 
      "File",
      [](ButtonObject *self) -> void {
        is_open_file_menu = !is_open_file_menu;
        fileMenuPlane->setVisibility(is_open_file_menu);
      },
      RGBAColor(COLOR::BLACK)      
    )
  );

  fileMenuPlane = new PlaneObject(
    0.0, window_height - 200, 120.0, 155.0, RGBAColor(80.0 / 255,  80.0 / 255,  80.0 / 255,  1.0));
  fileMenuPlane->setVisibility(false);
  draw_state_presistence.add(fileMenuPlane, false);

  fileMenuPlane->addItem(
    new ButtonObject(
      0.0, window_height - 80, 120.0, 35.0, 
      "New",
      [](ButtonObject *self) -> void {
        draw_state_presistence.clear();
      },
      RGBAColor(COLOR::BLACK)      
    )
  );

  ToolBarPlane = new PlaneObject(
    0.0, window_height - 90, window_width, 45, RGBAColor(204.0 / 255,  204.0 / 255,  204.0 / 255,  1.0));
  draw_state_presistence.add(ToolBarPlane, true);

  is_changed = true;
}

void display() {
  draw_state_presistence.display();
}

void idleCallback() {
  // if(is_changed) {
  //   draw_state_presistence.display();
  //   is_changed = false;
  // }
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
  paint_board->update(window_width, window_height);
  leftNavPlane->update(120.0, window_height - 90);
  NavBarPlane->update(0.0, window_height - 45, window_width, 45);
  ToolBarPlane->update(0.0, window_height - 90, window_width, 45);
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
  // glutPassiveMotionFunc(passiveMotionCallback);

  createMenu();

  glutIdleFunc(idleCallback);
  glutMainLoop();
}
