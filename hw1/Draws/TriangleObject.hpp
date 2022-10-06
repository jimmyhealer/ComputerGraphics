class TriangleObject : public DrawObject {
protected:
  float x2, y2, x3, y3;
  float line_width;
  RGBAColor color;
public:
  TriangleObject(float x, float y) {
    this->x = x, this->y = y;
  }
  TriangleObject(
    float x_, float y_,
    float x2_, float y2_,
    float x3_, float y3_,
    float line_width_,
    RGBAColor color_) : DrawObject(x_, y_) {
    x2 = x2_, y2 = y2_, x3 = x3_, y3 = y3_;
    color = color_;
    line_width = line_width_;
  }
  void set(int x_, int y_) {
    x2 = 2 * x - x_, y2 = y_;
    x3 = x_, y3 = y_;
  }
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
  }
};
