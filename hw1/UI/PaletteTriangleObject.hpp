class PaletteTriangleObject: public UIObject {
protected:
  float vertices[3][3];
  std::function<void(PaletteTriangleObject*, float x, float y)> callback;
public:
  std::pair<float, float> vertices_pair[3];
  PaletteTriangleObject(float x_, float y_,
    std::function<void(PaletteTriangleObject*, float, float)> callback_ ) :
    UIObject(x_, y_, 0, 0, RGBAColor(COLOR::WHITE)) {
      this->vertices[0][0] = x_;
      this->vertices[0][1] = y_;
      this->vertices[0][2] = 0;
      this->vertices[1][0] = x_ + 150;
      this->vertices[1][1] = y_;
      this->vertices[1][2] = 0;
      this->vertices[2][0] = x_ + 75;
      this->vertices[2][1] = y_ + 129;
      this->vertices[2][2] = 0;
      this->vertices_pair[0] = {x_, y_};
      this->vertices_pair[1] = {x_ + 150, y_};
      this->vertices_pair[2] = {x_ + 75, y_ + 129};
      this->callback = callback_;
    };
  void draw() override {
    if (!isVisible()) return;
    float color[] = {
      255, 0, 0,
      0, 255, 0,
      0, 0, 255
    };
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, color);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
  }
  bool isInside(int x_, int y_) override {
    float x1 = vertices_pair[0].first, y1 = vertices_pair[0].second;
    float x2 = vertices_pair[1].first, y2 = vertices_pair[1].second;
    float x3 = vertices_pair[2].first, y3 = vertices_pair[2].second;
    float v1 = (x2 - x1) * (y_ - y1) - (x_ - x1) * (y2 - y1);
    float v2 = (x3 - x2) * (y_ - y2) - (x_ - x2) * (y3 - y2);
    float v3 = (x1 - x3) * (y_ - y3) - (x_ - x3) * (y1 - y3);
    return (v1 > 0 && v2 > 0 && v3 > 0) || (v1 < 0 && v2 < 0 && v3 < 0);
  }
  void click(float x=0, float y=0) override {
    if(isEnabled()) {
      callback(this, x, y);
      is_changed = true;
    }
  }
  void addPoint(float, float) override {}
};