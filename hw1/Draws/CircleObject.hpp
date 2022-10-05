class CircleObject : public DrawObject {
protected:
  float radius;
  float line_width;
  RGBAColor color;
  GLUquadricObj *quadric = nullptr;
public:
  CircleObject() {}
  CircleObject(
    float x_, float y_,
    float radius_,
    float line_width_,
    RGBAColor color_) : DrawObject(x_, y_) {
    radius = radius_;
    color = color_;
    line_width = line_width_;
    if(quadric == nullptr) {
      quadric = gluNewQuadric();
      gluQuadricDrawStyle(quadric, GLU_FILL);
    }
  }
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    gluDisk(quadric, 0.0, radius, 100, 100);
    glPopMatrix();
  }
};