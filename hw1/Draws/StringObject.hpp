class StringObject : public DrawObject {
protected:
  void *font;
  std::string str;
  RGBAColor color;
public:
  StringObject() {}
  StringObject(float x_, float y_, void *font_, std::string str_, RGBAColor color_): DrawObject(x_, y_) {
    font = font_;
    str = str_;
    color = color_;
  }
  void update(std::string str_) {
    str = str_;
    is_changed = true;
    // draw_state_presistence.display();
  }
  void add(char c) {
    str += c;
    is_changed = true;
    // draw_state_presistence.display();
  }
  void del() {
    if(str.size() > 0) {
      str.pop_back();
      is_changed = true;
      // draw_state_presistence.display();
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
};