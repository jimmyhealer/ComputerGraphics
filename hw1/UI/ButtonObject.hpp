class ButtonObject: public UIObject {
private:
  StringObject *text;
  std::function<void(ButtonObject*)> callback;
  RGBAColor text_color = RGBAColor(1, 1, 1, 1);
  bool is_clicked = false;
public:
  ButtonObject() {};
  ButtonObject(
    float x_, float y_, 
    float width_, float height_, 
    std::string text_, std::function<void(ButtonObject*)> callback_,
    RGBAColor color_, RGBAColor text_color_=RGBAColor(1, 1, 1, 1)) :
    UIObject(x_, y_, width_, height_, color_) {
    this->text = new StringObject(x_ + width_ / 2 - 4.2 * text_.size(), y_ + height_ / 2.0 - height_ / 5.0);
    this->text->setColor(RGBAColor(text_color_));
    this->text->update(text_);
    this->callback = callback_;
  }
  void setPos(float x_, float y_) {
    this->x = x_;
    this->y = window_height - y_;
    // this->text.setPos(x_ + width / 2 - 4.2 * text.getText().size(), y_ + height / 2.0 - height / 5.0);
  }
  void draw() override {
    if (isVisible()) {
      if(is_clicked) {
        glColor4f(color.r + 0.7, color.g + 0.7, color.b + 0.7, color.a);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
      else {
        glColor4f(color.r, color.g, color.b, color.a);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }
      glLineWidth(1.0);
      glBegin(GL_POLYGON);
      glVertex2f(x, y);
      glVertex2f(x + width, y);
      glVertex2f(x + width, y + height);
      glVertex2f(x, y + height);
      glEnd();
      if(is_clicked) {
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
      }
      text->draw();
    }
  }
  bool getIsClicked() {
    return is_clicked;
  }
  bool isInside(int x, int y) {
    bool res = (
      x >= this->x && x <= this->x + this->width &&
      y >= this->y && y <= this->y + this->height
    );
    return res;
  }
  void hover() {
    color = RGBAColor(0.5, 0.5, 0.5, 1.0);
  }
  void click() {
    if (isEnabled()) {
      is_changed = true;
      callback(this);
    }
  }
  void setIsClicked(int is_clicked_) {
    is_clicked = is_clicked_;
  }
  void setTextColor(RGBAColor color_) {
    text_color = color_;
  }
  void addPoint(float x, float y) override {} 
};