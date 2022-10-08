class StringObject : public DrawObject {
protected:
  void *font;
  std::string str;
  RGBAColor color;
public:
  StringObject(float x_, float y_): DrawObject(x_, y_) {
    this->font = GLUT_BITMAP_9_BY_15;
    this->str = "";
    this->color = RGBAColor(g_now_color);
  }
  StringObject(float x_, float y_,
    std::string str_, RGBAColor color_): DrawObject(x_, y_) {
    this->font = GLUT_BITMAP_9_BY_15;
    this->str = str_;
    this->color = color_;
  }
  void update(std::string str_) {
    str = str_;
    is_changed = true;
  }
  void add(char c) {
    str += c;
    is_changed = true;
  }
  void del() {
    if(str.size() > 0) {
      str.pop_back();
      is_changed = true;
    }
  }
  void exit() {
    is_insert_mode = 0;
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
  void addPoint(float x, float y) override {}
};