class LineObject : public DrawObject {
protected:
  float x2, y2;
  float line_width;
  RGBAColor color;
public:
  LineObject() {}
  LineObject(
    float x_, float y_,
    float x2_, float y2_,
    float line_width_,
    RGBAColor color_) : DrawObject(x_, y_) {
    x2 = x2_;
    y2 = y2_;
    color = color_;
    line_width = line_width_;
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