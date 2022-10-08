class PaintBoardObject : public DrawObject {
protected:
  float width, height;
public:
  PaintBoardObject() {}
  PaintBoardObject(float x_, float y_, float width_, float height_) : DrawObject(x_, y_) {
    width = width_ - x_ - 120;
    height = height_ - y_ - 90;
  }
  void update(float width_, float height_) {
    width = width_ - x - 120;
    height = height_ - y - 90;
  }
  bool isInside(float x_, float y_) {
    return x_ >= x && x_ <= x + width && y_ >= y && y_ <= y + height;
  }
  std::pair<float, float> getCanDrawRange(float x_, float y_) {
    if(x_ < x) x_ = x;
    if(x_ > x + width) x_ = x + width;
    if(y_ < y) y_ = y;
    if(y_ > y + height) y_ = y + height;
    return {x_, y_};
  };
  float getCanDrawRange(float x_, float y_, float radius_) {
    if(x_ < x) x_ = x;
    if(x_ > x + width) x_ = x + width;
    if(y_ < y) y_ = y;
    if(y_ > y + height) y_ = y + height;
    if(x_ - radius_ < x) radius_ = x_ - x;
    if(x_ + radius_ > x + width) radius_ = x + width - x_;
    if(y_ - radius_ < y) radius_ = y_ - y;
    if(y_ + radius_ > y + height) radius_ = y + height - y_;
    return radius_;
  };
  void draw() override {
    glColor3f(1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
  }
  void addPoint(float x, float y) override {}
};