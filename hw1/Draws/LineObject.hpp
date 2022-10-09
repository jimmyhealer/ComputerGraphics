class LineObject : public DrawObject {
protected:
  float x2, y2;
  float line_width;
  RGBAColor color;
public:
  LineObject(float x_, float y_): DrawObject(x_, y_) {
    this->line_width = g_line_width;
    this->color = g_now_color_rgba;
  }
  void addPoint(float x, float y) override {
    x2 = x;
    y2 = y;
  }
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glLineWidth(line_width);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x2, y2);
    glEnd();
  }
};