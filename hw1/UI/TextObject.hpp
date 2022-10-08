class TextObject : public UIObject {
protected:
  void *font;
  std::string str;
public:
  TextObject() {}
  TextObject(float x_, float y_,
    std::string str_, RGBAColor color_): UIObject(x_, y_, 0, 0, color_) {
    this->font = GLUT_BITMAP_9_BY_15;
    this->str = str_;
  }
  void update(std::string str_) {
    str = str_;
    is_changed = true;
  }
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glRasterPos2f(x, y);
    for (int i = 0; i < str.length(); i++) {
      glutBitmapCharacter(font, str[i]);
    }
  }
  void setColor(RGBAColor color_) {
    color = color_;
  }
  void click() override {}
  void addPoint(float x, float y) override {}
};