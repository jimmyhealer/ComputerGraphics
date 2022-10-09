class TriangleObject : public DrawObject {
protected:
  float x2, y2, x3, y3;
  float line_width;
  int fill_mode;
  RGBAColor color;
public:
  TriangleObject(float x_, float y_): DrawObject(x_, y_) {
    this->line_width = g_line_width;
    this->color = g_now_color_rgba;
    this->fill_mode = is_full_mode ? GL_FILL : GL_LINE;
  }
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glLineWidth(line_width);
    glPolygonMode(GL_FRONT_AND_BACK, fill_mode);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
  }
  void addPoint(float x_, float y_) override {
    std::pair<float, float> p = PaintBoard::getCanDrawRange(2 * x - x_, y_);
    x2 = 2 * x - p.first;
    y2 = y_;
    x3 = p.first;
    y3 = p.second;
  }
};