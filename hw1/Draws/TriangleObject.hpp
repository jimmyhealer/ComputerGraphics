class TriangleObject : public DrawObject {
protected:
  float x2, y2, x3, y3;
  float line_width;
  RGBAColor color;
public:
  TriangleObject() {}
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
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glLineWidth(line_width);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
  }
};