class PaletteTriangleObject: public UIObject {
protected:
  float vertices[3][3];
public:
  PaletteTriangleObject(float x_, float y_) :
    UIObject(x_, y_, 0, 0, RGBAColor(COLOR::WHITE)) {
      vertices[0][0] = x_;
      vertices[0][1] = y_;
      vertices[0][2] = 0;
      vertices[1][0] = x_ + 150;
      vertices[1][1] = y_;
      vertices[1][2] = 0;
      vertices[2][0] = x_ + 75;
      vertices[2][1] = y_ + 150;
      vertices[2][2] = 0;
    };
  void draw() override {
    if (!isVisible()) return;
    float color[] = {
      255, 0, 0,
      0, 255, 0,
      0, 0, 255
    };
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, color);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
  }
  bool isInside(int x_, int y_) override {
    return true;
  }
  void click(float x=0, float y=0) override {
    if(isEnabled()) {
      DEBUG(x) DEBUGN(y)
      color = RGBAColor(255 / 255.0, 0.0 / 255, 0.0 / 255 , 1);
      is_changed = true;
    }
  }
  void addPoint(float, float) override {}
};