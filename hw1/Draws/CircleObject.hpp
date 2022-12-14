class CircleObject : public DrawObject {
protected:
  float radius;
  float line_width;
  int fill_mode;
  RGBAColor color;
  GLUquadricObj *quadric = nullptr;
public:
  CircleObject(float x_, float y_) : DrawObject(x_, y_) {
    this->line_width = g_line_width;
    this->color = g_now_color_rgba;
    this->fill_mode = is_full_mode;
    if(this->quadric == nullptr) {
      this->quadric = gluNewQuadric();
    }
  }
  void draw() override {
    float innerRadius = fill_mode ? 0 : radius - line_width;
    glColor3f(color.r, color.g, color.b);
    gluQuadricDrawStyle(quadric, GLU_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    gluDisk(quadric, innerRadius, radius, 50, 1);
    glPopMatrix();
  }
  void addPoint(float x, float y) override {
    radius = sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
    radius = PaintBoard::getCanDrawRange(this->x, this->y, radius);
  }
};