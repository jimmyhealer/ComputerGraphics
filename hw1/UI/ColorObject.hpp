class ColorObject : public UIObject{
std::function<void(ColorObject*)> callback;
public:
  ColorObject() {}
  ColorObject(float x_, float y_, float width_, float height_, std::function<void(ColorObject*)> callback_) :
    UIObject(x_, y_, width_, height_, RGBAColor(g_now_color)) {
      this->callback = callback_;
    }
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
  }
  void click(float x=0, float y=0) override {
    if(isEnabled()) {
      callback(this);
      is_changed = true;
    }
  }
  void addPoint(float x, float y) override {}
};