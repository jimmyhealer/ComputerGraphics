#include "define.hpp"

DrawObject *tmp;

void mouseCallback(int button, int state, int x, int y) {
  y = window_height - y;
  if(button != GLUT_LEFT_BUTTON) return;
  if(state == GLUT_DOWN) {
    pos_x = x, pos_y = y;
    is_mouse_down = true;
  }
  else if(state == GLUT_UP && is_mouse_down == 1) {
    is_mouse_down = false;
    draw_state.add(tmp);
  }
}

void motionCallback(int x, int y) {
  y = window_height - y;
  if(is_mouse_down) {
    tmp = new TriangleObject(
        pos_x, pos_y,
        2 * pos_x - x, y,
        x, y,
        line_width,
        RGBAColor(now_color)
      );
    draw_state.addTmpObject(tmp);
  }
}

void initData() {
  glReadBuffer(GL_FRONT);
  glDrawBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  paint_board = new PaintBoardObject(120.0, 0.0, window_width, window_height);
  draw_state.add(paint_board, true);
}

void display() {
  draw_state.display();
}

void windowReshape(int _new_width, int _new_height) {
  window_width = _new_width;
  window_height = _new_height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, _new_width, 0, _new_height);
  glViewport(0, 0, _new_width, _new_height);
  glMatrixMode(GL_MODELVIEW);
  paint_board->update(window_width, window_height);
  glutPostRedisplay();
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

  glutMouseFunc(mouseCallback);
  glutMotionFunc(motionCallback);  
  glutMainLoop();
}
