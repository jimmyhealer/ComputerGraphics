class ColorObject : public UIObject{
public:
  ColorObject() {}
  ColorObject(float x_, float y_, float width_, float height_) :
    UIObject(x_, y_, width_, height_, RGBAColor(g_now_color)) {}
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
  }
  void click() override {}
  void addPoint(float x, float y) override {}
};