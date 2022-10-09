class UIObject : public DrawObject {
protected:
  float width, height;
  bool is_visible;
  bool is_enabled;
  bool is_clicked;
  RGBAColor color;
public:
  UIObject() {};
  UIObject(
    float x_, float y_, 
    float width_, float height_, RGBAColor color_) :
    DrawObject(x_, y_) {
    this->x = x_;
    this->y = y_;
    this->width = width_;
    this->height = height_;
    this->color = color_;
    this->is_visible = true;
    this->is_enabled = true;
    this->is_clicked = false;
  }
  void enable() {
    is_enabled = true;
  }
  void disable() {
    is_enabled = false;
  }
  void show() {
    is_visible = true;
  }
  void hide() {
    is_visible = false;
  }
  void toggleVisibility() {
    is_visible = !is_visible;
  }
  void setVisibility(bool is_visible) {
    this->is_visible = is_visible;
  }
  bool isVisible() {
    return is_visible;
  }
  bool isEnabled() {
    return is_enabled;
  }
  bool getIsClicked() {
    return is_clicked;
  }
  virtual bool isInside(int x, int y) {
    bool res = (
      x >= this->x && x <= this->x + this->width &&
      y >= this->y && y <= this->y + this->height
    );
    return res;
  }
  void hover() {
    color = RGBAColor(0.5, 0.5, 0.5, 1.0);
  }
   void setIsClicked(int is_clicked_) {
    is_clicked = is_clicked_;
  }
  void setColor(RGBAColor color) {
    this->color = color;
  }
  RGBAColor getColor() {
    return color;
  }
  virtual void draw() = 0;
  virtual void click(float x=0, float y=0) = 0;
};